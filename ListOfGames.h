//
// Created by shay on 12/26/17.
//

#ifndef SERVER_LISTOFGAMES_H
#define SERVER_LISTOFGAMES_H


#include <vector>
#include "GameDetails.h"
#define ZEROGAMES "no games to display\n"
#define ZEROGAMESLEN 20
#define JOINED "You Joined A Game!\n"
#define JOINSIZE 19
#define NOGAME "No Such Game To Join\n"
#define NOGAMESIZE 21
class ListOfGames {
public:
    ListOfGames(){}
    void addNewGame(GameDetails* game);
    void removeGame(string gameName);
    int size();
    GameDetails* getGame(int i);

    //void sendMessageToClient(string msg);
    void startNewGame(vector<string> args);
    void listOfGames(vector<string> args);
    void joinToGame(vector<string> args);
    void closeGame(vector<string> args);
private:
    vector<GameDetails*> games;

};


#endif //SERVER_LISTOFGAMES_H
