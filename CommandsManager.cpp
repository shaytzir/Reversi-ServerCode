//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include <iostream>
#include "CommandsManager.h"
#include "StartGameCommand.h"
#include "GetGamesListCommand.h"
#include "JoinGameCommand.h"

CommandsManager::CommandsManager() {
    this->games = new ListOfGames;
    commandsMap["start"] = new StartGameCommand();
    commandsMap["list_games"] = new GetGamesListCommand();
    commandsMap["join"] = new JoinGameCommand();
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }

}

void CommandsManager::executeCommand(string command, vector<string> args) {
    //try to make args hold also the socket of the sender
    Command *commandObj = commandsMap[command];
    commandObj->execute(args, games);
}
