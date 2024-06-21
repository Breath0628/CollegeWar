#pragma once

#define WIN32_LEAN_AND_MEAN
#include <queue>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include "client.h"
#include <iostream>
#include <thread>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 1024
using namespace std;


class Client
{
private:
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL, * ptr = NULL, hints;
    char sendbuf[1024];
    char recvbuf[1024];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    bool isOpen = 0;
public:
    queue<char*> DataQueue;
    thread DataQueueThread;
public:
    Client(const char* ServerIp, const char* ServerPort)
    {  // 初始化winsocket
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        //写入连接地址和端口
        iResult = getaddrinfo(ServerIp, ServerPort, &hints, &result);
        if (iResult != 0) {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
        }
       
    }

    ~Client() = default;
    int ConnectServer() {
        ptr = result;
        // 创建连接套接字
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
        }
        for (int i = 0; i < 3;i++) {
            // 连接服务器 最大重连3次
            iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                closesocket(ConnectSocket);
                ConnectSocket = INVALID_SOCKET;
                continue;
            }
            break;
        }
        if (ConnectSocket == INVALID_SOCKET) {
            printf("Unable to connect to server!\n");
            WSACleanup();
        }
        StartDataQueue();
        DataQueueThread.detach();
        isOpen = 1;
        return iResult;
    }

    int SendData(const char* sendbuf) {
        //发送字符串数据 成功返回0 失败返回-1
        for (size_t i = 0; i < 3; i++)
        {
            //最大重发三次
            iResult = send(ConnectSocket, sendbuf, 1024, 0);
            if (iResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                WSACleanup();
                continue;
            }
            break;
        }
        return iResult;

    }
    int ReceveData(char* recvbuf) {
        // Receive until the Server closes the connection

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult == 0) {
            CloseConnect();
            printf("Connection closed\n");
        }
        else if (iResult < 0) {
            printf("recv failed with error: %d\n", WSAGetLastError());
        }


        return iResult;

    }
    void StartDataQueue() {
        DataQueueThread = thread([&]() {
            while (isOpen)
            {
                iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
                if (iResult > 0)
                {
                    DataQueue.push(recvbuf);
                    printf("数据队列获取到数据!\n");
                }
            }
            }
        );
    }
    void CloseConnect() {
        // cleanup
        closesocket(ConnectSocket);
        WSACleanup();
        isOpen = 0;
    }

private:

};

