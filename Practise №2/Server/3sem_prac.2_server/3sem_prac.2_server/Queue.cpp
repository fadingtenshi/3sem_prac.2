


#include "Queue.h"



void Queue_::push(S new_data, Queue* queue) {

	Node* new_node = new Node();
	new_node->data = new_data;
	new_node->next = NULL;

	if (isEmpty(queue)) {
		queue->first = new_node;
	}
	else {
		queue->last->next = new_node;
	}

	queue->last = new_node;

}

bool Queue_::isEmpty(Queue* queue) {

	return(queue->first == NULL);

}

void Queue_::initialize(Queue* queue) {

	queue->first = NULL;

}

S Queue_::pop(Queue* queue) {

	if (isEmpty(queue)) {
		return "Queue is empty";

	}

	S value = queue->first->data;
	Node* temp = queue->first;
	queue->first = temp->next;

	free(temp);

	return value;

}