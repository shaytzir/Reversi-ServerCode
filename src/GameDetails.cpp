//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include <iostream>
#include "../include/GameDetails.h"

string GameDetails::getName() {
    return this->name;
}

STATUS GameDetails::getStatus() const {
    return this->status;
}

int GameDetails::getP1Socket() {
    return this->player1Socket;
}

int GameDetails::getP2Socket() {
    return this->player2Socket;
}

void GameDetails::joinGame(int pNewSocket) {
    //by joining the game, we update the second player socket to be as given - 'pNewSocket'
    this->player2Socket = pNewSocket;
    //and updating the status to PLAY
    this->status = PLAY;
}

GameDetails::GameDetails(string &name, int psocket1, int psocket2) {
    this->name = name;
    this->player1Socket = psocket1;
    //usually when opening a new game we will have only 1 player
    //thus will enter the second one as '0', if so, the game is in WAIT status
    this->player2Socket = psocket2;
    if (psocket2 == 0) {
        this->status = WAIT;
    } else {
        this->status = PLAY;
    }

}



