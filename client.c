#define _DEFAULT_SOURCE

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>   // inet_ntoa
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>      // close

const char* data[] = {
    "Hello server!",
    "and",
    "some",
    "other",
    "messages"
};

int main()
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("socket()");
        return 1;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port   = htons(12345);
    if (inet_aton("127.0.0.1", &serverAddr.sin_addr) != 1)
    {
        fprintf(stderr, "inet_aton() failed\n");
        return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("Sending \"%s\"\n", data[i]);
        if (sendto(fd, data[i], strlen(data[i]), 0,
                   (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0)
        {
            perror("sendto()");
            return 1;
        }
    }
}
