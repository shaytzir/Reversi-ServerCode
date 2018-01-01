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
    /**
     * constructor
     * @param g GameDetails pointer
     */
    GameManager(GameDetails* g);
    /**
     * static function running a game - transfering messages between clients
     * @param g a GameDetails - void*
     * @return none
     */
    static void* run(void* g);
private:
    GameDetails* game;
};

#endif //SERVER_GAMEMANAGER_H