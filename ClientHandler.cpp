//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include <unistd.h>
#include <cstring>
#include "ClientHandler.h"
#include <sstream>

using namespace std;

ClientHandler::ClientHandler(int client_Socket, CommandsManager* manager) {
    this->socket = client_Socket;
    this->manager = manager;
}

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
        size_t pos = commandStr.find("<");
        string str = commandStr.substr (pos + 1);
        strcpy(gameName, str.c_str());
        gameName = strtok(gameName, ">");
        args.push_back(gameName);
        args.push_back(ss.str());
        cout << ss.str() << endl;
    }
    handler->manager->executeCommand(com, args);
}