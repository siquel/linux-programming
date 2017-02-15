#include "config.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

static uint32_t ipv4(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d)
{
    return uint32_t(_a) | (uint32_t(_b) << 8) | (uint32_t(_c) << 16) | (uint32_t(_d) << 24);
}

static void usage(const char* program_name)
{
    fprintf(stderr, "%s integer1 integer2\n");
}

int main(int argc, char* argv[])
{

    if (argc < 3)
    {
        usage(argv[0]);
        return 1;
    }

    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "socket() failed, errno %d\n", errno);
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = ipv4(127, 0, 0, 1);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0)
    {
        fprintf(stderr, "connect() failed, errno %d\n", errno);
        return 1;
    }

    return 0;
}
