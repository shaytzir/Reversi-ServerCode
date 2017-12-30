//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include <iostream>
#include "GetGamesListCommand.h"

void GetGamesListCommand::execute(vector<string> args, ListOfGames* games) {
    cout << "DEBUG : GOT INTO EXECUTE IN GetGamesListCommand" << endl;
    games->listOfGames(args);
}
