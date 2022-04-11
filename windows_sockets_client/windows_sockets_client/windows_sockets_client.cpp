#include<io.h>
#include<iostream>
#include<stdio.h>
#include<winsock2.h>
#include <windows.h>

#pragma warning(disable:4996) 

#pragma comment(lib,"ws2_32.lib")

#define ST_PORT 8080

int main() {
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
        printf("\nBlad polaczenia !");
        return 1;
    }

    int dlug;
    char buf[80];
    while(true) {
        fgets(buf, 80, stdin);
        dlug = strlen(buf); buf[dlug - 1] = '\0';
        send(s, buf, dlug, 0);
        if (strcmp(buf, "KONIEC") == 0) break;
    }
    closesocket(s);
    WSACleanup();

    return 0;
}