#include <unistd.h>
#include <cstring>
#include "ClientHandler.h"
#include <string>
#include <sstream>

using namespace std;

ClientHandler::ClientHandler(int client_Socket, vector <pthread_t*> threadsVec, int i, CommandsManager* manager) {
    this->socket = client_Socket;
    this->threads = threadsVec;
    this->index = i;
    this->manager = manager;
}

/*void ClientHandler::handle() {
    pthread_t* clientHandle;
    this->threads.push_back(clientHandle);
    int rc = pthread_create(threads[this->index], NULL, handleCommand, &this->index);
}*/

void *ClientHandler::handleCommand(void *clientH) {
    ClientHandler* handler = (ClientHandler*) clientH;
    char commandChar, command[50];
    int socket = handler->socket;

    read(socket, command, sizeof(command));
    /*for (int i = 0; i < sizeof(command); i++) {
        read(socket, &commandChar, sizeof(commandChar));
        command[i] = commandChar;
        if (commandChar == '\n') {
            break;
        }
    }*/
    //cout << "I am the command " << command << endl; /////////////////////////////////////// delete
    vector<string> args;
    char *com, *gameName;
    stringstream ss;
    com = strtok(command, " ");
    ss << socket;

    if (strcmp(com, "list_games") == 0) {
        args.push_back(com);
        args.push_back(ss.str());
    } else {
        gameName = strtok(command, "\n");  ///////////doesnt work
        args.push_back(gameName);
        args.push_back(ss.str());
    }
    handler->manager->executeCommand(com, args);
}

