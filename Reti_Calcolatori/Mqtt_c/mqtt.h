#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>

#define mqtt_mq_currsz(mq_ptr) (mq_ptr->curr >= (uint8_t *)((mq_ptr)->queue_tail - 1)) ? 0 : ((uint8_t *)((mq_ptr)->queue_tail - 1)) - (mq_ptr)->curr
#define mqtt_mq_get(mq_ptr, index) (((struct mqtt_queued_message*) ((mq_ptr)->mem_end)) - 1 - index)
#define MQTT_PROTOCOL_LEVEL 0x04

#define GENERATE_ENUM(ENUM) ENUM,

#define __ALL_MQTT_ERRORS(MQTT_ERROR)                    \
    MQTT_ERROR(MQTT_ERROR_NULLPTR)                       \
    MQTT_ERROR(MQTT_ERROR_CONTROL_FORBIDDEN_TYPE)        \
    MQTT_ERROR(MQTT_ERROR_CONTROL_INVALID_FLAGS)         \
    MQTT_ERROR(MQTT_ERROR_CONTROL_WRONG_TYPE)            \
    MQTT_ERROR(MQTT_ERROR_CONNECT_CLIENT_ID_REFUSED)     \
    MQTT_ERROR(MQTT_ERROR_CONNECT_NULL_WILL_MESSAGE)     \
    MQTT_ERROR(MQTT_ERROR_CONNECT_FORBIDDEN_WILL_QOS)    \
    MQTT_ERROR(MQTT_ERROR_CONNACK_FORBIDDEN_FLAGS)       \
    MQTT_ERROR(MQTT_ERROR_CONNACK_FORBIDDEN_CODE)        \
    MQTT_ERROR(MQTT_ERROR_PUBLISH_FORBIDDEN_QOS)         \
    MQTT_ERROR(MQTT_ERROR_SUBSCRIBE_TOO_MANY_TOPICS)     \
    MQTT_ERROR(MQTT_ERROR_MALFORMED_RESPONSE)            \
    MQTT_ERROR(MQTT_ERROR_UNSUBSCRIBE_TOO_MANY_TOPICS)   \
    MQTT_ERROR(MQTT_ERROR_RESPONSE_INVALID_CONTROL_TYPE) \
    MQTT_ERROR(MQTT_ERROR_CONNECT_NOT_CALLED)            \
    MQTT_ERROR(MQTT_ERROR_SEND_BUFFER_IS_FULL)           \
    MQTT_ERROR(MQTT_ERROR_SOCKET_ERROR)                  \
    MQTT_ERROR(MQTT_ERROR_MALFORMED_REQUEST)             \
    MQTT_ERROR(MQTT_ERROR_RECV_BUFFER_TOO_SMALL)         \
    MQTT_ERROR(MQTT_ERROR_ACK_OF_UNKNOWN)                \
    MQTT_ERROR(MQTT_ERROR_NOT_IMPLEMENTED)               \
    MQTT_ERROR(MQTT_ERROR_CONNECTION_REFUSED)            \
    MQTT_ERROR(MQTT_ERROR_SUBSCRIBE_FAILED)              \
    MQTT_ERROR(MQTT_ERROR_CONNECTION_CLOSED)             \
    MQTT_ERROR(MQTT_ERROR_INITIAL_RECONNECT)             \
    MQTT_ERROR(MQTT_ERROR_INVALID_REMAINING_LENGTH)      \
    MQTT_ERROR(MQTT_ERROR_CLEAN_SESSION_IS_REQUIRED)     \
    MQTT_ERROR(MQTT_ERROR_RECONNECTING)

struct mqtt_client
{
    int socketfd;
    uint16_t pid_lfsr;
    uint16_t keep_alive;
    int number_of_keep_alives;
    size_t send_offset;
    time_t time_of_last_send;
    enum MQTTErrors error;
    int response_timeout;
    int number_of_timeouts;
    double typical_response_time;
    void (*publish_response_callback)(void **state, struct mqtt_response_publish *publish);
    void *publish_response_callback_state;
    enum MQTTErrors (*inspector_callback)(struct mqtt_client *);
    void (*reconnect_callback)(struct mqtt_client *, void **);
    void *reconnect_state;
    struct
    {
        uint8_t *mem_start;
        size_t mem_size;
        uint8_t *curr;
        size_t curr_sz;
    } recv_buffer;
    pthread_mutex_t mutex;
    struct mqtt_message_queue mq;
};

