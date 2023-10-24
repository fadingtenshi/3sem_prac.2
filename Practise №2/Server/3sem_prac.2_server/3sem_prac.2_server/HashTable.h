#pragma once

#include <string>
#include <iostream>
#include <ws2tcpip.h>
#include <winsock2.h>

#define HASH_MAX_SIZE 50

typedef std::string S;

namespace HashTable_{

	struct HashTab {

		S key;
		S data;

	};

	struct HashTable {

		HashTab hTab[HASH_MAX_SIZE];

		HashTable() {

			for (int i = 0; i < HASH_MAX_SIZE; i++) {

				hTab[i].key = "";
				hTab[i].data = "";

			}

		}

	};

	unsigned int simpleHash(const std::string& str);

	void insert(HashTable* container, S new_key, S new_data, SOCKET clientSocket);

	void remove(HashTable* container, S key, SOCKET clientSocket);

	S get(HashTable* container, S key, SOCKET clientSocket);

};