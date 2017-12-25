//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#ifndef SERVER_GAMEMANAGER_H
#define SERVER_GAMEMANAGER_H

#include "GameDetails.h"

class GameManager {
public:
    GameManager(GameDetails* g);
    static void* run(void* g);
    bool getMoves(int soc1, int soc2);
private:
    GameDetails* game;
};

#endif //SERVER_GAMEMANAGER_H