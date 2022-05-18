//udp bidirectional (client process)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("Usage:%s <port>\n", argv[0]);
        exit(0);
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);

    int sockfd;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        perror("SOCKET ERROR");
        exit(1);
    }

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    bzero(buffer, 1024);
    strcpy(buffer, "This is a message from UPD Client\n");
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
    printf("Data Sent: %s\n", buffer);

    bzero(buffer, 1024);
    addr_size = sizeof(addr);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
    printf("Data received: %s\n", buffer);

    return 0;

}
