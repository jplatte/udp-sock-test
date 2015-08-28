#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>   // inet_ntoa
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>      // close

int main()
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("socket()");
        return 1;
    }

    struct sockaddr_in localAddr;
    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family      = AF_INET;
    localAddr.sin_port        = htons(12345);
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(fd, (struct sockaddr*) &localAddr, sizeof(localAddr)) != 0)
    {
        perror("bind()");
        return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        struct sockaddr_in addr;
        socklen_t addrLen;
        char buf[512];

        ssize_t bytesRecvd =
            recvfrom(fd, buf, 512, 0, (struct sockaddr*) &addr, &addrLen);

        if (bytesRecvd < 0)
        {
            perror("recvfrom()");
            return 1;
        }

        buf[bytesRecvd] = '\0';
        printf("Received \"%s\" from %s:%u\n",
               buf, inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    }

    close(fd);
}
