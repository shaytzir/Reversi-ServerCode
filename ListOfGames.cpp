//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
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
    int socket = atoi(args[1].c_str()), check;
    for (int i = 0; i < size(); i++) {
        if (strcmp(getGame(i)->getName().c_str(), name.c_str()) == 0) {
            check = -1;
            int n = write(socket, &check, sizeof(check));
            if (n == -1) {
                throw "Error writing command to socket";
            }
            return;
        }
    }
    GameDetails *newGame= new GameDetails(name, socket, 0);
    addNewGame(newGame);
    //sendMassege(socket, 1);
}

void ListOfGames::listOfGames(vector<string> args) {
    int socket = atoi(args[1].c_str());
    int n;
    cout << "socket: " << socket << endl;
    string listOfGames = "";
    int numOfGames = size();
    cout << "numOfGamesL " << numOfGames << endl;
    cout << "numOfGames: " << numOfGames;
    char *name, c;
    if (numOfGames == 0) {
        n = write(socket, &ZEROGAMES, ZEROGAMESLEN);
    } else {
        for (int i = 0; i < numOfGames; i++) {
            if (getGame(i)->getStatus() == WAIT) {
                name = new char[getGame(i)->getName().length() + 1];
                strcpy(name, getGame(i)->getName().c_str());
                for (int j = 0; j < getGame(i)->getName().length(); j++) {
                    c = name[j];
                    cout << c;
                    n = write(socket, &c, sizeof(c));
                    if (n == -1) {
                        throw "Error writing command to socket";
                    }
                    if (n == 0) {
                        throw "Error, connection disconnected!";
                    }
                    if ((j + 1) == getGame(i)->getName().length() && i + 1 != numOfGames) {
                        c = ',';
                        write(socket, &c, sizeof(c));
                        c = ' ';
                        write(socket, &c, sizeof(c));
                    }
                }
            }
        }
        c = '\n';
        n = write(socket, &c, sizeof(c));
        int check = -1;
        n = write(socket, &check, sizeof(check));
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
    int check;
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
        check = -1;
        int n = write(socket, &check, sizeof(check));
    } else {
        GameManager gMan(game);
        pthread_t gameThread;
        int rc = pthread_create(&gameThread, NULL, gMan.run, (void*)game);
    }
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