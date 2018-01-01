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
    //locking the list, because the function runs over the entire list
    pthread_mutex_lock(&list_lock);
    for (int i = 0; i < this->games.size(); i++) {
        //if the game we want to remove from list is in it
        if (strcmp(gameName.c_str(), this->games[i]->getName().c_str()) == 0) {
            //remove it fromthe list and break the loop
            this->games.erase(this->games.begin() + i);
            break;
        }
    }
    pthread_mutex_unlock(&list_lock);
}



void ListOfGames::startNewGame(vector<string> args) {
    //the name of the new game is saved in the first place in the args vector
    string name = args[0];
    //client's socket saved in second place in args
    int socket = atoi(args[1].c_str());
    int check, n;
    //locking the list, because the function runs over the entire list
    pthread_mutex_lock(&list_lock);
    for (int i = 0; i < this->games.size(); i++) {
        //if the client wants to create an exisiting game
        if (strcmp(this->games[i]->getName().c_str(), name.c_str()) == 0) {
            //write him an error message
            n = write(socket, &EXISTS, EXISTSLEN);
            if (n == -1) {
                throw "Error writing command to socket";
            }
            if (n == 0 ) {
                throw "ERROR";
            }
            check = -1;
            //send -1 flag so the client will need to connect again to the server
            n = write(socket, &check, sizeof(check));
            if (n == -1) {
                throw "Error writing command to socket";
            }
            if (n == 0) {
                throw "ERROR";
            }
            //unlock and return
            pthread_mutex_unlock(&list_lock);
            return;
        }
    }
    //if theres no such game with the same name, write the client that his creation succeed
    n = write(socket, CREATEDAGAME, CREATEDLEN);
    if (n == -1) {
        throw "Error writing command to socket";
    }
    if (n == 0) {
        throw "ERROR";
    }
    //unlock
    pthread_mutex_unlock(&list_lock);
    //create new game by parameters
    GameDetails *newGame= new GameDetails(args[0], socket, 0);
    //add to this lists
    pthread_mutex_lock(&list_lock);
    this->games.push_back(newGame);
    pthread_mutex_unlock(&list_lock);
}

void ListOfGames::listOfGames(vector<string> args) {
    int socket = atoi(args[1].c_str());
    int n;
    string listOfGames = "";
    pthread_mutex_lock(&list_lock);
    int numOfGames = this->games.size();
    char *name, c;
    //if there are no games, send a message to the client
    if (numOfGames == 0) {
        n = write(socket, &ZEROGAMES, ZEROGAMESLEN);
        //sending a -1 flag to the client, after asking for the list the client connects again
        int check = -1;
        n = write(socket, &check, sizeof(check));
        //if there are games, write him the list
    } else {
        for (int i = 0; i < numOfGames; i++) {
            GameDetails* curG = this->games[i];
            //if the client can join this game
            if (curG->getStatus() == WAIT) {
                //save the game's name and write to client, char by char
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
        //send -1 flag because after asking for a list the client connects again
        int check = -1;
        n = write(socket, &check, sizeof(check));
    }
    if (n == -1) {
        throw "Error writing command to socket";
    }
    if (n == 0) {
        throw "Error, connection disconnected!";
    }
    //unlock
    pthread_mutex_unlock(&list_lock);
}

void ListOfGames::joinToGame(vector<string> args) {
    //the name of the desired game is in thr first place in args
    string name = args[0];
    void* status;
    GameDetails* game = NULL;
    int check, n;
    int socket = atoi(args[1].c_str());
    int player1 = -1;
    //locking because were going ovr in a loop on the entire list
    pthread_mutex_lock(&list_lock);
    for (int i = 0 ; i < this->games.size(); i++) {
        //if the game is available to join (status=wait) and exists with the same name
        if ((this->games[i]->getStatus() == WAIT) &&
                (strcmp(this->games[i]->getName().c_str(), name.c_str()) == 0)) {
            //update the game from null
            game = this->games[i];
            //update second player and change status to play
            this->games[i]->joinGame(socket);
            player1 = this->games[i]->getP1Socket();
            break;
        }
    }
    //not using the list anymore, unlock
    pthread_mutex_unlock(&list_lock);
    //if there no such game w that name or, it exists but cant be joined
    if (game == NULL) {
        //write message to the client
        n = write(socket, &JOINANOTHER, JOINANOTHERLEN);
        if (n == -1) {
            throw "ERROR";
        }
        if (n == 0) {
            throw "ERROR";
        }
        //send -1 to make him connect again
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
        //run the game for those 2 players
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
        //wait for the game to end in order to delete it from the list
        pthread_join(gameThread, &status);
    }
    removeGame(game->getName());
}
