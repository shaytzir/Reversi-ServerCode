//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include <pthread.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "CommandsManager.h"

using namespace std;

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


class Server {

public:
    Server(int port);
    void start();
    static void stop();
private:
    bool exit;
    int port;
    vector<pthread_t*> threads;
    vector<int> clientSockets;
    static void *exitServer(void* server);
    void exitNow();
    int serverSocket; // the socket's file descriptor
    bool handleClient(int clientSocket1, int clientSocket2);
    void closeTrheads();
    static void *mainThread(void* obj);
};

#endif //SERVER_SERVER_H
