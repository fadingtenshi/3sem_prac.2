#pragma once

#include <string>
#include <iostream>
#include <ws2tcpip.h>
#include <winsock2.h>

#define SET_MAX_SIZE 50

typedef std::string S;

namespace Set_ {

	struct _Set {

		S data;

	};

	struct Set {

		_Set set[SET_MAX_SIZE];

		Set() {

			for (int i = 0; i < SET_MAX_SIZE; i++) {

				set[i].data = "";

			}

		}

	};

	unsigned int simpleHash(const std::string& str);

	void insert(Set* container, S new_data, SOCKET clientSocket);

	void remove(Set* container, S data, SOCKET clientSocket);

	S get(Set* container, S data, SOCKET clientSocket);

};