#include<io.h>
#include<iostream>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

#define ST_PORT 8080
#define CLIENTS_NUMBER 3

int main() {
    WSADATA wsas;
    WORD version;
    version = MAKEWORD(1, 1);
    if (int result = WSAStartup(version, &wsas)) {
        std::cout << "Winsock loading error\n";
    }

    int result;

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sa;
    memset((void*)(&sa), 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(ST_PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (int result = bind(serverSocket, (struct sockaddr FAR*) & sa, sizeof(sa))) {
        std::cout << "Binding error\n";
    }

    if (int result = listen(serverSocket, 5)) {
        std::cout << "Listening error\n";
    }

    SOCKET si[CLIENTS_NUMBER];
    struct sockaddr_in sc;
    int lenc;
    while(true) {
        lenc = sizeof(sc);
        for (int i = 0; i < CLIENTS_NUMBER; i++) {
            si[i] = accept(serverSocket, (struct sockaddr FAR*) & sc, &lenc);
        }
        
        while (true) {
            for (int i = 0; i < CLIENTS_NUMBER; i++) {
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