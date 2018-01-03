//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#include <vector>
#include <string>
#include "ListOfGames.h"

using namespace std;
class Command {
public:
    /**
     * recieving paramters about the current command, and ListOfGames to make changes on
     * @param args
     * @param games
     */
    virtual void execute(vector<string> args, ListOfGames* games) = 0;
    virtual ~Command() {}
};

#endif //SERVER_COMMAND_H
