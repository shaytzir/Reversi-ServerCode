//
// Created by shay on 12/26/17.
//

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include "GetGamesListCommand.h"

void GetGamesListCommand::execute(vector<string> args, ListOfGames* games) {
   /* int socket = atoi(args[0].c_str());
    int n;
    string listOfGames = "";
    int numOfGames = games->size();
    if (numOfGames == 0) {
        n = write(socket, &ZEROGAMES, ZEROGAMESLEN);

    } else {
        for (int i = 0; i < games->size(); i++) {
            if (games->getGame(i).getStatus() == WAIT) {
                listOfGames.append(games->getGame(i).getName());
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
    */
    cout << "GetGamesListCommand" << endl;
    games->listOfGames(args);

}
