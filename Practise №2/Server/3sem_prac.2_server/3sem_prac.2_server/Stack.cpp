


#include "Stack.h"



void Stack_::push(S new_data, Node** head) {
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = (*head);
    (*head) = new_node;
}

void Stack_::initialize(Stack* stack) {
    stack->head = NULL;
}

S Stack_::pop(Node** head) {

    if (*(head) == NULL) {
        return "Stack is empty";
    }

    Node* new_node = (*head);
    S value = new_node->data;
    (*head) = new_node->next;
    free(new_node);
    return value;

}