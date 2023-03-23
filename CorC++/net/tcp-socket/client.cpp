#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

//
//Tencent Cloud Server
//
const char* server_ip = "49.234.24.67";

#define port 8889

int main()
{
    /* init winsock */
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 1), &wsaData))
    {
        printf("winsock init failed\n");
        return 1;
    }

    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);                      /* 服务器监听端口 */
    serverAddr.sin_addr.S_un.S_addr = inet_addr(server_ip);     /* 服务器地址 */

    /* connect to server */
    printf("connecting...\n");

    /* create a tcp socket  */
    SOCKET sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_fd <= 0)
    {
        printf("socket create failed\n");
        return -1;
    }

    int len = sizeof(serverAddr);
    if (connect(sock_fd, (SOCKADDR*)&serverAddr, len) != 0)
    {
        printf("connection failed\n");
        return -1;
    }
    printf("connected\n");


    char buffer[1024];
    while (1)
    {
        printf("send: ");
        fgets(buffer, sizeof(buffer), stdin);

        /* send to server */
        if (send(sock_fd, buffer, sizeof(buffer), 0) <= 0)
        {
            printf("send error\n");
            break;
        }

        if (recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, &len) != SOCKET_ERROR)
        {
            printf("receive: %s", buffer);
        }
    }

    WSACleanup();

    return 0;
}