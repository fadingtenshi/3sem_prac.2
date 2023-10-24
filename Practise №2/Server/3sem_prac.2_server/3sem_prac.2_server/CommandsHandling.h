#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ws2tcpip.h>
#include <winsock2.h>

#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "Set.h"

void sadd(const std::vector<std::string>& args, Set_::Set* setContainer, SOCKET clientSocket);

void srem(const std::vector<std::string>& args, Set_::Set* setContainer, SOCKET clientSocket);

void sismember(const std::vector<std::string>& args, Set_::Set* setContainer, SOCKET clientSocket);

void spush(const std::vector<std::string>& args, Stack_::Stack& stackContainer, SOCKET clientSocket);

void spop(const std::vector<std::string>& args, Stack_::Stack& stackContainer, SOCKET clientSocket);

void qpush(const std::vector<std::string>& args, Queue_::Queue* queueContainer, SOCKET clientSocket);

void qpop(const std::vector<std::string>& args, Queue_::Queue* queueContainer, SOCKET clientSocket);

void hset(const std::vector<std::string>& args, HashTable_::HashTable* hashTable, SOCKET clientSocket);

void hdel(const std::vector<std::string>& args, HashTable_::HashTable* hashTable, SOCKET clientSocket);

void hget(const std::vector<std::string>& args, HashTable_::HashTable* hashTable, SOCKET clientSocket);

void commandParse(const std::string& command, SOCKET clientSocket);
