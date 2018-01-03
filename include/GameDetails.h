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
    WAIT, PLAY
};

class GameDetails {

public:
    /**
     * Constructor
     * @param name name of the game
     * @param psocket1 socket of the first player
     * @param psocket2 socket of the second player
     */
    GameDetails(string &name, int psocket1, int psocket2);
    /**
     * getter
     * @return this game's name
     */
    string getName();
    /**
     * getter
     * @return the first player socket
     */
    int getP1Socket();
    /**
     * getter
     * @return the second player socket
     */
    int getP2Socket();
    /**
     * joining a game changing the status from WAIT to PLAY, and edits the
     * second player socket to be as given as an input
     * @param pNewSocket the joining (second) player socket
     */
    void joinGame(int pNewSocket);
    /**
     * getter
     * @return this game's status
     */
    STATUS getStatus() const;
private:
    string name;
    int player1Socket;
    int player2Socket;
    STATUS status;
};


#endif //SERVER_GAMESDETAIL_H
