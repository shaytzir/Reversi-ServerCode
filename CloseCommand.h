//
// Created by shay on 12/26/17.
//

#ifndef SERVER_CLOSECOMMAND_H
#define SERVER_CLOSECOMMAND_H


#include "Command.h"

class CloseCommand: public Command{
public:
    void execute(vector<string> args, ListOfGames* games);

};


#endif //SERVER_CLOSECOMMAND_H
