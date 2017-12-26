//
// Created by shay on 12/26/17.
//

#ifndef SERVER_GETGAMESLISTCOMMAND_H
#define SERVER_GETGAMESLISTCOMMAND_H


#include "Command.h"
#define ZEROGAMES "no games to display\n"
#define ZEROGAMESLEN 20
class GetGamesListCommand : public Command{
public:
    void execute(vector<string> args, ListOfGames* games);

};


#endif //SERVER_GETGAMESLISTCOMMAND_H
