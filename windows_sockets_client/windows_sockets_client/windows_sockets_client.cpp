#include <io.h>
#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <thread>
#include <mutex>
#include <string>

#pragma warning(disable:4996) 

#pragma comment(lib,"ws2_32.lib")

#define ST_PORT 8080
#define CLIENTS_NUMBER 3

std::mutex mtx;

void create_client(std::string userNumber) {
    WSADATA wsas;
    WORD version;
    version = MAKEWORD(2, 0);
    if (int result = WSAStartup(version, &wsas)) {
        std::cout << "Winsock loading error\n";
    }

    SOCKET connectSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in clientAddress;
    memset((void*)(&clientAddress), 0, sizeof(clientAddress));
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_port = htons(ST_PORT);
    clientAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (int result = connect(connectSocket, (struct sockaddr FAR*) &clientAddress, sizeof(clientAddress)) == SOCKET_ERROR) {
        std::cout << "Connection error\n";
    }
    
    std::string buffer;
    std::string message;
    std::string receiverNumber;
    while (true) {
        // DWORD recvCount = 0;
        // ioctlsocket(connectSocket, FIONREAD, &recvCount);
        unsigned long iMode = 1;
        ioctlsocket(connectSocket, FIONBIO, &iMode);
        char bufferb[80];
        if (recv(connectSocket, bufferb, 80, 0) > 0) { // recvCount > 0 && 
            std::cout << "[User number: " << userNumber << "] Received message:" << bufferb << "\n";
        };

        mtx.lock();
        std::cout << "[User number: " << userNumber << "] Message:\n";
        std::cin >> message;
        std::cout << "[User number: " << userNumber << "] Receiver (if everyone: 0):\n";
        std::cin >> receiverNumber;
        mtx.unlock();

        buffer = userNumber + receiverNumber + message;
        send(connectSocket, buffer.c_str(), buffer.length() + 1, 0);
    }

    closesocket(connectSocket);
    WSACleanup();
}

int main() {
    std::thread clients[CLIENTS_NUMBER];

    for (int clientNumber = 0; clientNumber < CLIENTS_NUMBER; clientNumber++) {
        clients[clientNumber] = std::thread{ create_client, std::to_string(clientNumber + 1) };
    }

    for (int clientNumber = 0; clientNumber < CLIENTS_NUMBER; clientNumber++) {
        clients[clientNumber].join();
    }

    return 0;
}