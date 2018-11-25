#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <thread>

#include "../include/MapRender.h"
#include "../include/Server.h"



void getInfo() {
    Server s;
    s.getInfo();
}

void createServer() {
    Server s;
    s.createServer();
}

int main() {
    sf::Thread* serverCr;
    serverCr = new sf::Thread(&createServer);
    sf::Thread * thread;
    thread = new sf::Thread(&getInfo);

    serverCr->launch();
    thread->launch();

    return 0;

}
