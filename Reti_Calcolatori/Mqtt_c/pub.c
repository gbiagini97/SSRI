#include "open_socket.c"
#include "mqtt.h"

#define MOSQUITTO_ADDR "test.mosquitto.org"
#define MOSQUITTO_PORT "1883"

int main(int argc, const char *argv[]) {

    int sockfd = open_nb_socket(MOSQUITTO_ADDR, MOSQUITTO_PORT);

    if (sockfd == -1) {
        perror("Failed to open socket");
    }

    struct mqtt_client client;
    uint8_t sendbuf[2048];
    uint8_t recvbuf[1024];

    
}