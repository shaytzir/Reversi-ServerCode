#include <unistd.h>
#include <iostream>
#include "GameManager.h"

GameManager::GameManager(GameDetails *g) {
    this->game = g;
}

void *GameManager::run(void *g) {
    GameManager *man = (GameManager*)g;
    int soc1 = man->game->getP1Socket();
    int soc2 = man->game->getP2Socket();
    int n;
    int first = 1;
    n = write(soc1, &first, sizeof(first));
    if (n == -1) {
        cout << "Error writing to socket1" << endl;
        return NULL;
    }
    int second = 2;
    n = write(soc2, &second, sizeof(second));
    if (n == -1) {
        cout << "Error writing to socket2" << endl;
        return NULL;
    }
    /*if (clientSocket1 == -1 || clientSocket2 == -1) {
        throw "Error on accept";
    }*/
    //keep switching between clients untill stop = true
    bool stop = false;
    while(!stop) {
        stop = man->getMoves(soc1, soc2);
        int temp = soc1;
        soc1 = soc2;
        soc2 = temp;
    }

    cout << "for debug: got into gameManager RunGame, closing the socket - might be changed" << endl;
    close(soc1);
    close(soc2);
}

bool GameManager::getMoves(int soc1, int soc2) {
    char buffer[10];
    cout << "got in handleclient"<<endl;
    int n = read(soc1, buffer, sizeof(buffer));
    if (n == -1) {
        cout << "Error reading choice" << endl;
        return true;
    }
    if (n == 0 ) {
        cout << "a Client Disconnect from server" << endl;
        return true;
    }

    cout << "got move: " << buffer << endl;
    n = write(soc2, buffer, sizeof(buffer));
    if (n == -1) {
        cout << "Error writing choice" << endl;
        return true;
    }
    if(n == 0) {
        cout << "Client disconnected from server" << endl;
        return true;
    }
    cout << "Move sent:" << buffer << endl;
    return false;
}