#include "mqtt.h"

enum MQTTErrors mqtt_init(struct mqtt_client *client,
                          int sockfd,
                          uint8_t *sendbuf, size_t sendbufsz,
                          uint8_t *recvbuf, size_t recvbufsz,
                          void (*publish_response_callback)(void **state, struct mqtt_response_publish *publish))
{
    if (client == NULL || sendbuf == NULL || recvbuf == NULL)
    {
        return MQTT_ERROR_NULLPTR;
    }

    /* initialize mutex */
    MQTT_PAL_MUTEX_INIT(&client->mutex);
    MQTT_PAL_MUTEX_LOCK(&client->mutex); /* unlocked during CONNECT */

    client->socketfd = sockfd;

    mqtt_mq_init(&client->mq, sendbuf, sendbufsz);

    client->recv_buffer.mem_start = recvbuf;
    client->recv_buffer.mem_size = recvbufsz;
    client->recv_buffer.curr = client->recv_buffer.mem_start;
    client->recv_buffer.curr_sz = client->recv_buffer.mem_size;

    client->error = MQTT_ERROR_CONNECT_NOT_CALLED;
    client->response_timeout = 30;
    client->number_of_timeouts = 0;
    client->number_of_keep_alives = 0;
    client->typical_response_time = -1.0;
    client->publish_response_callback = publish_response_callback;
    client->pid_lfsr = 0;
    client->send_offset = 0;

    client->inspector_callback = NULL;
    client->reconnect_callback = NULL;
    client->reconnect_state = NULL;

    return MQTT_OK;
}

void mqtt_mq_init(struct mqtt_message_queue *mq, void *buf, size_t bufsz)
{
    if (buf != NULL)
    {
        mq->mem_start = buf;
        mq->mem_end = (unsigned char *)buf + bufsz;
        mq->curr = buf;
        mq->queue_tail = mq->mem_end;
        mq->curr_sz = mqtt_mq_currsz(mq);
    }
}

#define MQTT_CLIENT_TRY_PACK(tmp, msg, client, pack_call, release) \
    if (client->error < 0)                                         \
    {                                                              \
        if (release)                                               \
            int(&client->mutex);                                   \
        return client->error;                                      \
    }                                                              \
    tmp = pack_call;                                               \
    if (tmp < 0)                                                   \
    {                                                              \
        client->error = tmp;                                       \
        if (release)                                               \
            int(&client->mutex);                                   \
        return tmp;                                                \
    }                                                              \
    else if (tmp == 0)                                             \
    {                                                              \
        mqtt_mq_clean(&client->mq);                                \
        tmp = pack_call;                                           \
        if (tmp < 0)                                               \
        {                                                          \
            client->error = tmp;                                   \
            if (release)                                           \
                int(&client->mutex);             \
            return tmp;                                            \
        }                                                          \
        else if (tmp == 0)                                         \
        {                                                          \
            client->error = MQTT_ERROR_SEND_BUFFER_IS_FULL;        \
            if (release)                                           \
                int(&client->mutex);             \
            return MQTT_ERROR_SEND_BUFFER_IS_FULL;                 \
        }                                                          \
    }                                                              \
    msg = mqtt_mq_register(&client->mq, tmp);

enum MQTTErrors mqtt_connect(struct mqtt_client *client,
                             const char *client_id,
                             const char *will_topic,
                             const void *will_message,
                             size_t will_message_size,
                             const char *user_name,
                             const char *password,
                             uint8_t connect_flags,
                             uint16_t keep_alive)
{
    ssize_t rv;
    struct mqtt_queued_message *msg;

    client->keep_alive = keep_alive;
    if (client->error == MQTT_ERROR_CONNECT_NOT_CALLED)
    {
        client->error = MQTT_OK;
    }

    MQTT_CLIENT_TRY_PACK(rv, msg, client,
                         mqtt_pack_connection_request(
                             client->mq.curr, client->mq.curr_sz,
                             client_id, will_topic, will_message,
                             will_message_size, user_name, password,
                             connect_flags, keep_alive),
                         1);

    msg->control_type = MQTT_CONTROL_CONNECT;

    int(&client->mutex);
    return MQTT_OK;
}