enum MQTTErrors
{
    MQTT_ERROR_UNKNOWN = INT_MIN,
    __ALL_MQTT_ERRORS(GENERATE_ENUM)
        MQTT_OK = 1
};

struct mqtt_message_queue
{
    void *mem_start;
    void *mem_end;
    uint8_t *curr;
    size_t curr_sz;
    struct mqtt_queued_message *queue_tail;
};

struct mqtt_queued_message
{
    uint8_t *start;
    size_t size;
    enum MQTTQueuedMessageState state;
    time_t time_sent;
    enum MQTTControlPacketType control_type;
    uint16_t packet_id;
};

enum MQTTQueuedMessageState
{
    MQTT_QUEUED_UNSENT,
    MQTT_QUEUED_AWAITING_ACK,
    MQTT_QUEUED_COMPLETE
};

enum MQTTControlPacketType
{
    MQTT_CONTROL_CONNECT = 1u,
    MQTT_CONTROL_CONNACK = 2u,
    MQTT_CONTROL_PUBLISH = 3u,
    MQTT_CONTROL_PUBACK = 4u,
    MQTT_CONTROL_PUBREC = 5u,
    MQTT_CONTROL_PUBREL = 6u,
    MQTT_CONTROL_PUBCOMP = 7u,
    MQTT_CONTROL_SUBSCRIBE = 8u,
    MQTT_CONTROL_SUBACK = 9u,
    MQTT_CONTROL_UNSUBSCRIBE = 10u,
    MQTT_CONTROL_UNSUBACK = 11u,
    MQTT_CONTROL_PINGREQ = 12u,
    MQTT_CONTROL_PINGRESP = 13u,
    MQTT_CONTROL_DISCONNECT = 14u
};

enum MQTTConnectFlags {
    MQTT_CONNECT_RESERVED = 1u,
    MQTT_CONNECT_CLEAN_SESSION = 2u,
    MQTT_CONNECT_WILL_FLAG = 4u,
    MQTT_CONNECT_WILL_QOS_0 = (0u & 0x03) << 3,
    MQTT_CONNECT_WILL_QOS_1 = (1u & 0x03) << 3,
    MQTT_CONNECT_WILL_QOS_2 = (2u & 0x03) << 3,
    MQTT_CONNECT_WILL_RETAIN = 32u,
    MQTT_CONNECT_PASSWORD = 64u,
    MQTT_CONNECT_USER_NAME = 128u
};

struct mqtt_response_publish
{
    uint8_t dup_flag;
    uint8_t qos_level;
    uint8_t retain_flag;
    uint16_t topic_name_size;
    const void *topic_name;
    uint16_t packet_id;
    const void *application_message;
    size_t application_message_size;
};

struct mqtt_fixed_header 
{
    enum MQTTControlPacketType control_type;
    uint32_t control_flags: 4;
    uint32_t remaining_length;
};

enum MQTTErrors mqtt_init(struct mqtt_client *client,
                          int sockfd,
                          uint8_t *sendbuf, size_t sendbufsz,
                          uint8_t *recvbuf, size_t recvbufsz,
                          void (*publish_response_callback)(void **state, struct mqtt_response_publish *publish));

void mqtt_mq_init(struct mqtt_message_queue *mq, void *buf, size_t bufsz);

enum MQTTErrors mqtt_connect(struct mqtt_client *client,
                             const char *client_id,
                             const char *will_topic,
                             const void *will_message,
                             size_t will_message_size,
                             const char *user_name,
                             const char *password,
                             uint8_t connect_flags,
                             uint16_t keep_alive);

ssize_t mqtt_pack_connection_request(uint8_t *buf, size_t bufsz,
                                     const char *client_id,
                                     const char *will_topic,
                                     const void *will_message,
                                     size_t will_message_size,
                                     const char *user_name,
                                     const char *password,
                                     uint8_t connect_flags,
                                     uint16_t keep_alive);