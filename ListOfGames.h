//
// Created by shay on 12/26/17.
//

#ifndef SERVER_LISTOFGAMES_H
#define SERVER_LISTOFGAMES_H


#include <vector>
#include "GameDetails.h"

class ListOfGames {
public:
    ListOfGames(){}
    void addNewGame(GameDetails game);
    void removeGame(string gameName);
    int size();
    GameDetails getGame(int i);
private:
    vector<GameDetails> games;

};


#endif //SERVER_LISTOFGAMES_H
