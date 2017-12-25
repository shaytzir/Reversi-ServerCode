//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#ifndef SERVER_CLIENTHANDLER_H
#define SERVER_CLIENTHANDLER_H

#include <iostream>
#include "vector"
#include "CommandsManager.h"
#include "GameDetails.h"

class ClientHandler {
public:
    ClientHandler(int client_Socket, CommandsManager* manager);
    static void *handleCommand(void* clientH);
    static void* executeHandleCommand(void *tArgs) ;
    void openSocket(int client_Socket);
private:
    CommandsManager *manager;
    vector<GameDetails*>  games;
    int socket;
};


#endif //SERVER_CLIENTHANDLER_H
