//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include <iostream>
#include "GameDetails.h"

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
    this->player2Socket = pNewSocket;
    this->status = PLAY;
}

GameDetails::GameDetails(string &name, int psocket1, int psocket2) {
    this->name = name;
    this->player1Socket = psocket1;
    this->player2Socket = psocket2;
    if (psocket2 == 0) {
        this->status = WAIT;
    } else {
        this->status = PLAY;
    }

}

GameDetails::~GameDetails() {};


