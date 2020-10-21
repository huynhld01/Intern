#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define RED          0x1
#define GREEN        0x2
#define WHITE        0x17

#define RESETATTR    0
#define BRIGHT       1
#define DIM          2
#define UNDERSCORE   4
#define BLINK        5           
#define REVERSE      7
#define HIDDEN       8

#define __set_gm(attr,color,val)                                        \
        if (!color)                                                     \
            printf("\e[%dm", attr);                                     \
        else                                                            \
            printf("\e[%d;%dm", color & 0x10 ? 1 : 0, (color & 0xF) + val)


#define textcolor(color)      __set_gm(RESETATTR, color, 30)

#define PORT 2020

void main()
{
    struct sockaddr_in client,server;
    int sockfd, n;
    char buffer[100];

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd < 0)
    {
        textcolor(RED);
        perror("Error opening socket");
	exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    //server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_addr.s_addr = INADDR_ANY;

    textcolor(GREEN);
    printf("Client ready...\n\n");
    n = sizeof(server);

    while(1)
    {
        textcolor(WHITE);
        printf("Client: ");
        memset(buffer, '0', 100);
        gets(buffer);
        sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &server, n);
        if(strcmp(buffer, "end") == 0)
            break;
        recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        printf("Server: %s\n", buffer);
    }
    shutdown(sockfd, SHUT_RDWR);
}
