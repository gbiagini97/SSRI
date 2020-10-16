#include <stdio.h>  //printf, sprintf, fgets, BUFSIZ
#include <stdlib.h> // malloc, exit, atoi
#include <string.h> // stlen, strtok, bzero, strcpy, strcat

#include "params.h"

char *getHost()
{
    char *host;
    host = (char *)malloc(128 * sizeof(char));
    host[0] = '\0';

    printf("Enter host (default httpbin.org): ");
    fgets(host, 128, stdin);
    if (host[0] == '\n')
    {
        strcpy(host, "httpbin.org");
    }
    else
    {
        strtok(host, "\n");
    }
    return host;
}

int getPort()
{
    int port = 80;
    char *portInsert;
    portInsert = (char *)malloc(8 * sizeof(char));
    portInsert[0] = '\0';

    printf("Enter port (default 80): ");
    fgets(portInsert, 5, stdin);
    strtok(portInsert, "\n");
    if (atoi(portInsert) != 0)
    {
        port = atoi(portInsert);
    }
    free(portInsert);
    return port;
}

char *getPath()
{
    char *path;
    path = (char *)malloc(128 * sizeof(char));
    path[0] = '\0';

    printf("Enter path (default /): ");
    fgets(path, 128, stdin);
    if (path[0] == '\n')
    {
        strcpy(path, "/");
    }
    else
    {
        strtok(path, "\n");
    }
    return path;
}

char *getMethod()
{

    char *method;
    method = (char *)malloc(12 * sizeof(char));
    method[0] = '\0';

    printf("Enter method (default GET): ");
    fgets(method, 12, stdin);
    if (method[0] == '\n')
    {
        strcpy(method, "GET");
    }
    else
    {
        strtok(method, "\n");
    }
    return method;
}

char *getHeaders(char *message)
{
    char *headers;
    headers = (char *)malloc(256 * sizeof(char));
    bzero(headers, 256 * sizeof(char));

    for (;;)
    {
        printf(message);
        char header[128];
        fgets(header, 128, stdin);

        if (header[0] != '\n')
        {
            strtok(header, "\n");
            strcat(header, "\r\n");
            strcat(headers, header);
        }
        else
            break;
    }
    return headers;
}

char *getBody()
{
    char *body;
    body = (char *)malloc(512 * sizeof(char));
    bzero(body, 512 * sizeof(char));

    for (;;)
    {
        printf("Enter body (leave blank to finish): ");
        char bodyLine[128];
        fgets(bodyLine, 128, stdin);

        strcat(body, bodyLine);
        if (bodyLine[0] == '\n')
        {
            break;
        }
    }
    return body;
}

char *getEntityHeaders(char *body)
{
    char *entityHeaders;
    entityHeaders = (char *)malloc(512 * sizeof(char));
    entityHeaders[0] = '\0';

    char contentType[64];

    printf("Enter Content-Type: ");
    fgets(contentType, 64, stdin);
    strtok(contentType, "\n");

    sprintf(entityHeaders, "Content-Type: %s\r\nContent-Length: %d\r\n", contentType, (int)strlen(body));

    return entityHeaders;
}
