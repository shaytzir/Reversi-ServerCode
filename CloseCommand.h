//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#ifndef SERVER_CLOSECOMMAND_H
#define SERVER_CLOSECOMMAND_H

#include "Command.h"

class CloseCommand: public Command{
public:
    void execute(vector<string> args, ListOfGames* games);
};

#endif //SERVER_CLOSECOMMAND_H
