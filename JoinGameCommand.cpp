//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include "JoinGameCommand.h"

void JoinGameCommand::execute(vector<string> args, ListOfGames* games) {
    games->joinToGame(args);
}
