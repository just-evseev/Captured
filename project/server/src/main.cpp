#include <iostream>
#include <vector>
#include <SFML/Network.hpp>

#include "../include/MapRender.h"
#include "../include/Server.h"

int main()
{
    sf::Thread* serverCr = nullptr;
    sf::Thread* thread = nullptr;

    serverCr = new sf::Thread(&Server::createServer);
    thread = new sf::Thread(&Server::getInfo);
    serverCr->launch();
    thread->launch();

    if(serverCr)
    {
        serverCr->wait();
        delete serverCr;
    }

    if(thread)
    {
        thread->wait();
        delete thread;
    }
    return 0;

}
