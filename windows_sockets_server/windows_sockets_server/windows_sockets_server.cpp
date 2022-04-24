#include <io.h>
#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

#define ST_PORT 8080
#define CLIENTS_NUMBER 2

int main() {
    WSADATA wsas;
    WORD version;
    version = MAKEWORD(1, 1);
    if (int result = WSAStartup(version, &wsas)) {
        std::cout << "Winsock loading error\n";
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sa;
    memset((void*)(&sa), 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(ST_PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (int result = bind(listenSocket, (struct sockaddr FAR*) &sa, sizeof(sa))) {
        std::cout << "Binding error\n";
    }

    if (int result = listen(listenSocket, 5)) {
        std::cout << "Listening error\n";
    }

    SOCKET clientSockets[CLIENTS_NUMBER];
    struct sockaddr_in sc;
    int lenc;
    while(true) {
        lenc = sizeof(sc);
        for (int i = 0; i < CLIENTS_NUMBER; i++) {
            clientSockets[i] = accept(listenSocket, (struct sockaddr FAR*) &sc, &lenc);
            std::string userNumber = std::to_string(i + 1);
            send(clientSockets[i], userNumber.c_str(), userNumber.length() + 1, 0);
        }
        
        while (true) {
            for (int i = 0; i < CLIENTS_NUMBER; i++) {
                char buffer[80];
                if (recv(clientSockets[i], buffer, 80, 0) > 0) {
                    int receiverNumber = buffer[0] - '0';

                    std::string message(buffer);
                    message.erase(0, 1);
                    message.insert(0, std::to_string(i + 1));

                    if (receiverNumber == 0) {
                        for (int j = 0; j < CLIENTS_NUMBER; j++) {
                            if (j != i) {
                                send(clientSockets[j], message.c_str(), message.length() + 1, 0);
                            }
                        }
                        std::cout << "Sent messsage: '" << message << "' From: " << i + 1 << " To: all\n";
                    }
                    else {
                        send(clientSockets[receiverNumber - 1], message.c_str(), message.length() + 1, 0);
                        std::cout << "Sent messsage: '" << message << "' From: " << i + 1 << " To user number: " << receiverNumber << "\n";
                    }
                };
            }
        }
    }

    return 0;
}