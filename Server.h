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
    void handleClient(int clientSocket);
    int calc(int arg1, const char op,int arg2) const;
};

#endif //SERVER_SERVER_H
