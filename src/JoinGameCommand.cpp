//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include "../include/JoinGameCommand.h"

void JoinGameCommand::execute(vector<string> args, ListOfGames* games) {
    //calling listofgames to run this command - joining a game
    games->joinToGame(args);
}
