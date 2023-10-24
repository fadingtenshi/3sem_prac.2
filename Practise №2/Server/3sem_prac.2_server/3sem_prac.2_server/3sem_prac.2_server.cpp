


#include "CommandsHandling.h"



#pragma comment(lib, "ws2_32.lib")



void handleClient(SOCKET clientSocket) {

	char buffer[1024];

	int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

	if (bytesReceived == SOCKET_ERROR) {

		std::cout << "Error reading data from the client. Error #" << WSAGetLastError() << std::endl;
		closesocket(clientSocket);
		return;

	}

	std::string command;

	for (int i = 0; i < strlen(buffer); i++) {

		if (buffer[i] != '\n') {

			command += buffer[i];

		}
		else {

			break;

		}

	}

	if (command == "./dbms --help") {
		std::string helpMessage = "--query:\n";
		helpMessage += "\tSADD [KEY] [VALUE]\n";
		helpMessage += "\tSREM [KEY]\n";
		helpMessage += "\tSISMEMBER [KEY] [VALUE]\n";
		helpMessage += "\tSPUSH [KEY]\n";
		helpMessage += "\tSPOP [KEY]\n";
		helpMessage += "\tQPUSH [KEY]\n";
		helpMessage += "\tQPOP [KEY]\n";
		helpMessage += "\tHSET [KEY] [VALUE]\n";
		helpMessage += "\tHDEL [KEY]\n";
		helpMessage += "\tHGET [KEY]\n\n";

		send(clientSocket, helpMessage.c_str(), helpMessage.size() + 1, 0);

		return;

	}
	
	commandParse(command, clientSocket);

}

int main() {

	WSADATA wsa;

	if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsa))) {

		std::cout << "Error during Winsock initialization. Error #" << WSAGetLastError() << std::endl;
		return 0;

	}

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (INVALID_SOCKET == serverSocket) {

		std::cout << "Error when creating a socket. Error #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;

	}

	in_addr ip_to_num;

	if (inet_pton(AF_INET, "127.0.0.1", &ip_to_num) <= 0) {

		std::cout << "Error during socket binding. Error #" << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;

	}

	struct sockaddr_in servInfo;
	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(6379);

	if (bind(serverSocket, (sockaddr*)&servInfo, sizeof(servInfo)) != 0) {

		std::cout << "Error Socket binding to server info. Error # " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;

	}

	if (listen(serverSocket, SOMAXCONN) != 0) {

		std::cout << "Can't start to listen to. Error # " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;

	}

	sockaddr_in clientInfo;

	ZeroMemory(&clientInfo, sizeof(clientInfo));

	int clientInfo_size = sizeof(clientInfo);

	SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientInfo, &clientInfo_size);

	if (clientSocket == INVALID_SOCKET) {

		std::cout << "Client detected, but can't connect to a client. Error # " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		closesocket(clientSocket);
		WSACleanup();
		return 0;

	}

	while (true) {

		handleClient(clientSocket);

	}

	closesocket(serverSocket);
	return 0;

}