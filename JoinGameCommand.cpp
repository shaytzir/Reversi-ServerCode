//
// Created by shay on 12/26/17.
//

#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "JoinGameCommand.h"

void JoinGameCommand::execute(vector<string> args, ListOfGames* games) {
    string name = args[0];
    int socket = atoi(args[1]);
    int player1 = -1;
    for (int i = 0 ; i <games->size(); i++) {
        if ((games->getGame(i).getStatus() ==WAIT) && (strcmp(games->getGame(i).getName(), name) == 0)) {
            games->getGame(i).joinGame(socket);
            player1 = games->getGame(i).getP1Socket();
            break;
        }
    }

    if (player1 == -1) {
        int n = write(socket, &NOGAME, NOGAMESIZE);
    } else {
        int n = write(player1, &JOINED, JOINSIZE);
        int first = 1;
        n = write(player1, &first, sizeof(first));
        n = write(socket, &JOINED, JOINSIZE);
        int second = 2;
        n = write(socket, &second, sizeof(second));
    }

}
