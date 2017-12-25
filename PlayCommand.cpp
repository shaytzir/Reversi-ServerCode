//
// Created by shay on 12/26/17.
//

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "PlayCommand.h"

void PlayCommand::execute(vector<string> args, ListOfGames *games) {
    /*cout << "EXECUTE PLAY MOVE";
    int senderSocket = atoi(args[0].c_str());
    const char* move = args[1].c_str(); //getting the move as "x,y"

    for (int i = 0; i < games->size(); i++) {
        if (games->getGame(i).getP1Socket() == senderSocket) {
            int receiveSocket = games->getGame(i).getP2Socket();
            int n = write(receiveSocket, move, sizeof(move));
            break;
        } else if (games->getGame(i).getP2Socket() == senderSocket) {
            int receiveSocket = games->getGame(i).getP1Socket();
            int n = write(receiveSocket, move, sizeof(move));
            break;
        }
    }*/

}
