//
// Created by shay on 12/26/17.
//

#include <cstring>
#include "ListOfGames.h"

void ListOfGames::addNewGame(GameDetails game) {
    this->games.push_back(game);
}

void ListOfGames::removeGame(string gameName) {
    for (int i = 0; i < this->games.size(); i++) {
        if (strcmp(gameName, this->games[i].getName()) ==0) {
            this->games.erase(this->games.begin() + i);
            break;
        }
    }
}

int ListOfGames::size() {
    return this->games.size();
}

GameDetails ListOfGames::getGame(int i) {
    return this->games[i];
}
