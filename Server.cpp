//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include "Server.h"
#include "ClientHandler.h"
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
using namespace std;

#define MAX_CONNECTED_CLIENTS   10
struct ExitStruct {
    int socket;
    struct sockaddr_in *add;
    socklen_t *len;
    Server* s;
    CommandsManager* man;
};

Server:: Server( int port): port(port), serverSocket(0) {
    exit = false;
    cout << "Server" << endl;
}
void Server:: start() {

    int i = 0;
    CommandsManager* man = new CommandsManager();
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM,0);
    if (serverSocket == - 1 ) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void*)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;


    struct ExitStruct exitStruct;
    exitStruct.socket = serverSocket;
    exitStruct.add = &clientAddress;
    exitStruct.len = &clientAddressLen;
    exitStruct.s = this;
    exitStruct.man = man;

    // Accept a new client connection
    pthread_t exitThread;
    int rc = pthread_create(&exitThread, NULL, mainThread, (void*)&exitStruct);

    string input;
    do {
        cin >> input;
    }while(strcmp(input.c_str(), "exit") != 0);
    //ser->exit = true;
    closeTrheads();
    pthread_cancel(exitThread);

    // Accept a new client connection
    /*pthread_t exitThread;
    int rc = pthread_create(&exitThread, NULL, exitServer, this);
    while(!exit) {
        cout << "Waiting for client connections..." << endl;
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket == -1) {
            throw "Error on accept";
        }
        ClientHandler handler(clientSocket, man);
        pthread_t* clientHandle = new pthread_t;
        this->threads.push_back(clientHandle);
        int rc = pthread_create(threads[i], NULL, handler.handleCommand, &handler);
        i++;
    }*/
}

void *Server::exitServer(void* server) {
    Server* ser = (Server*)server;
    string input;
    do {
        cin >> input;
    }while(strcmp(input.c_str(), "exit") != 0);
    ser->exit = true;
    ser->closeTrheads();
}

void Server::closeTrheads() {
    void *status;
    int signToClose = -1;
    for (int i = 0; i < this->clientSockets.size(); i++) {
        write(clientSockets[i], &signToClose, sizeof(signToClose));
        //close(clientSockets[i]);
    }
    for (int i = 0; i < this->threads.size(); i++) {
        pthread_cancel(*this->threads[i]);
        pthread_join(*this->threads[i], &status);
    }
    close(serverSocket);
}

void *Server::mainThread(void *obj) {
    ExitStruct* ser = (ExitStruct*)obj;
    int serverSocket = ser->socket;
    socklen_t clientAddressLen = *(ser->len);
    struct sockaddr_in clientAddress = *(ser->add);
    Server* server = ser->s;
    CommandsManager* man = ser->man;
    int i = 0;
    while(true) {
        cout << "Waiting for client connections..." << endl;
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket == -1) {
            throw "Error on accept";
        }
        server->clientSockets.push_back(clientSocket);
        ClientHandler handler(clientSocket, man);
        pthread_t* clientHandle = new pthread_t;
        server->threads.push_back(clientHandle);
        int rc = pthread_create(server->threads[i], NULL, handler.handleCommand, &handler);
        i++;
    }
}
