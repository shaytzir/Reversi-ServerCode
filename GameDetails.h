//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#ifndef SERVER_GAMESDETAIL_H
#define SERVER_GAMESDETAIL_H

#include <sys/socket.h>
#include <string>
using namespace std;

enum STATUS {
    WAIT, PLAY, END
};

class GameDetails {

public:
    GameDetails(string name, int psocket1, int psocket2);
    string getName();
    int getP1Socket();
    int getP2Socket();
    void joinGame(int pNewSocket);
    GameDetails();
    ~GameDetails();
    STATUS getStatus() const;
private:
    string name;
    int player1Socket;
    int player2Socket;
    STATUS status;
};


#endif //SERVER_GAMESDETAIL_H
