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

struct sockets {
    int client1sock;
    int client2sock;
};

class ListOfGames {
public:
    ListOfGames(){}
    void removeGame(string gameName);
    void startNewGame(vector<string> args);
    void listOfGames(vector<string> args);
    void joinToGame(vector<string> args);
private:
    vector<GameDetails*> games;
};

#endif //SERVER_LISTOFGAMES_H
