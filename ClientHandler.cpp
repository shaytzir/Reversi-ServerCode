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
    char commandChar;
    int socket = handler->socket;
    string commandStr;
    for (int i = 0; i < 50; i++) {
        read(socket, &commandChar, sizeof(commandChar));
        commandStr.append(1u, commandChar);
        if (commandChar == '>' || strcmp(commandStr.c_str(), "list_games") == 0) {
            break;
        }
    }
    /*for (int i = 0; i < sizeof(command); i++) {
        read(socket, &commandChar, sizeof(commandChar));
        command[i] = commandChar;
        if (commandChar == '\n') {
            break;
        }
    }*/
    //cout << "I am the command " << command << endl; /////////////////////////////////////// delete
    vector<string> args;
    char *com, *gameName, *command;
    command = new char[commandStr.length() + 1];
    gameName = new char[commandStr.length() + 1];
    stringstream ss;
    strcpy(command, commandStr.c_str());
    com = strtok(command, " <");
    ss << socket;

    if (strcmp(com, "list_games") == 0) {
        args.push_back(com);
        args.push_back(ss.str());
    } else {
        //strcpy(command, commandStr.c_str());
        size_t pos = commandStr.find("<");      // position of "live" in str
        string str = commandStr.substr (pos + 1);
        strcpy(gameName, str.c_str());
        gameName = strtok(gameName, ">");  ///////////doesnt work
        args.push_back(gameName);
        args.push_back(ss.str());
    }
    handler->manager->executeCommand(com, args);
}

