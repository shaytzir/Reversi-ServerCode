//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include <unistd.h>
#include <iostream>
#include "GameManager.h"

GameManager::GameManager(GameDetails *g) {
    this->game = g;
}

void *GameManager::run(void *g) {
    GameDetails *man = (GameDetails*)g;
    int soc1 = man->getP1Socket();
    int soc2 = man->getP2Socket();
    int n,check = 1, first = 1;
    n = write(soc1, &first, sizeof(first));
    if (n == -1) {
        cout << "Error writing to socket1" << endl;
        return NULL;
    }
    if (n == 0) {
        cout << "ERROR\n";
        return NULL;
    }
    int second = 2;
    n = write(soc2, &second, sizeof(second));
    if (n == -1) {
        return NULL;
    }
    if (n == 0) {
        cout << "ERROR\n";
        return NULL;
    }
    //keep switching between clients untill stop = true
    while(true) {
        char buffer[10];
        n = read(soc1, buffer, sizeof(buffer));
        if (n == -1) {
            cout << "Error reading choice" << endl;
            break;
        }
        if (n == 0) {
            cout << "a Client Disconnect from server" << endl;
            break;
        }
        n = write(soc1, &check, sizeof(check));
        if (n == -1) {
            cout << "Error reading choice" << endl;
            break;
        }
        if (n == 0) {
            cout << "a Client Disconnect from server" << endl;
            break;
        }
        cout << "got move: " << buffer << endl;
        n = write(soc2, buffer, sizeof(buffer));
        if (n == -1) {
            cout << "Error writing choice" << endl;
            break;
        }
        if(n == 0) {
            cout << "Client disconnected from server" << endl;
            break;
        }
        n = write(soc2, &check, sizeof(check));
        if (n == -1) {
            cout << "Error reading choice" << endl;
            break;
        }
        if (n == 0) {
            cout << "a Client Disconnect from server" << endl;
            break;
        }
        cout << "Move sent:" << buffer << endl;
        int temp = soc1;
        soc1 = soc2;
        soc2 = temp;
    }
    close(soc1);
    close(soc2);
}