//
// Created by shay on 12/26/17.
//

#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "ListOfGames.h"
#include "GameManager.h"
#include <iostream>

void ListOfGames::addNewGame(GameDetails* game) {
    this->games.push_back(game);
}

void ListOfGames::removeGame(string gameName) {
    for (int i = 0; i < this->games.size(); i++) {
        if (strcmp(gameName.c_str(), this->games[i]->getName().c_str()) ==0) {
            this->games.erase(this->games.begin() + i);
            break;
        }
    }
}

int ListOfGames::size() {
    return this->games.size();
}

GameDetails* ListOfGames::getGame(int i) {
    return this->games[i];
}

void ListOfGames::startNewGame(vector<string> args) {
    string name = args[0];
    int socket = atoi(args[1].c_str());
    for (int i = 0; i < size(); i++) {
        if (strcmp(getGame(i)->getName().c_str(), name.c_str()) == 0) {
            int error = -1;
            int n = write(socket, &error, sizeof(error));
            if (n == -1) {
                throw "Error writing command to socket";
            }
        }
    }
    GameDetails *newGame= new GameDetails(name, socket, 0);
    addNewGame(newGame);
    //sendMassege(socket, 1);
}

void ListOfGames::listOfGames(vector<string> args) {
    int socket = atoi(args[0].c_str());
    int n;
    string listOfGames = "";
    int numOfGames = size();
    char *name;

    if (numOfGames == 0) {
        n = write(socket, &ZEROGAMES, ZEROGAMESLEN);
    } else {
        for (int i = 0; i < size(); i++) {
            if (getGame(i)->getStatus() == WAIT) {
                name = new char[getGame(i)->getName().length() + 1];
                strcpy(name, getGame(i)->getName().c_str());
                for (int j = 0; j < getGame(i)->getName().length(); j++) {
                    char c = name[j];
                    n = write(socket, &c, sizeof(c));
                }
                //listOfGames.append(getGame(i)->getName());
                //listOfGames.append(",");
            }
        }
        //listOfGames.append("\n");
        //for (int i = 0; i < listOfGames.length(); i++) {
            //const char c = listOfGames[i];
            //n = write(socket, &listOfGames[i], sizeof(listOfGames[i]));
        //}
        //const char *finalList = listOfGames.c_str();
        //char c = listOfGames[]
    }
    if (n == -1) {
        throw "Error writing command to socket";
    }
    if (n == 0) {
        throw "Error, connection disconnected!";
    }
}

void ListOfGames::joinToGame(vector<string> args) {
    string name = args[0];
    GameDetails* game = NULL;
    int socket = atoi(args[1].c_str());
    int player1 = -1;
    for (int i = 0 ; i <size(); i++) {
        if ((getGame(i)->getStatus() ==WAIT) && (strcmp(getGame(i)->getName().c_str(), name.c_str()) == 0)) {
            game = getGame(i);
            cout << "game num: " << i << endl;
            getGame(i)->joinGame(socket);
            player1 = getGame(i)->getP1Socket();
            break;
        }
    }

    if (game == NULL) {
        int n = write(socket, &NOGAME, NOGAMESIZE);
    } else {
        //int n = write(player1, &JOINED, JOINSIZE);
        //if (n == -1) {
            //throw "Error reading result from socket";
        //}
        //n = write(socket, &JOINED, JOINSIZE);
        //if (n == -1) {
            //throw "Error reading result from socket";
        //}
        GameManager gMan(game);
        pthread_t gameThread;
        int rc = pthread_create(&gameThread, NULL, gMan.run, (void*)game);
    }
    /*string name = args[0];
    GameDetails* game;
    sockets clientsSockets;
    int socket = atoi(args[0].c_str());
    int player1Socket = -1;
    for (int i = 0 ; i <size(); i++) {
        if ((getGame(i)->getStatus() == WAIT) && (strcmp(getGame(i)->getName().c_str(), name.c_str()) == 0)) {
            game = getGame(i);
            getGame(i)->joinGame(socket);
            player1Socket = getGame(i)->getP1Socket();
            break;
        }
    }
    sendMassege(socket, 2);
    sendMassege(player1Socket, 2);
    int first = 1;
    int n = write(player1Socket, &first, sizeof(first));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    int second = 2;
    n = write(socket, &second, sizeof(first));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    clientsSockets.client1sock = player1Socket;
    clientsSockets.client2sock = socket;
    pthread_t gameThread;
    int rc = pthread_create(&gameThread, NULL, handleClient, (void*)&clientsSockets);
    //keep switching between clients untill stop = true
    bool stop = false;
    while(true) {
        //stop = handleClient(clientSocket1, clientSocket2);
        //int temp = clientSocket1;
        //socket
                //clientSocket1 = clientSocket2;
        //clientSocket2 = temp;
    }
    close(socket);
    close(player1Socket);
    /*if (game == NULL) {
        int n = write(socket, &NOGAME, NOGAMESIZE);
    } else {
        int n = write(player1, &JOINED, JOINSIZE);
        n = write(socket, &JOINED, JOINSIZE);
        GameManager gMan(game);
        pthread_t gameThread;
        int rc = pthread_create(&gameThread, NULL, gMan.run, (void*)&gMan);
    }*/
}

void ListOfGames::sendMassege(int socket, int message) {
    write(socket, &message, sizeof(message));
}

void *ListOfGames::handleClient(void *sockets) {
    char buffer[10];
    struct sockets *args = (struct sockets*) sockets;
    cout << "got in handleclient"<<endl;
    int n = read(args->client1sock, buffer, sizeof(buffer));
    if (n == -1) {
        cout << "Error reading choice" << endl;
        //return true;
    }
    if (n == 0 ) {
        cout << "a Client Disconnect from server" << endl;
        //return true;
    }
    cout << "got move: " << buffer << endl;
    n = write(args->client2sock, buffer, sizeof(buffer));
    if (n == -1) {
        cout << "Error writing choice" << endl;
        //return true;
    }
    if(n == 0) {
        cout << "Client disconnected from server" << endl;
        //return true;
    }
    cout << "Move sent:" << buffer << endl;
    return NULL;
}


