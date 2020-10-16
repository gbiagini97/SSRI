#include <stdio.h>     //printf, sprintf, fgets, BUFSIZ
#include <stdlib.h>    // malloc, exit, atoi
#include <string.h>    // stlen, strtok, bzero, strcpy, strcat
#include <unistd.h>    // write, read, close
#include <netdb.h>     // gethostbyname
#include <arpa/inet.h> // inet_addr, inet_ntoa

#include "params.h"
#include "http.h"

int initSocket();
void configureSocket(int sockfd, char *host, int port);
void repl(int sockfd, char *host, int port);

int main()
{
    char *host = getHost();
    int port = getPort();

    int sockfd = initSocket();

    configureSocket(sockfd, host, port);
    execute(sockfd, buildRequest(host, port));

    repl(sockfd, host, port);

    // Close socket and terminate program
    close(sockfd);
    exit(0);
}

void repl(int sockfd, char *host, int port)
{
    char *newReq;
    newReq = (char *)malloc(12 * sizeof(char));
    newReq[0] = '\0';

    printf("Do you want to make a new request? (y/n) ");
    fgets(newReq, 12, stdin);
    strtok(newReq, "\n");
    if (strcmp(newReq, "y") == 0)
    {

        char *sameConf;
        sameConf = (char *)malloc(12 * sizeof(char));
        sameConf[0] = '\0';
        printf("Do you want to send another request to %s:%d? (y/n) ", host, port);
        fgets(sameConf, 12, stdin);
        strtok(sameConf, "\n");

        if (strcmp(sameConf, "y") == 0)
        {
            printf("Using same socket configuration..\n");
            char *requestLine = buildRequest(host, port);
            execute(sockfd, requestLine);

            repl(sockfd, host, port);
        }
        else
        {

            free(host);
            close(sockfd);

            host = getHost();
            port = getPort();

            printf("Initializing new socket..\n");
            sockfd = initSocket();
            configureSocket(sockfd, host, port);

            char *requestLine = buildRequest(host, port);
            execute(sockfd, requestLine);

            repl(sockfd, host, port);
        }

        free(newReq);
        free(sameConf);
    }
}

int initSocket()
{
    // Variables for socket creation and connection
    int sockfd;

    // Build the Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket creation failed..\n");
        exit(1);
    }
    else
        printf("Socket successfully created..\n");

    return sockfd;
}

void configureSocket(int sockfd, char *host, int port)
{
    struct sockaddr_in servaddr;
    struct hostent *hostent;
    in_addr_t in_addr;

    // Copy n zero values from sizeof(servaddr) in servaddr
    bzero(&servaddr, sizeof(servaddr));

    // Retrieve host information from a host database
    hostent = gethostbyname(host);
    if (hostent == NULL)
    {
        printf("Host resolution failed..\n");
        exit(1);
    }
    else
        printf("Host resolution done..\n");

    // Build address
    // inet_ntoa = converts long to decimal
    // inet_addr = converts decimals that represents an IP address to long
    in_addr = inet_addr(inet_ntoa(*(struct in_addr *)*(hostent->h_addr_list)));
    if (in_addr == (in_addr_t)-1)
    {
        printf("Address build failed..\n");
        exit(1);
    }
    else
        printf("Address built..\n");

    // Assign address and port
    // Endianness matters!
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = in_addr;
    servaddr.sin_port = htons(port);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Connection with the server failed..\n");
        exit(1);
    }
    else
        printf("Connected to the server..\n");
}