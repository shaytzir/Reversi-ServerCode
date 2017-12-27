//
// Created by shay on 12/25/17.
//

#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#include <vector>
#include <string>
#include "ListOfGames.h"

using namespace std;
class Command {
public:
    virtual void execute(vector<string> args, ListOfGames* games) = 0;
    virtual ~Command() {}
private:

};

#endif //SERVER_COMMAND_H
