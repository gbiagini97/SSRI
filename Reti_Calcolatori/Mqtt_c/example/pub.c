#include <stdio.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <netdb.h> 
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "mqtt.h"

#define MOSQUITTO_ADDR "127.0.0.1"
#define MOSQUITTO_PORT "1883"
#define TOPIC "gbiagini/test"

int open_socket(const char* addr, const char* port);
void repl(struct mqtt_client client, int sockfd, pthread_t *client_daemon);
void exit_example(int status, int sockfd, pthread_t *client_daemon);
void publish_callback();
void* client_refresher(void* client);


int main() 
{
    int sockfd = open_socket(MOSQUITTO_ADDR, MOSQUITTO_PORT);

    if (sockfd == -1) {
        perror("Failed to open socket: ");
        exit_example(EXIT_FAILURE, sockfd, NULL);
    }

    /* setup a client */
    struct mqtt_client client;
    uint8_t sendbuf[2048]; /* sendbuf should be large enough to hold multiple whole mqtt messages */
    uint8_t recvbuf[1024]; /* recvbuf should be large enough any whole mqtt message expected to be received */

    mqtt_init(&client, sockfd, sendbuf, sizeof(sendbuf), recvbuf, sizeof(recvbuf), publish_callback);
    const char* client_id = NULL;
    uint8_t connect_flags = MQTT_CONNECT_CLEAN_SESSION;
    
    mqtt_connect(&client, client_id, NULL, NULL, 0, NULL, NULL, connect_flags, 400);

    /* check that we don't have any errors */
    if (client.error != MQTT_OK) {
        fprintf(stderr, "Error: %s\n", mqtt_error_str(client.error));
        exit_example(EXIT_FAILURE, sockfd, NULL);
    }

    /* start a thread to refresh the client (handle egress and ingree client traffic) */
    pthread_t client_daemon;

    if(pthread_create(&client_daemon, NULL, client_refresher, &client)) {
        fprintf(stderr, "Failed to start client daemon.\n");
        exit_example(EXIT_FAILURE, sockfd, NULL);
    }

    
    //repl(client, sockfd, &client_daemon);
    send_message_example(client, sockfd, &client_daemon);

    exit_example(EXIT_SUCCESS, sockfd, &client_daemon);

}

int open_socket(const char* addr, const char* port) 
{
       
    struct addrinfo hints = {0};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    int sockfd = -1;
    int rv;
    
    struct addrinfo *p, *servinfo;

    /* get address information */
    rv = getaddrinfo(addr, port, &hints, &servinfo);
    if(rv != 0) {
        fprintf(stderr, "Failed to open socket (getaddrinfo): %s\n", gai_strerror(rv));
        return -1;
    }

    /* open the first possible socket */
    for(p = servinfo; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) continue;

        /* connect to server */
        rv = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
        if(rv == -1) continue;
        break;
    }  

    freeaddrinfo(servinfo);
    if (sockfd != -1) fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);

    return sockfd; 
}

void repl(struct mqtt_client client, int sockfd, pthread_t *client_daemon) 
{
    char application_message[256];
    int n;
    for(;;)
    {
        bzero(application_message, sizeof(application_message));
        printf("\nEnter the message (enter 0 to exit): ");
        n = 0;
        while((application_message[n++] = getchar()) != '\n')
            ;
        if((strncmp(application_message, "0", 1)) == 0)
        {
                printf("\nDisconnecting from %s\n", MOSQUITTO_ADDR);
                sleep(1);
                break;
        }

        printf("Sending message: %s", application_message);
        printf("Status: %s\n", mqtt_error_str(mqtt_publish(&client, TOPIC, application_message, strlen(application_message) + 1, MQTT_PUBLISH_QOS_0)));
        
        /* check for errors */
        if (client.error != MQTT_OK) 
        {
            fprintf(stderr, "error: %s\n", mqtt_error_str(client.error));
            exit_example(EXIT_FAILURE, sockfd, client_daemon);
        }
    }
}

void send_message_example(struct mqtt_client client, int sockfd, pthread_t *client_daemon) {
    char application_message[256];
    strcpy(application_message, "Test message from simple method");
    mqtt_publish(&client, TOPIC, application_message, strlen(application_message) + 1, MQTT_PUBLISH_QOS_0);
}

void exit_example(int status, int sockfd, pthread_t *client_daemon)
{
    if (sockfd != -1) close(sockfd);
    if (client_daemon != NULL) pthread_cancel(*client_daemon);
    exit(status);
}


void publish_callback() 
{
    /* not used in this example */
}
void* client_refresher(void* client)
{
    while(1) 
    {
        mqtt_sync((struct mqtt_client*) client);
        usleep(100000U);
    }
    return NULL;
}