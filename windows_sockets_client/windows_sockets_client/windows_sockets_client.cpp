#include<io.h>
#include<iostream>
#include<stdio.h>
#include<winsock2.h>
#include <windows.h>
#include <thread>

#pragma warning(disable:4996) 

#pragma comment(lib,"ws2_32.lib")

#define ST_PORT 8080
#define CLIENTS_NUMBER 2

void create_client() {
    SOCKET s;
    struct sockaddr_in sa;
    WSADATA wsas;
    WORD wersja;
    wersja = MAKEWORD(2, 0);
    WSAStartup(wersja, &wsas);
    s = socket(AF_INET, SOCK_STREAM, 0);
    memset((void*)(&sa), 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(ST_PORT);
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");

    int result;
    result = connect(s, (struct sockaddr FAR*) & sa, sizeof(sa));
    if (result == SOCKET_ERROR) {
        printf("Connection error\n");
    }

    int dlug;
    char buf[80];
    while (true) {
        fgets(buf, 80, stdin);
        dlug = strlen(buf); buf[dlug - 1] = '\0';
        send(s, buf, dlug, 0);
        if (strcmp(buf, "quit") == 0) break;
    }
    closesocket(s);
    WSACleanup();
}

int main() {
    std::thread clients[CLIENTS_NUMBER] {std::thread {create_client}, std::thread {create_client}};

    for (int clientNumber = 0; clientNumber < CLIENTS_NUMBER; clientNumber++) {
        clients[clientNumber].join();
    }

    return 0;
}