#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

int main(int argc, char **argv)
{
    int client_len;
    int client_sockfd;
    struct sockaddr_in clientaddr;

    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientaddr.sin_port = htons(5558);

    client_len = sizeof(clientaddr);

    if (connect(client_sockfd, (struct sockaddr *)&clientaddr, client_len) < 0) {
        perror("Connect error: ");
        exit(0);
    }

    std::string snd_msg = argv[1];
    for (int i = 0; i < 10; i++) {
        char rcv_buf[256];
        write(client_sockfd, snd_msg.c_str(), snd_msg.size());
        int size = read(client_sockfd, rcv_buf, 255);
        rcv_buf[size] = '\0';
        printf("%d %s\n", i, rcv_buf);
    }

    close(client_sockfd);
    return 0;
}
