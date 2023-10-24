


#include "CommandsHandling.h"



void sadd(const std::vector<std::string>& args, Set_::Set* setContainer, SOCKET clientSocket) {

    if (args.size() != 2) {

        std::string outMessage = "-> Invalid arguments for SADD";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }
    else {

        Set_::insert(setContainer, args[1], clientSocket);

    }

}

void srem(const std::vector<std::string>& args, Set_::Set* setContainer, SOCKET clientSocket) {

    if (args.size() != 2) {

        std::string outMessage = "-> Invalid arguments for SREM";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }
    else {

        Set_::remove(setContainer, args[1], clientSocket);

    }

};

void sismember(const std::vector<std::string>& args, Set_::Set* setContainer, SOCKET clientSocket) {

    if (args.size() != 2) {
        
        std::string outMessage = "-> Invalid arguments for SISMEMBER";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }
    else {
        std::string result = Set_::get(setContainer, args[1], clientSocket);
        if (result == args[1]) {

            std::cout << "-> The element is present in the set" << std::endl;

        }
        else if (result == "-> Key not found") {

            std::cout << result << std::endl;

        }
        else {

            std::cout << "-> The element is not present in the set" << std::endl;

        }
    }

}

void spush(const std::vector<std::string>& args, Stack_::Stack& stackContainer, SOCKET clientSocket) {

    if (args.size() != 2) {
        
        std::string outMessage = "-> Invalid arguments for SPUSH";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }
    else {

        Stack_::push(args[1], &(stackContainer.head));

    }

}

void spop(const std::vector<std::string>& args, Stack_::Stack& stackContainer, SOCKET clientSocket) {

    if (args.size() != 1) {
        
        std::string outMessage = "-> Invalid arguments for SPOP";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }
    else {

        std::string result = Stack_::pop(&stackContainer.head);

        if (result == "Stack is empty") {

            send(clientSocket, result.c_str(), result.size() + 1, 0);
            return;

        }
        std::string outMessage = "-> Element" + result + " has been deleted";
        send(clientSocket, result.c_str(), result.size() + 1, 0);
        return;

    }

};

void qpush(const std::vector<std::string>& args, Queue_::Queue* queueContainer, SOCKET clientSocket) {

    if (args.size() != 2) {
        
        std::string outMessage = "-> Invalid arguments for QPUSH";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }
    else {

        Queue_::push(args[1], queueContainer);

    }

}

void qpop(const std::vector<std::string>& args, Queue_::Queue* queueContainer, SOCKET clientSocket) {

    if (args.size() != 1) {
       
        std::string outMessage = "-> Invalid arguments for QPOP";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }
    else {

        std::string result = Queue_::pop(queueContainer);

        if (result == "Queue is empty") {

            send(clientSocket, result.c_str(), result.size() + 1, 0);
            return;

        }

        std::string outMessage = "-> Element" + result + " has been deleted";
        send(clientSocket, result.c_str(), result.size() + 1, 0);
        return;

    }

}

void hset(const std::vector<std::string>& args, HashTable_::HashTable* hashTable, SOCKET clientSocket) {

    if (args.size() != 3) {
        
        std::string outMessage = "-> Invalid arguments for HSET";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }
    else {

        HashTable_::insert(hashTable, args[1], args[2], clientSocket);

    }

};

void hdel(const std::vector<std::string>& args, HashTable_::HashTable* hashTable, SOCKET clientSocket) {

    if (args.size() != 2) {
        
        std::string outMessage = "-> Invalid arguments for HDEL";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }
    else {

        HashTable_::remove(hashTable, args[1], clientSocket);

    }

};

void hget(const std::vector<std::string>& args, HashTable_::HashTable* hashTable, SOCKET clientSocket) {

    if (args.size() != 2) {
        
        std::string outMessage = "-> Invalid arguments for HGET";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }
    else {

        std::string result = HashTable_::get(hashTable, args[1], clientSocket);

        if (result == "-> Zero-length key") {

            send(clientSocket, result.c_str(), result.size() + 1, 0);
            return;

        }

    }

}

void commandParse(const std::string& command, SOCKET clientSocket) {

    std::vector<std::string> commands = { "SADD", "SREM", "SISMEMBER", "SPUSH", "SPOP", "QPUSH", "QPOP", "HSET", "HDEL", "HGET" };

    static Set_::Set setContainer[SET_MAX_SIZE];


    static HashTable_::HashTable hashTable[HASH_MAX_SIZE];

    static Stack_::Stack stackContainer;

    static Queue_::Queue queueContainer;

    static bool latch = false;
    if (latch == false) {

        Stack_::initialize(&stackContainer);
        Queue_::initialize(&queueContainer);
        latch = true;

    }
    std::vector<std::string> args;
    size_t pos = 0;
    std::string delimiter = " ";
    size_t start = 0;
    std::string outMessage;

    while ((pos = command.find(delimiter, start)) != std::string::npos) {
        args.push_back(command.substr(start, pos - start));
        start = pos + delimiter.length();
    }

    args.push_back(command.substr(start));

    if (args.size() < 2) {

        outMessage = "-> Invalid command line arguments";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }

    if (args[0] != "./dbms" || args[1] != "--query") {

        outMessage = "-> Invalid command line arguments";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }

    args.erase(args.begin(), args.begin() + 2);

    if (!args.empty()) {
        std::string argument = args[0];
        if (argument == "SADD") {

            sadd(args, setContainer, clientSocket);

        }
        else if (argument == "SREM") {

            srem(args, setContainer, clientSocket);

        }
        else if (argument == "SISMEMBER") {

            sismember(args, setContainer, clientSocket);

        }
        else if (argument == "SPUSH") {

            spush(args, stackContainer, clientSocket);

        }
        else if (argument == "SPOP") {

            spop(args, stackContainer, clientSocket);

        }
        else if (argument == "QPUSH") {

            qpush(args, &queueContainer, clientSocket);

        }
        else if (argument == "QPOP") {

            qpop(args, &queueContainer, clientSocket);

        }
        else if (argument == "HSET") {

            hset(args, hashTable, clientSocket);

        }
        else if (argument == "HDEL") {

            hdel(args, hashTable, clientSocket);

        }
        else if (argument == "HGET") {

            hget(args, hashTable, clientSocket);

        }

    }
    else {

        outMessage = "-> Invalid command";
        send(clientSocket, outMessage.c_str(), outMessage.size() + 1, 0);
        return;

    }
}