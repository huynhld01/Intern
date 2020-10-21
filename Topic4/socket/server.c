#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>


int main(int argc, char **argv)
{
    int sockfd; /* socket server to listen connect */
    int newsockfd; /* socket created when server accept connect */
    int portno; /* port no */

    char sendbuff[256];
    char readbuff[256];

    struct sockaddr_in serv_addr, client_addr; /* struct about info server, client */
    int n, len;

    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    portno = atoi(argv[1]);

    /* init memmory */
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(&client_addr, '0', sizeof(client_addr));
    memset(sendbuff, '0', 256);

    /* config server address */
    serv_addr.sin_family = AF_INET; /* default */
    serv_addr.sin_addr.s_addr = INADDR_ANY; /* ip server */
    serv_addr.sin_port = htons(portno); /* port number */

    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    /* bind socket */
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error ("ERROR openning socket");

    /* listening */
    listen(sockfd, 5); /* maximum 5 backlog in queue */
    len = sizeof(client_addr); /* get info address client conneted*/

    /* alway listing */
            printf("server is listening at port %d\n", portno);
        newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *)&len);
        if (newsockfd < 0)
        {
            error("ERROR on accept");
        }
    while (1)
    {

        char s[255]; /* get info client conneted */
        inet_ntop(client_addr.sin_family, (struct sockaddr*)&client_addr, s, sizeof(s));
        printf("server: got connect from %s\n", s);
        memset(readbuff, 0, 256);
        /* read data from socket */
        n = read(newsockfd, readbuff, 255); /* block until client send data */
        if (n < 0) error("ERROR reading from socket");
            printf("Client: %s\n", readbuff);
        
        if (strcmp(readbuff, "end") != 0)
            break;

        /* write data via socket */
        //strcpy(sendbuff, "Server has got message\n");
        strcpy(sendbuff, "Client: \n");
        fgets(sendbuff, 255, stdin);
        n = write(newsockfd,sendbuff,sizeof(sendbuff));
        if (n < 0) error("ERROR writing to socket");
      
        //close(newsockfd);    // diconnect client
        sleep(1);
    }
    close(sockfd);
    return 0;
}