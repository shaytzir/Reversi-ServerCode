//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include "../include/Server.h"
#include "../include/ClientHandler.h"
#include <netinet/in.h>
#include <unistd.h>
#include"../include/Task.h"
#include<iostream>
#include<unistd.h>
#include <string.h>
using namespace std;
#define THREADS_NUM 5
#define TASKS_NUM 5
struct ExitStruct {
    int socket;
    struct sockaddr_in *add;
    socklen_t *len;
    Server* s;
    CommandsManager* man;
    ThreadPool* pool;
    Task** tasks;
};
#define MAX_CONNECTED_CLIENTS   10


Server:: Server( int port): port(port), serverSocket(0) {
    cout << "Server" << endl;
}
void Server:: start() {
    //creating new commands manger to pass on when dealing with clients
    CommandsManager* man = new CommandsManager();

    void* status;
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

    //creating a struct to send as parameters to the main thread
    struct ExitStruct exitStruct;
    exitStruct.socket = serverSocket;
    exitStruct.add = &clientAddress;
    exitStruct.len = &clientAddressLen;
    exitStruct.s = this;
    exitStruct.man = man;
    // Accept a new client connection
    pthread_t exitThread;
    //creating the main thread which runs the program
    int rc = pthread_create(&exitThread, NULL, mainThread, (void*)&exitStruct);
    if (rc) {
        throw "Error: unable to main create thread";
    }

    //the main thread will run forever unless the user
    //will type "exit" and close the main thread and all sub threads
    string input;
    do {
        cin >> input;
    }while(strcmp(input.c_str(), "exit") != 0);
    //call the functions to close all sub sockets and sub threads
    delete man;
    closeThreads();
    /////////////////////////////////////
    exitStruct.pool->terminate();
    for (int i = 0; i < TASKS_NUM; i++) {
        delete exitStruct.tasks[i];
    }
    /////////////////////////////////////
    //close main thread
    pthread_cancel(exitThread);
    pthread_join(exitThread, &status);
}


void Server::closeThreads() {
    void *status;
    //closing all of the sockets of the clients that were part of the program
    for (int i = 0; i < this->clientSockets.size(); i++) {
        close(clientSockets[i]);
    }

    //closing all threads that ran through the program
    /*for (int i = 0; i < this->threads.size(); i++) {
        pthread_cancel(*this->threads[i]);
        pthread_join(*this->threads[i], &status);
    }*/
    close(serverSocket);
}

void *Server::mainThread(void *obj) {
    ExitStruct* ser = (ExitStruct*)obj;
    //extracting all info from the struct that was sents
    int serverSocket = ser->socket;
    socklen_t clientAddressLen = *(ser->len);
    struct sockaddr_in clientAddress = *(ser->add);
    Server* server = ser->s;
    CommandsManager* man = ser->man;
///////////////////////////////////////////////
    ThreadPool threadPool(THREADS_NUM);
    ser->pool = &threadPool;
    Task* tasks[TASKS_NUM];
    ser->tasks = tasks;
//////////////////////////////////////////////
    int i = 0;
    while(true) {
        cout << "Waiting for client connections..." << endl;
        //accepting new client
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket == -1) {
            throw "Error on accept";
        }
        //saving it's socket in the sockets vector
        server->clientSockets.push_back(clientSocket);
        //creating a personal handler per client
        ClientHandler handler(clientSocket, man);
        //sub thread for this specific request
        /*pthread_t* clientHandle = new pthread_t;
        //add this thread to the threads vector
        server->threads.push_back(clientHandle);
        //run the handling command function
        int rc = pthread_create(server->threads[i], NULL, handler.handleCommand, &handler);*/
        tasks[i] = new Task(&handler.handleCommand, (void *) &handler);
        threadPool.addTask(tasks[i]);
        i++;
    }
}