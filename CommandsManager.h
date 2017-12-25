//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#ifndef SERVER_COMMANDSMANAGER_H
#define SERVER_COMMANDSMANAGER_H

#include <map>
#include "Command.h"

class CommandsManager {
public:
    CommandsManager();
    ~CommandsManager();
    void executeCommand(string command, vector<string> args);
private:
    map<string, Command*> commandsMap;
    ListOfGames* games;

};


#endif //SERVER_COMMANDSMANAGER_H
