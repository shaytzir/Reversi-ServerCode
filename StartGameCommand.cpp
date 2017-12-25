//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include "StartGameCommand.h"

void StartGameCommand::execute(vector<string> args, ListOfGames* games) {
    games->startNewGame(args);
}
