#pragma once

#include <string>

typedef std::string S;

namespace Stack_ {
    struct Node {
        S data;
        Node* next;
    };

    struct Stack {
        Node* head;
    };

    void push(S new_data, Node** head);
    void initialize(Stack* stack);
    S pop(Node** head);
}