

#include <ws2tcpip.h>
#include <winsock2.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")


int main() {

	WSADATA wsa;

	if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsa))) {

		std::cout << "Error during Winsock initialization. Error #" << WSAGetLastError() << std::endl;
		return 0;

	}

	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (INVALID_SOCKET == clientSocket) {

		std::cout << "Error when creating a socket. Error #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;

	}

	in_addr ip_to_num;

	if (inet_pton(AF_INET, "127.0.0.1", &ip_to_num) <= 0) {

		std::cout << "Error during socket binding. Error #" << WSAGetLastError() << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		return 0;

	}

	struct sockaddr_in clientInfo;
	ZeroMemory(&clientInfo, sizeof(clientInfo));

	clientInfo.sin_family = AF_INET;
	clientInfo.sin_addr = ip_to_num;
	clientInfo.sin_port = htons(6379);

	if (connect(clientSocket, (sockaddr*)&clientInfo, sizeof(clientInfo)) != 0) {

		std::cout << "Connection to server failed. Error #" << WSAGetLastError() << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		return 0;

	}
	else {

		std::cout << "Connection established" << std::endl;

	}

	std::cout << "Client started ..." << std::endl;

	std::cout << "Enter ./dbms --help for options" << std::endl;

	while (true) {

		std::string outMessage;
		std::getline(std::cin, outMessage);

		const char* outMessage_ = outMessage.c_str();

		if (send(clientSocket, outMessage_, sizeof(outMessage), 0) == SOCKET_ERROR) {

			std::cout << "Can't send message to Server. Error # " << WSAGetLastError() << std::endl;
			closesocket(clientSocket);
			WSACleanup();
			return 0;

		}

		char inpMessage[1024];

		if (recv(clientSocket, inpMessage, sizeof(inpMessage), 0) == SOCKET_ERROR) {

			std::cout << "Can't receive message from Server. Error # " << WSAGetLastError() << std::endl;
			closesocket(clientSocket);
			WSACleanup();
			return 0;

		}

		std::cout << inpMessage << std::endl;

	}

	closesocket(clientSocket);
	return 0;

}