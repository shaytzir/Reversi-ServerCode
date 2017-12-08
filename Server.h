//
// Created by shay on 12/6/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

class Server {
public:
    Server(int port);
    void start();
    void stop();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    int client;
    bool handleClient(int clientSocket1, int clientSocket2);
};

#endif //SERVER_SERVER_H
