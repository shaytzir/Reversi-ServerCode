//
// Created by shay on 12/25/17.
//

#ifndef SERVER_CLIENTHANDLER_H
#define SERVER_CLIENTHANDLER_H

#include <iostream>
#include "vector"
#include "CommandsManager.h"
#include "GameDetails.h"

class ClientHandler {
public:
    ClientHandler(int client_Socket, vector<pthread_t*> threads, int index, ListOfGames games);
    void handle();
    void *handleCommand(void* clientSocket);

    static void* executeHandleCommand(void *tArgs) ;

    void openSocket(int client_Socket);

private:
    CommandsManager *manager;
    vector<GameDetails*>  games;
    int socket;
    vector<pthread_t*> threads;
    int index;
};


#endif //SERVER_CLIENTHANDLER_H
