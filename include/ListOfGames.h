//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#ifndef SERVER_LISTOFGAMES_H
#define SERVER_LISTOFGAMES_H

#include <vector>
#include "GameDetails.h"
#define ZEROGAMES "no games to display\n"
#define ZEROGAMESLEN 20
#define JOINED "You Joined A Game!\n"
#define JOINSIZE 19
#define EXISTS "Please Start Another Game With Different Name\n"
#define EXISTSLEN 46
#define JOINANOTHER "There's No Game With This Name. Please Join Another One\n"
#define JOINANOTHERLEN 56
#define CREATEDAGAME "A Game Was Created! waiting for another player to join\n"
#define CREATEDLEN 55

class ListOfGames {
public:
    ListOfGames(){}
    ~ListOfGames();
    /**
     * removing a game from this list of games
     * @param gameName a name of a game to remove
     */
    void removeGame(string gameName);
    /**
     * start new game command - creating new game and adding to list
     * @param args parameters, name of new game and the creator's socket
     */
    void startNewGame(vector<string> args);
    /**
     * list_games command - writing to the requesting socket the list of games
     * @param args parameters - the requtesting client's socket
     */
    void listOfGames(vector<string> args);
    /**
     * join a game comman - editing an existing game in the list, and making the clients play
     * @param args parameters, name of a game to join + joining client's socket
     */
    void joinToGame(vector<string> args);
private:
    vector<GameDetails*> games;
};

#endif //SERVER_LISTOFGAMES_H
