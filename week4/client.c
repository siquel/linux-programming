#include "config.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h> // atoi
#include <string.h> // memcpy

static uint32_t ipv4(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d)
{
    return (uint32_t)_a | (((uint32_t)_b) << 8) | (((uint32_t)_c) << 16) | (((uint32_t)_d) << 24);
}

static void usage(const char* program_name)
{
    fprintf(stderr, "%s integer1 integer2\n", program_name);
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

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    printf("sending %d and %d\n", a, b);

    char buffer[sizeof(int) * 2];
    memcpy(buffer, &a, sizeof(int));
    memcpy(buffer + sizeof(int), &b, sizeof(int));

    size_t sent_bytes;
    if ((sent_bytes = send(sockfd, buffer, sizeof(buffer), 0)) == -1)
    {
        fprintf(stderr, "send() failed, errno: %d\n", errno);
        return 1;
    }

    char recv_buf[64] = { 0 };

    size_t recv_size;
    if ((recv_size = recv(sockfd, recv_buf, sizeof(recv_buf), 0)) == -1)
    {
        fprintf(stderr, "recv() failed, errno: %d\n", errno);
        return 1;
    }

    int sum = 0, diff = 0, product = 0;
    memcpy(&sum, recv_buf, sizeof(int));
    memcpy(&diff, recv_buf + 4, sizeof(int));
    memcpy(&product, recv_buf + 8, sizeof(int));

    printf("Sum = %d, Diff = %d, Product = %d\n", sum, diff, product);

    return 0;
}
