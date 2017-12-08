#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server:: Server( int port): port(port), serverSocket(0) {
    cout << "Server" << endl;
}
void Server:: start() {
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
    struct sockaddr_in clientAddress2;
    socklen_t clientAddressLen2;
    // Accept a new client connection
    while(true) {
        cout << "Waiting for client connections..." << endl;
        int clientSocket1 = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);
        cout << "First player connected" << endl;
        int clientSocket2 = accept(serverSocket, (struct sockaddr*)&clientAddress2, &clientAddressLen2);
        cout << "Second player connected" << endl;

        int first = 1;
        int n = write(clientSocket1, &first, sizeof(first));
        if (n == -1) {
            cout << "Error writing to socket1" << endl;
            return;
        }

        int second = 2;
        n = write(clientSocket2, &second, sizeof(second));
        if (n == -1) {
            cout << "Error writing to socket2" << endl;
            return;
        }

        if (clientSocket1 == -1 || clientSocket2 == -1) {
            throw "Error on accept";
        }
        bool stop = false;
        while(!stop) {
            stop = handleClient(clientSocket1, clientSocket2);
            int temp = clientSocket1;
            clientSocket1 = clientSocket2;
            clientSocket2 = temp;
        }

        close(clientSocket1);
        close(clientSocket2);
    }
}

// Handle requests from a specific client
bool Server::handleClient(int clientSocket1, int clientSocket2) {
    char buffer[10];
    cout << "got in handleclient"<<endl;
    int n = read(clientSocket1, buffer, sizeof(buffer));
    if (n == -1) {
        cout << "Error reading choice" << endl;
        return true;
    }
    if (n == 0 ) {
        cout << "a Client Disconnect from server" << endl;
        return true;
    }

    cout << "got move: " << buffer << endl;
    n = write(clientSocket2, buffer, sizeof(buffer));
    if (n == -1) {
        cout << "Error writing choice" << endl;
        return true;
    }
    if(n == 0) {
        cout << "Client disconnected from server" << endl;
        return true;
    }
    cout << "Move sent:" << buffer << endl;
    return false;
}


void Server::stop() {
    close(serverSocket);
}