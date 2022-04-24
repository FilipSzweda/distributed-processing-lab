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
int userNumber = -1;

void receive_message(SOCKET* connectSocket) {
    while (true) {
        u_long modeNonBlocking = 1;
        ioctlsocket(*connectSocket, FIONBIO, &modeNonBlocking);
        char bufferb[80];
        if (recv(*connectSocket, bufferb, 80, 0) > 0) {
            std::string message (bufferb);
            if (message.length() == 1 && userNumber == -1) {
                userNumber = message[0] - '0';
                std::cout << "You are user number: " << userNumber << "\n";
            }
            else {
                int senderNumber = message[0] - '0';
                message.erase(0, 1);
                std::cout << "User: " << senderNumber << " wrote: " << message << "\n";
            }
        };
        u_long modeBlocking = 0;
        ioctlsocket(*connectSocket, FIONBIO, &modeBlocking);
    }
}

void create_client() {
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
    
    std::thread message_receiver{ receive_message, &connectSocket};

    std::string buffer;
    std::string message;
    std::string receiverNumber;
    while (true) {
        std::cout << "Write message:\n";
        std::cin >> message;
        std::cout << "To user number (if all: 0):\n";
        std::cin >> receiverNumber;

        buffer = receiverNumber + message;
        send(connectSocket, buffer.c_str(), buffer.length() + 1, 0);
    }

    message_receiver.join();

    closesocket(connectSocket);
    WSACleanup();
}

int main() {
    std::thread client{create_client};
    client.join();

    return 0;
}