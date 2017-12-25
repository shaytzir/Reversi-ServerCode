//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include "CloseCommand.h"

void CloseCommand::execute(vector<string> args, ListOfGames* games) {
    string name = args[0];
    games->removeGame(name);
}
