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

pthread_mutex_t list_lock;


void ListOfGames::removeGame(string gameName) {
    pthread_mutex_lock(&list_lock);
    for (int i = 0; i < this->games.size(); i++) {
        if (strcmp(gameName.c_str(), this->games[i]->getName().c_str()) == 0) {
            this->games.erase(this->games.begin() + i);
            break;
        }
    }
    pthread_mutex_unlock(&list_lock);
}



void ListOfGames::startNewGame(vector<string> args) {
    string name = args[0];
    int socket = atoi(args[1].c_str());
    int check, n;
    pthread_mutex_lock(&list_lock);
    for (int i = 0; i < this->games.size(); i++) {
        if (strcmp(this->games[i]->getName().c_str(), name.c_str()) == 0) {
            n = write(socket, &EXISTS, EXISTSLEN);
            if (n == -1) {
                throw "Error writing command to socket";
            }
            if (n == 0 ) {
                throw "ERROR";
            }
            check = -1;
            n = write(socket, &check, sizeof(check));
            if (n == -1) {
                throw "Error writing command to socket";
            }
            if (n == 0) {
                throw "ERROR";
            }
            pthread_mutex_unlock(&list_lock);
            return;
        }
    }

    n = write(socket, CREATEDAGAME, CREATEDLEN);
    if (n == -1) {
        throw "Error writing command to socket";
    }
    if (n == 0) {
        throw "ERROR";
    }
    pthread_mutex_unlock(&list_lock);
    GameDetails *newGame= new GameDetails(args[0], socket, 0);

    pthread_mutex_lock(&list_lock);
    this->games.push_back(newGame);
    pthread_mutex_unlock(&list_lock);
}

void ListOfGames::listOfGames(vector<string> args) {
    pthread_mutex_lock(&list_lock);
    int socket = atoi(args[1].c_str());
    int n;
    string listOfGames = "";
    int numOfGames = this->games.size();
    char *name, c;
    if (numOfGames == 0) {
        n = write(socket, &ZEROGAMES, ZEROGAMESLEN);
        int check = -1;
        n = write(socket, &check, sizeof(check));
    } else {
        for (int i = 0; i < numOfGames; i++) {
            GameDetails* curG = this->games[i];
            if (curG->getStatus() == WAIT) {
                name = new char[curG->getName().length() + 1];
                strcpy(name, curG->getName().c_str());
                for (int j = 0; j < curG->getName().length(); j++) {
                    c = name[j];
                    n = write(socket, &c, sizeof(c));
                    if ((j + 1) == curG->getName().length() && i + 1 != numOfGames) {
                        c = ',';
                        n = write(socket, &c, sizeof(c));
                        c = ' ';
                        n = write(socket, &c, sizeof(c));
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
    pthread_mutex_unlock(&list_lock);
}

void ListOfGames::joinToGame(vector<string> args) {
    string name = args[0];
    void* status;
    GameDetails* game = NULL;
    int check, n;
    int socket = atoi(args[1].c_str());
    int player1 = -1;
    pthread_mutex_lock(&list_lock);
    for (int i = 0 ; i <this->games.size(); i++) {
        if ((this->games[i]->getStatus() == WAIT) && (strcmp(this->games[i]->getName().c_str(), name.c_str()) == 0)) {
            game = this->games[i];
            this->games[i]->joinGame(socket);
            player1 = this->games[i]->getP1Socket();
            break;
        }
    }
    pthread_mutex_unlock(&list_lock);
    if (game == NULL) {
        n = write(socket, &JOINANOTHER, JOINANOTHERLEN);
        if (n == -1) {
            throw "ERROR";
        }
        if (n == 0) {
            throw "ERROR";
        }
        check = -1;
        n = write(socket, &check, sizeof(check));
        if (n == -1) {
            throw "ERROR";
        }
        if (n == 0) {
            throw "ERROR";
        }
        return;
    } else {
        GameManager gMan(game);
        pthread_t gameThread;
        n = write(socket, &JOINED, JOINSIZE);
        if (n == -1) {
            throw "ERROR";
        }
        if (n == 0) {
            throw "ERROR";
        }
        int rc = pthread_create(&gameThread, NULL, gMan.run, (void*)game);
        pthread_join(gameThread, &status);
    }
    removeGame(game->getName());
}
