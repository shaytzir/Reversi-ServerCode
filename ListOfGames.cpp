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

void ListOfGames::addNewGame(GameDetails* game) {
    pthread_mutex_lock(&list_lock);
    this->games.push_back(game);
    pthread_mutex_unlock(&list_lock);
}

void ListOfGames::removeGame(string gameName) {
    cout << "DEBUG: before lock in removeGame" << endl;
    pthread_mutex_lock(&list_lock);         //////////////should the lock be here or inside the loop
    for (int i = 0; i < this->games.size(); i++) {
        if (strcmp(gameName.c_str(), this->games[i]->getName().c_str()) == 0) {
            cout << "DEBUG about to delete " << gameName <<endl;
            this->games.erase(this->games.begin() + i);
            cout << "DEBUG deleted " << gameName << endl;
            break;
        }
    }
    pthread_mutex_unlock(&list_lock);
    cout << "DEBUG: after lock in removeGame" <<endl;
}


GameDetails* ListOfGames::getGame(int i) {
    pthread_mutex_lock(&list_lock);
    GameDetails* game = this->games[i];
    pthread_mutex_unlock(&list_lock);
    return game;
}

void ListOfGames::startNewGame(vector<string> args) {
    string name = args[0];
    int socket = atoi(args[1].c_str());
    int check;
    cout << "DUBUG: startNewGame in listofgames before lock" << endl;
    pthread_mutex_lock(&list_lock);
    for (int i = 0; i < this->games.size(); i++) {
        if (strcmp(this->games[i]->getName().c_str(), name.c_str()) == 0) {
            check = -1;
            int n = write(socket, &check, sizeof(check));
            if (n == -1) {
                throw "Error writing command to socket";
            }
            return;
        }
    } ///////////////////////////////?
    pthread_mutex_unlock(&list_lock);
    cout << "DUBUG: startNewGame in listofgames after lock" << endl;

    GameDetails *newGame= new GameDetails(args[0], socket, 0);
    //addNewGame(newGame);

    pthread_mutex_lock(&list_lock);
    this->games.push_back(newGame);
    pthread_mutex_unlock(&list_lock);
    //sendMassege(socket, 1);
}

void ListOfGames::listOfGames(vector<string> args) {
    cout << "DEBUG got into listOfGames in ListOfGames" << endl;
    pthread_mutex_lock(&list_lock);
    cout <<"DEBUG insidr mutex lock in ListOfGames" <<endl;
    int socket = atoi(args[1].c_str());
    int n;
    cout << "DEBUG: in listofgames in ListOfGames, sending to socket socket: " << socket << endl;
    string listOfGames = "";
    int numOfGames = this->games.size();
    char *name, c;
    if (numOfGames == 0) {
        n = write(socket, &ZEROGAMES, ZEROGAMESLEN);
    } else {
        for (int i = 0; i < numOfGames; i++) {
            GameDetails* curG = this->games[i];
            if (curG->getStatus() == WAIT) {
                name = new char[curG->getName().length() + 1];
                strcpy(name, curG->getName().c_str());
                for (int j = 0; j < curG->getName().length(); j++) {
                    c = name[j];
                    cout << c;
                    n = write(socket, &c, sizeof(c));
                    if (n == -1) {
                        throw "Error writing command to socket";
                    }
                    if (n == 0) {
                        throw "Error, connection disconnected!";
                    }
                    if ((j + 1) == curG->getName().length() && i + 1 != numOfGames) {
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
    pthread_mutex_unlock(&list_lock);
}

void ListOfGames::joinToGame(vector<string> args) {
    string name = args[0];
    GameDetails* game = NULL;
    int check;
    int socket = atoi(args[1].c_str());
    int player1 = -1;
    pthread_mutex_lock(&list_lock);
    for (int i = 0 ; i <this->games.size(); i++) {
        if ((this->games[i]->getStatus() == WAIT) && (strcmp(this->games[i]->getName().c_str(), name.c_str()) == 0)) {
            game = this->games[i];
            cout << "DEBUG: got into joinToGame in ListOfGames. game num: " << i << endl;
            this->games[i]->joinGame(socket);
            player1 = this->games[i]->getP1Socket();
            break;
        }
    }
    pthread_mutex_unlock(&list_lock);
    if (game == NULL) {
        check = -1;
        int n = write(socket, &check, sizeof(check));
    } else {
        GameManager gMan(game);
        pthread_t gameThread;
        int rc = pthread_create(&gameThread, NULL, gMan.run, (void*)game);
    }
    /**
     *
     *
     *
     * how to make this point wait until the thread "gman.run" is over
     */
    removeGame(game->getName());
}

void ListOfGames::sendMassege(int socket, int message) {
    write(socket, &message, sizeof(message));
}