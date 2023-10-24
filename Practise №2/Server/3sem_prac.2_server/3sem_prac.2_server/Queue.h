#pragma once

#include <string>

#define QUEUE_MAX_SIZE 50

typedef std::string S;

namespace Queue_ {

	struct Node {
		S data;
		Node* next;
	};

	struct Queue {
		Node* first;
		Node* last;
	};

	void push(S new_data, Queue* queue);
	bool isEmpty(Queue* queue);
	void initialize(Queue* queue);
	S pop(Queue* queue);

}