//
// Created by shay on 12/26/17.
//

#ifndef SERVER_PLAYCOMMAND_H
#define SERVER_PLAYCOMMAND_H


#include "Command.h"

class PlayCommand : public Command{
public:
void execute(vector<string> args, ListOfGames* games);

};


#endif //SERVER_PLAYCOMMAND_H
