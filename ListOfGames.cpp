//
// Created by shay on 12/26/17.
//

#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "ListOfGames.h"
#include "GameManager.h"

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
            /*
             * check if failed bla bla
             */
        }
    }
    GameDetails *newGame= new GameDetails(name, socket, 0);
    addNewGame(newGame);

}

void ListOfGames::listOfGames(vector<string> args) {
    int socket = atoi(args[0].c_str());
    int n;
    string listOfGames = "";
    int numOfGames = size();
    if (numOfGames == 0) {
        n = write(socket, &ZEROGAMES, ZEROGAMESLEN);

    } else {
        for (int i = 0; i < size(); i++) {
            if (getGame(i)->getStatus() == WAIT) {
                listOfGames.append(getGame(i)->getName());
                listOfGames.append("\n");
            }
        }

        const char *finalList = listOfGames.c_str();
        n = write(socket, finalList, sizeof(finalList));
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
            getGame(i)->joinGame(socket);
            player1 = getGame(i)->getP1Socket();
            break;
        }
    }

    if (game == NULL) {
        int n = write(socket, &NOGAME, NOGAMESIZE);
    } else {
        int n = write(player1, &JOINED, JOINSIZE);
        n = write(socket, &JOINED, JOINSIZE);
        GameManager gMan(game);
        pthread_t gameThread;
        int rc = pthread_create(&gameThread, NULL, gMan.run, (void*)&gMan);
    }

}


