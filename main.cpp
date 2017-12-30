//
// Shay Tzirin
// ID: 315314930
// Yuval Hoch
// ID: 204468474
//

#include "Server.h"
#include <fstream>
using namespace std;

int main() {
    //read server configuration
    ifstream inFile;
    //inFile.open("ServerConfig.txt");
    //int port;
    //inFile >> port;
    int port = 8000; ///////////////////
    Server server(port);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    return 0;
}