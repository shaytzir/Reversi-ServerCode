//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#ifndef SERVER_JOINGAMECOMMAND_H
#define SERVER_JOINGAMECOMMAND_H

#include "Command.h"
#define JOINED "You Joined A Game!\n"
#define JOINSIZE 19
#define NOGAME "No Such Game To Join\n"
#define NOGAMESIZE 21
class JoinGameCommand : public Command{
public:
    void execute(vector<string> args, ListOfGames* games);
};

#endif //SERVER_JOINGAMECOMMAND_H
