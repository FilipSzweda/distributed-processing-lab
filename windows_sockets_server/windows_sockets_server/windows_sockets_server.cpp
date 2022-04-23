#include<io.h>
#include<iostream>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

#define ST_PORT 8080

int main() {
    WSADATA wsas;
    int result;
    WORD wersja;
    wersja = MAKEWORD(1, 1);
    result = WSAStartup(wersja, &wsas);
    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sa;
    memset((void*)(&sa), 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(ST_PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    result = bind(s, (struct sockaddr FAR*) & sa, sizeof(sa));
    result = listen(s, 5);

    SOCKET si[2];
    struct sockaddr_in sc;
    int lenc;
    while(true) {
        lenc = sizeof(sc);
        for (int i = 0; i < 2; i++) {
            si[i] = accept(s, (struct sockaddr FAR*) & sc, &lenc);
        }
        
        while (true) {
            for (int i = 0; i < 2; i++) {
                char buf[80];
                if (recv(si[i], buf, 80, 0) > 0) {
                    if (strcmp(buf, "quit") == 0) {
                        closesocket(si[i]);
                        WSACleanup();
                        return 0;
                    }
                    printf("%s\n", buf);
                };
            }
        }

        
    }

    return 0;
}