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
#define NOGAME "No Such Game To Join\n"
#define NOGAMESIZE 21

struct sockets {
    int client1sock;
    int client2sock;
};

class ListOfGames {
public:
    ListOfGames(){}
    void addNewGame(GameDetails* game);
    void removeGame(string gameName);
    int size();
    GameDetails* getGame(int i);
    void startNewGame(vector<string> args);
    void listOfGames(vector<string> args);
    void joinToGame(vector<string> args);
    void closeGame(vector<string> args);
private:
    vector<GameDetails*> games;
    void sendMassege(int socket, int message);
    static void *handleClient(void *sockets);
};

#endif //SERVER_LISTOFGAMES_H