ssize_t mqtt_pack_connection_request(uint8_t* buf, size_t bufsz,
                                     const char* client_id,
                                     const char* will_topic,
                                     const void* will_message,
                                     size_t will_message_size,
                                     const char* user_name,
                                     const char* password,
                                     uint8_t connect_flags,
                                     uint16_t keep_alive)
{ 
    struct mqtt_fixed_header fixed_header;
    size_t remaining_length;
    const uint8_t *const start = buf;
    ssize_t rv;

    /* pack the fixed headr */
    fixed_header.control_type = MQTT_CONTROL_CONNECT;
    fixed_header.control_flags = 0x00;

    /* calculate remaining length and build connect_flags at the same time */
    connect_flags = connect_flags & ~MQTT_CONNECT_RESERVED;
    remaining_length = 10; /* size of variable header */

    if (client_id == NULL) {
        client_id = "";
    }
    /* For an empty client_id, a clean session is required */
    if (client_id[0] == '\0' && !(connect_flags & MQTT_CONNECT_CLEAN_SESSION)) {
        return MQTT_ERROR_CLEAN_SESSION_IS_REQUIRED;
    }
    /* mqtt_string length is strlen + 2 */
    remaining_length += __mqtt_packed_cstrlen(client_id);

    if (will_topic != NULL) {
        uint8_t temp;
        /* there is a will */
        connect_flags |= MQTT_CONNECT_WILL_FLAG;
        remaining_length += __mqtt_packed_cstrlen(will_topic);
        
        if (will_message == NULL) {
            /* if there's a will there MUST be a will message */
            return MQTT_ERROR_CONNECT_NULL_WILL_MESSAGE;
        }
        remaining_length += 2 + will_message_size; /* size of will_message */

        /* assert that the will QOS is valid (i.e. not 3) */
        temp = connect_flags & 0x18; /* mask to QOS */   
        if (temp == 0x18) {
            /* bitwise equality with QoS 3 (invalid)*/
            return MQTT_ERROR_CONNECT_FORBIDDEN_WILL_QOS;
        }
    } else {
        /* there is no will so set all will flags to zero */
        connect_flags &= ~MQTT_CONNECT_WILL_FLAG;
        connect_flags &= ~0x18;
        connect_flags &= ~MQTT_CONNECT_WILL_RETAIN;
    }

    if (user_name != NULL) {
        /* a user name is present */
        connect_flags |= MQTT_CONNECT_USER_NAME;
        remaining_length += __mqtt_packed_cstrlen(user_name);
    } else {
        connect_flags &= ~MQTT_CONNECT_USER_NAME;
    }

    if (password != NULL) {
        /* a password is present */
        connect_flags |= MQTT_CONNECT_PASSWORD;
        remaining_length += __mqtt_packed_cstrlen(password);
    } else {
        connect_flags &= ~MQTT_CONNECT_PASSWORD;
    }

    /* fixed header length is now calculated*/
    fixed_header.remaining_length = remaining_length;

    /* pack fixed header and perform error checks */
    rv = mqtt_pack_fixed_header(buf, bufsz, &fixed_header);
    if (rv <= 0) {
        /* something went wrong */
        return rv;
    }
    buf += rv;
    bufsz -= rv;

    /* check that the buffer has enough space to fit the remaining length */
    if (bufsz < fixed_header.remaining_length) {
        return 0;
    }

    /* pack the variable header */
    *buf++ = 0x00;
    *buf++ = 0x04;
    *buf++ = (uint8_t) 'M';
    *buf++ = (uint8_t) 'Q';
    *buf++ = (uint8_t) 'T';
    *buf++ = (uint8_t) 'T';
    *buf++ = MQTT_PROTOCOL_LEVEL;
    *buf++ = connect_flags;
    buf += __mqtt_pack_uint16(buf, keep_alive);

    /* pack the payload */
    buf += __mqtt_pack_str(buf, client_id);
    if (connect_flags & MQTT_CONNECT_WILL_FLAG) {
        buf += __mqtt_pack_str(buf, will_topic);
        buf += __mqtt_pack_uint16(buf, (uint16_t)will_message_size);
        memcpy(buf, will_message, will_message_size);
        buf += will_message_size;
    }
    if (connect_flags & MQTT_CONNECT_USER_NAME) {
        buf += __mqtt_pack_str(buf, user_name);
    }
    if (connect_flags & MQTT_CONNECT_PASSWORD) {
        buf += __mqtt_pack_str(buf, password);
    }

    /* return the number of bytes that were consumed */
    return buf - start;
}

struct mqtt_queued_message* mqtt_mq_register(struct mqtt_message_queue *mq, size_t nbytes)
{
    /* make queued message header */
    --(mq->queue_tail);
    mq->queue_tail->start = mq->curr;
    mq->queue_tail->size = nbytes;
    mq->queue_tail->state = MQTT_QUEUED_UNSENT;

    /* move curr and recalculate curr_sz */
    mq->curr += nbytes;
    mq->curr_sz = mqtt_mq_currsz(mq);

    return mq->queue_tail;
}

void mqtt_mq_clean(struct mqtt_message_queue *mq) {
    struct mqtt_queued_message *new_head;

    for(new_head = mqtt_mq_get(mq, 0); new_head >= mq->queue_tail; --new_head) {
        if (new_head->state != MQTT_QUEUED_COMPLETE) break;
    }
    
    /* check if everything can be removed */
    if (new_head < mq->queue_tail) {
        mq->curr = mq->mem_start;
        mq->queue_tail = mq->mem_end;
        mq->curr_sz = mqtt_mq_currsz(mq);
        return;
    } else if (new_head == mqtt_mq_get(mq, 0)) {
        /* do nothing */
        return;
    }

    /* move buffered data */
    {
        size_t n = mq->curr - new_head->start;
        size_t removing = new_head->start - (uint8_t*) mq->mem_start;
        memmove(mq->mem_start, new_head->start, n);
        mq->curr = (unsigned char*)mq->mem_start + n;
      

        /* move queue */
        {
            ssize_t new_tail_idx = new_head - mq->queue_tail;
            memmove(mqtt_mq_get(mq, new_tail_idx), mq->queue_tail, sizeof(struct mqtt_queued_message) * (new_tail_idx + 1));
            mq->queue_tail = mqtt_mq_get(mq, new_tail_idx);
          
            {
                /* bump back start's */
                ssize_t i = 0;
                for(; i < new_tail_idx + 1; ++i) {
                    mqtt_mq_get(mq, i)->start -= removing;
                }
            }
        }
    }

    /* get curr_sz */
    mq->curr_sz = mqtt_mq_currsz(mq);
}
