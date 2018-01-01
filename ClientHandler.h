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
    /**
     * constructor
     * @param client_Socket the socket of the client the handler treating
     * @param manager pointer to th command manger
     */
    ClientHandler(int client_Socket, CommandsManager* manager);
    /**
     * extracting the command and according string and passing to manager to execute
     * @param clientH void* param, will cast to ClientHandler*
     * @return none
     */
    static void *handleCommand(void* clientH);
private:
    CommandsManager *manager;
    vector<GameDetails*>  games;
    int socket;
};


#endif //SERVER_CLIENTHANDLER_H
