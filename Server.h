//
// Created by shay on 12/6/17.
//
#include <pthread.h>

#include <cstdlib>
#include <iostream>
#include <vector>
#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
struct ThreadArgs {
    int i;
    pthread_t thread ;
};

class Server {


public:
    Server(int port);
    void start();
    static void stop();
private:
    bool exit;
    int port;
    std::vector<pthread_t*> threads;
    static void *exitServer(void* server);
    void exitNow();
    int serverSocket; // the socket's file descriptor
    bool handleClient(int clientSocket1, int clientSocket2);
};

#endif //SERVER_SERVER_H
