


#include "Set.h"



unsigned int Set_::simpleHash(const std::string& str) {

	unsigned int hash = 0;

	if (str.length() == 0) {

		return -1;

	}

	for (char element : str) {

		hash += static_cast<unsigned int>(element);

	}

	return hash;

}

void Set_::insert(Set* container, S new_data, SOCKET clientSocket) {

	int new_key_ = simpleHash(new_data);
	int hash = new_key_ % SET_MAX_SIZE;

	if (new_key_ == -1) {

		std::cout << "-> Zero-length key" << std::endl;

	}
	else {

		int initialHash = hash;

		do {
			if (container[hash].set->data == "") {

				container[hash].set->data = new_data;
				std::cout << "-> Data was inserted" << std::endl;
				return;

			}
			else if (container[hash].set->data == new_data) {

				std::cout << "-> The key already presented in the set" << std::endl;
				return;

			}
			//линейное пробирование
			hash = (hash + 1) % SET_MAX_SIZE;
		} while (hash != initialHash);

		std::cout << "-> No free slot" << std::endl;

	}
}

void Set_::remove(Set* container, S data, SOCKET clientSocket) {

	int key_ = simpleHash(data);
	int hash = key_ % SET_MAX_SIZE;


	if (key_ == -1) {

		std::cout << "-> Zero-length key" << std::endl;
		return;

	}

	int initialHash = hash;

	do {

		if (container[hash].set->data != "") {

			container[hash].set->data = "";
			return;

		}

		//линейное пробирование
		hash = (hash + 1) % SET_MAX_SIZE;
	} while (hash != initialHash);

	std::cout << "-> Key not found" << std::endl;

}

S Set_::get(Set* container, S data, SOCKET clientSocket) {

	int key_ = simpleHash(data);

	if (key_ == -1) {

		return "-> Zero-length key";

	}

	int hash = key_ % SET_MAX_SIZE;

	int initialHash = hash;

	do {

		if (container[hash].set->data == data) {

			return container[hash].set->data;

		}

		//линейное пробирование
		hash = (hash + 1) % SET_MAX_SIZE;
	} while (hash != initialHash);

	return "-> Key not found";

}