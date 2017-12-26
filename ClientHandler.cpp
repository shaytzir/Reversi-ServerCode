#include <unistd.h>
#include <cstring>
#include "ClientHandler.h"
#include <string>
#include <sstream>

using namespace std;

ClientHandler::ClientHandler(int client_Socket, vector <pthread_t*> threadsVec, int i, ListOfGames games) {
    this->socket = client_Socket;
    this->threads = threadsVec;
    this->index = i;
    this->manager = new CommandsManager(&games);
}

void ClientHandler::handle() {
    pthread_t* clientHandle;
    this->threads.push_back(clientHandle);
    int rc = pthread_create(threads[this->index], NULL, handleCommand, NULL);
}

void *ClientHandler::handleCommand(void *clientSocket) {
    char commandChar;
    int buff = 50;
    string command = "";
    for (int i = 0; i < buff; i++) {
        read(this->socket, &commandChar, sizeof(commandChar));
        command.append(1u, commandChar);
    }
    vector<string> args;
    char *name, *gameName;
    stringstream ss;
    name = strtok(command, " ");
    ss << this->socket;
    if (strcmp(name, "list_games") == 0) {
        args.push_back(name);
        args.push_back(ss.str());
    } else {
        gameName = strtok(command, "\n");
        args.push_back(gameName);
        args.push_back(ss.str());
    }
    this->manager->executeCommand(name, args);
}

