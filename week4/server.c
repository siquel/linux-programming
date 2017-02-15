#include <sys/types.h>
#include <sys/socket.h>
#include <string.h> // memset
#include <stdio.h> // fprintf
#include <arpa/inet.h> // htons
#include <errno.h> // errno
#include "config.h"

int main()
{
    struct sockaddr_in server_addr, client_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "socket() failed, errno: %d\n", errno);
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        fprintf(stderr, "bind() failed, errno: %d\n", errno);
        return 1;
    }
            
    if (listen(sockfd, 1) == -1)
    {
        fprintf(stderr, "listen() failed, errno: %d\n", errno);
        return 1;
    }

    fprintf(stdout, "Started math server on port %d, waiting for connections...\n", SERVER_PORT);

    while (1)
    {
        int addr_len = sizeof(struct sockaddr_in);
        int clientfd = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)&addr_len);

        if (clientfd < 0)
        {
            fprintf(stderr, "accept() failed, errno: %d\n", errno);
            return 1;
        }
        char buffer[256] = { 0 };
        
        int read_bytes = recv(clientfd, buffer, sizeof(buffer), 0);

        if (read_bytes > 0)
        {
            fprintf(stdout, "Got message: %s\n", buffer);
        }
    }

    return 0;

    return 0;
}
