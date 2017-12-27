//
// Created by shay on 12/25/17.
//

#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "StartGameCommand.h"

void StartGameCommand::execute(vector<string> args, ListOfGames* games) {
    /*string name = args[0];
    int socket = atoi(args[1].c_str());
    for (int i = 0; i < games->size(); i++) {
        if (strcmp(games->getGame(i).getName().c_str(), name.c_str()) == 0) {
            int error = -1;
            int n = write(socket, &error, sizeof(error));
            /*
             * check if failed bla bla
             */
      //  }
    //}
   // GameDetails newGame(name, socket, 0);
    games->startNewGame(args);

}
