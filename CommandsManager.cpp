//
// Created by shay on 12/25/17.
//

#include "CommandsManager.h"
#include "StartGameCommand.h"
#include "GetGamesListCommand.h"
#include "JoinGameCommand.h"
#include "PlayCommand.h"

CommandsManager::CommandsManager(ListOfGames* games) {
    commandsMap["start"] = new StartGameCommand();
    commandsMap["list_games"] = new GetGamesListCommand();
    commandsMap["join"] = new JoinGameCommand();
    commandsMap["play"] = new PlayCommand();
    this->games = games;
    //commandsMap["close"] = new CloseGameCommand(); //client cant close game
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
    commandObj->execute(args, this->games);
}
