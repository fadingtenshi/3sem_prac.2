


#include "HashTable.h"



unsigned int HashTable_::simpleHash(const std::string& str) {

	unsigned int hash = 0;

	if (str.length() == 0) {

		return -1;

	}

	for (char element : str) {

		hash += static_cast<unsigned int>(element);

	}

	return hash;

}

void HashTable_::insert(HashTable* container, S new_key, S new_data, SOCKET clientSocket) {

	int new_key_ = simpleHash(new_key);
	int hash = new_key_ % HASH_MAX_SIZE;
	int temp_hash = hash;

	std::string outMessage;

	if (new_key_ == -1) {

		outMessage = "-> Zero-length key";
		send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
		return;

	}
	else if (container[hash].hTab->key == new_key) {

		outMessage = "-> This key already exist in the hashtable";
		send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
		return;

	}

	else {

		int initialHash = hash;

		do {
			if (container[hash].hTab->key == "") {

				container[hash].hTab->data = new_data;
				container[hash].hTab->key = new_key;
				outMessage = "-> Data was inserted";
				send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
				return;

			}
			//линейное пробирование
			hash = (hash + 1) % HASH_MAX_SIZE;
		} while (hash != initialHash);

		outMessage = "-> No free slot";
		send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
		return;

	}
}

void HashTable_::remove(HashTable* container, S key, SOCKET clientSocket) {

	int key_ = simpleHash(key);
	int hash = key_ % HASH_MAX_SIZE;
	std::string outMessage;

	if (key_ == -1) {

		outMessage = "-> Zero-length key";
		send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
		return;

	}

	int initialHash = hash;

	do {

		if(container[hash].hTab->key == key) {

			container[hash].hTab->key = "";
			container[hash].hTab->data = "";
			outMessage = "-> Bucket was deleted";
			send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
			return;

		}

		//линейное пробирование
		hash = (hash + 1) % HASH_MAX_SIZE;
	} while (hash != initialHash);

	outMessage = "-> Key not found";
	send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
	return;

}

S HashTable_::get(HashTable* container, S key, SOCKET clientSocket) {

	int key_ = simpleHash(key);
	std::string outMessage;

	if (key_ == -1) {

		return "-> Zero-length key";

	}

	int hash = key_ % HASH_MAX_SIZE;

	int initialHash = hash;

	do {

		if (container[hash].hTab->key == key) {

			outMessage = "-> " + container[hash].hTab->data;
			send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
			return "";

		}

		//линейное пробирование
		hash = (hash + 1) % HASH_MAX_SIZE;
	} while (hash != initialHash);

	outMessage = "-> Key not found";
	send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
	return "";

}