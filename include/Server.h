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
#include "ThreadPool.h"

using namespace std;

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


class Server {

public:
    /**
     * constructor for the server
     * @param port  server's socket
     */
    Server(int port);
    /**
     * starting the servers program
     */
    void start();
private:
    int port;
    vector<pthread_t*> threads;
    vector<int> clientSockets;
    void exitNow();
    int serverSocket; // the socket's file descriptor
    void closeThreads();
    static void *mainThread(void* obj);
};

#endif //SERVER_SERVER_H
