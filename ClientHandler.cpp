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
    int socket = handler->socket, n;
    string commandStr;
    //reading the command the client typed in
    for (int i = 0; i < 50; i++) {
        n = read(socket, &commandChar, sizeof(commandChar));
        if (n == -1) {
            throw "ERROR";
        }
        if (n == 0) {
            throw "ERROR";
        }
        commandStr.append(1u, commandChar);
        //the command end if it "list_games", or any other command ending with '>'
        if (commandChar == '>' || strcmp(commandStr.c_str(), "list_games") == 0) {
            break;
        }
    }
    vector<string> args;
    char *com, *gameName, *command;
    //saving the command in char* format
    command = new char[commandStr.length() + 1];
    //saving the gamename in char* format
    gameName = new char[commandStr.length() + 1];
    stringstream ss;
    //saving the command in commandStr
    strcpy(command, commandStr.c_str());
    //com is the command after the sign '<'
    com = strtok(command, " <");
    ss << socket; //changing the socket from int to string
    if (strcmp(com, "list_games") == 0) {
        //in order not to enter empty name, we'll push "list_games" as a name but will never use it
        args.push_back(com);
        //pushing the socket to the vector args
        args.push_back(ss.str());
    } else {
        //saving only the name game without the "<" and ">"
        size_t pos = commandStr.find("<");
        string str = commandStr.substr (pos + 1);
        strcpy(gameName, str.c_str());
        gameName = strtok(gameName, ">");
        args.push_back(gameName); //pushing the name to args
        args.push_back(ss.str());//pushing the socket to args
    }
    //calling to the command manger to execute the order
    handler->manager->executeCommand(com, args);
}