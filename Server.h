//
// Created by shay on 12/6/17.
//
#include <pthread.h>

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
    void stop();
private:
    bool exit;
    int port;
    void *exitServer(void* close);
    int serverSocket; // the socket's file descriptor
    bool handleClient(int clientSocket1, int clientSocket2);
};

#endif //SERVER_SERVER_H
