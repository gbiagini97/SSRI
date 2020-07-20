#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

void func(int sockfd) {
    char buff[MAX];
    int n;

    // REPL
    for(;;) {
        bzero(buff, MAX);

        // Read message from client and copy in the buffer
        read(sockfd, buff, sizeof(buff));

        // Print the buffer
        printf("From client: %s\t To client: ", buff);

        // Copy server message to buffer
        bzero(buff, MAX);
        n = 0;
        while((buff[n++] = getchar()) != '\n') {
           ; 
        }
        
        // Send message in the buffer to the client
        write(sockfd, buff, sizeof(buff));

        if(strncmp("exit", buff, 4) == 0) {
            printf("Server exit\n");
            break;
        }
    }
}


int main() {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // Socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        exit(0);
    }
    else {
        printf("Socket successfully created\n");
    }

    bzero(&servaddr, sizeof(servaddr));

    // Assign IP and PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Socket binding to given IP
    if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed\n");
        exit(0);
    }
    else {
        printf("Socket successfully binded\n");
    }

    // Setup server in listening mode
    if((listen(sockfd, 5)) != 0) {
        printf("Listen failed\n");
        exit(0);
    }
    else {
        printf("Server listening\n");
    }
    len = sizeof(cli);

    // Accept data from client
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0 ) {
        printf("Server accept failed\n");
        exit(0);
    }
    else {
        printf("Server accept the client\n");
    }

    func(connfd);

    close(sockfd);

}