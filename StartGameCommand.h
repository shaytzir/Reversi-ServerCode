//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#ifndef SERVER_STARTGAMECOMMAND_H
#define SERVER_STARTGAMECOMMAND_H

#include "Command.h"

class StartGameCommand : public Command {
public:
    void execute(vector<string> args,ListOfGames* games);
};

#endif //SERVER_STARTGAMECOMMAND_H
