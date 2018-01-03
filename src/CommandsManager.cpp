//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include <iostream>
#include "../include/CommandsManager.h"
#include "../include/StartGameCommand.h"
#include "../include/GetGamesListCommand.h"
#include "../include/JoinGameCommand.h"

CommandsManager::CommandsManager() {
    //creating the ListOfGames, holds vector of all games and runs start/join/list_games
    this->games = new ListOfGames;
    //holding a map which pairs a command to certain class
    commandsMap["start"] = new StartGameCommand();
    commandsMap["list_games"] = new GetGamesListCommand();
    commandsMap["join"] = new JoinGameCommand();
}

CommandsManager::~CommandsManager() {
    //should delete all things created on heap, deleteing the map and the listOfGames class
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
    delete games;

}

void CommandsManager::executeCommand(string command, vector<string> args) {
    //saving the right command Class in commanObject
    Command *commandObject = commandsMap[command];
    //executing the command
    commandObject->execute(args, games);
}
