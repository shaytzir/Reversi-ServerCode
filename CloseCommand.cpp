//
// Created by shay on 12/26/17.
//

#include "CloseCommand.h"

void CloseCommand::execute(vector<string> args, ListOfGames* games) {
    string name = args[0];
    games->removeGame(name);
}
