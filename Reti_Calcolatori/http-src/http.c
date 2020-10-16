#include <stdio.h>  //printf, sprintf, fgets, BUFSIZ
#include <stdlib.h> // malloc, exit, atoi
#include <string.h> // stlen, strtok, bzero, strcpy, strcat
#include <unistd.h> // write, read, close

#include "http.h"
#include "params.h"

char *buildRequest(char *host, int port)
{
    // Variables for request creation
    char *requestLine;
    requestLine = (char *)malloc(1024 * sizeof(char));
    requestLine[0] = '\0';

    char *method = getMethod();
    char *path = getPath();
    char *generalHeaders = getHeaders("Enter general header (leave blank to finish): ");
    char *requestHeaders = getHeaders("Enter request header (leave blank to finish): ");
    char *body = getBody();
    char *entityHeaders;

    // Check if body is present to add proper headers
    if (strlen(body) > 1)
    {
        entityHeaders = getEntityHeaders(body);
        sprintf(requestLine, "%s %s HTTP/1.1\r\nHost: %s:%d\r\n%s%s%s\r\n%s", method, path, host, port, generalHeaders, requestHeaders, entityHeaders, body);

        free(entityHeaders);
        free(body);
    }
    else
    {
        sprintf(requestLine, "%s %s HTTP/1.1\r\nHost: %s:%d\r\n%s%s\r\n", method, path, host, port, generalHeaders, requestHeaders);
    }

    // Build request and retrieve the size
    printf("\nRequest:\n%s", requestLine);

    free(method);
    free(path);
    free(generalHeaders);
    free(requestHeaders);

    return requestLine;
}

void execute(int sockfd, char *requestLine)
{

    // Variables for sending HTTP request
    ssize_t bytes, lastByte;
    int requestLen = strlen(requestLine);

    // Variable for reading HTTP response
    char response[4096];
    int responseLen;

    // Send HTTP request
    bytes = 0;
    while (bytes < requestLen)
    {
        lastByte = write(sockfd, requestLine + bytes, requestLen - bytes);
        if (lastByte < 0)
        {
            printf("Error while sending HTTP request..\n");
            exit(1);
        }
        if (lastByte == 0)
            break;

        bytes += lastByte;
    }

    // Read HTTP response
    memset(response, 0, sizeof(response));
    responseLen = sizeof(response) - 1;
    int received = 0;
    while (received < responseLen)
    {
        bytes = read(sockfd, response + received, responseLen - received);
        if (bytes < 0)
        {
            printf("Error while reading HTTP response..\n");
            exit(1);
        }
        if (bytes == 0)
            break;

        received += bytes;
    }

    printf("Response:\n%s\n", response);
    free(requestLine);
}