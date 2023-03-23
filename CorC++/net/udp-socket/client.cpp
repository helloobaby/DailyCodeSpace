﻿#define _CRT_SECURE_NO_WARNINGS
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

//
//https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-sendto
//
int main()
{

    int iResult;
    WSADATA wsaData;

    SOCKET SendSocket = INVALID_SOCKET;
    sockaddr_in RecvAddr;

    int recvLen = sizeof(sockaddr);
    unsigned short Port = port;

    char SendBuf[1024];
    memcpy(SendBuf,"[Windows]hello server,I'm client\n",34);
    int BufLen = 1024;

    //----------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    //---------------------------------------------
    // Create a socket for sending data
    SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (SendSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //---------------------------------------------
    // Set up the RecvAddr structure with the IP address of
    // the receiver (in this example case "192.168.1.1")
    // and the specified port number.
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = inet_addr(server_ip);

    //---------------------------------------------
    // Send a datagram to the receiver
    wprintf(L"Sending a datagram to the receiver...\n");
    iResult = sendto(SendSocket,
        SendBuf, BufLen, 0, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(SendSocket);
        WSACleanup();
        return 1;
    }

    if(recvfrom(SendSocket,SendBuf,BufLen,0, (SOCKADDR*)&RecvAddr,&recvLen) == SOCKET_ERROR)
    {
        printf("WSAERROR %d",WSAGetLastError());
        closesocket(SendSocket);
        WSACleanup();
        return 1;
    }
    
    fputs(SendBuf,stdout);
    //---------------------------------------------
    // When the application is finished sending, close the socket.
    wprintf(L"Finished sending and recving. Closing socket.\n");
    iResult = closesocket(SendSocket);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"closesocket failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //---------------------------------------------
    // Clean up and quit.
    wprintf(L"Exiting.\n");
    WSACleanup();
    return 0;
}