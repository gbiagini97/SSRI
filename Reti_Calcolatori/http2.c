#include <stdio.h> //printf, sprintf, fgets, BUFSIZ
#include <stdlib.h> // malloc, exit, atoi
#include <string.h> // stlen, strtok, bzero, strcpy, strcat
#include <unistd.h> // write, read, close
#include <netdb.h> // gethostbyname
#include <arpa/inet.h> // inet_addr, inet_ntoa

char *getHost();
int getPort();
char *getPath();
char *getMethod();
char *getHeaders(char *message);
char *getBody();

int main()
{
    // Variables for request creation
    char requestLine[1024];
    int requestLen;

    // Variables for socket creation and connection
    int sockfd;
    struct sockaddr_in servaddr;
    struct hostent *hostent;
    in_addr_t in_addr;

    // Variables for sending HTTP request
    ssize_t bytes, lastByte;

    // Variable for reading HTTP response
    char buf[BUFSIZ];

    // Input Variables for request creation
    char *method = getMethod();
    char *host = getHost();
    int port = getPort();
    char *path = getPath();
    char *generalHeaders = getHeaders("Enter general header (leave blank to finish): ");
    char *requestHeaders = getHeaders("Enter request header (leave blank to finish): ");
    char *body = getBody();
    char entityHeaders[512];

    // Check if body is present to add proper headers
    if (strlen(body) > 1)
    {
        char contentType[64];
        printf("Enter Content-Type: ");
        fgets(contentType, 64, stdin);
        strtok(contentType, "\n");
        sprintf(entityHeaders, "Content-Type: %s\r\nContent-Length: %d\r\n", contentType,(int)strlen(body));
    }

    // Build request and retrieve the size
    requestLen = sprintf(requestLine, "%s %s HTTP/1.1\r\nHost: %s:%d\r\n%s%s%s\r\n%s", method, path, host, port, generalHeaders, requestHeaders, entityHeaders, body);
    printf("\nRequest:\n%s", requestLine);


    // Build the Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket creation failed..\n");
        exit(1);
    }
    else
        printf("Socket successfully created..\n");

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
    in_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));
    if (in_addr == (in_addr_t)-1) {
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

    // Send HTTP request
    bytes = 0;
    while(bytes < requestLen)
    {
        lastByte = write(sockfd, requestLine + bytes, requestLen - bytes);
        if (lastByte == -1)
        {
            printf("Error while sending HTTP request..\n");
            exit(1);
        }
        bytes += lastByte;
    }

    // Read HTTP response
    printf("\nResponse:\n");
    while((bytes = read(sockfd, buf, BUFSIZ)) > 0)
    {
        write(1, buf, bytes);
    }

    printf("Do you want to make a new request? (y/n)");
    char newReq = getchar();
    if(newReq == 'y') {
        bzero(&method, sizeof(method));
        bzero(&path, sizeof(path));
        bzero(&host, sizeof(host));
        bzero(&port, sizeof(port));
        bzero(&generalHeaders, sizeof(generalHeaders));
        bzero(&requestHeaders, sizeof(requestHeaders));
        bzero(&entityHeaders, sizeof(entityHeaders));
        bzero(&body, sizeof(body));
        
        main();
    } else
    {
        // Close socket and terminate program
        close(sockfd);
        exit(0);    
    }
}


char *getHost()
{
    char *host;
    host = (char*) malloc(128 * sizeof(char));
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
    portInsert = (char*) malloc(8 * sizeof(char));
    portInsert[0] = '\0';

    printf("Enter port (default 80): ");
    fgets(portInsert, 5, stdin);
    strtok(portInsert, "\n");
    if (atoi(portInsert) != 0)
    {
        port = atoi(portInsert);
    }
    return port;
}

char *getPath()
{
    char *path;
    path = (char*) malloc(128 * sizeof(char));
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
    method = (char*) malloc(12 * sizeof(char));
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
    headers = (char*) malloc(256 * sizeof(char));

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
    body = (char*) malloc(512 * sizeof(char));

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
