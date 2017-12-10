#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main() {
    //read server configuration
    ifstream inFile;
    inFile.open("ServerConfig.txt");
    int port;
    inFile >> port;
    Server server(port);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    return 0;
}