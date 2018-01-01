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
    /**
     * constructor
     */
    CommandsManager();
    /**
     * destructor
     */
    ~CommandsManager();
    /**
     * getting a command and executing it
     * @param command one of 3 commands: "start"/"list_games"/"join"
     * @param args vector which holds the name entered for the command and the client's socket
     */
    void executeCommand(string command, vector<string> args);
private:
    map<string, Command*> commandsMap;
    ListOfGames* games;

};


#endif //SERVER_COMMANDSMANAGER_H
