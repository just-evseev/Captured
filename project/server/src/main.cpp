#include <iostream>
#include <vector>
//#include <thread>
//#include <sstream>
#include <SFML/Network.hpp>

#include "../include/MapRender.h"

//std::vector<sf::TcpSocket*> socket;
static std::vector<std::unique_ptr<sf::TcpSocket>> socket;
sf::Mutex globalMutex;

std::string msgSend;
bool quit = false;

const unsigned short PORT = 5000;

void GetInfo(void)
{
    while(!quit)
    {
        sf::Packet packetSend;
        globalMutex.lock();
        packetSend << msgSend;
        globalMutex.unlock();

        for (int i = 0; i < socket.size(); ++i) {
            socket[i]->send(packetSend);  // todo проверить успешность

            std::string msg;
            sf::Packet packetReceive;

            socket[i]->receive(packetReceive);// проверить успешность
            if (msg == "exit")
            {
                std::cout << socket[i]->getRemoteAddress() << ": Disconnect" << std::endl;
            }

            if ((packetReceive >> msg) && !msg.empty())
            {
                std::cout << socket[i]->getRemoteAddress() << ": " << msg << std::endl;
            }
        }
    }
}

void Server(void)
{
    std::cout << "Server created" << std::endl;
    sf::TcpListener listener;
    if(listener.listen(PORT)!=sf::Socket::Done){
        exit(1);
    }
    listener.setBlocking(false);
    while (!quit) {
        std::unique_ptr<sf::TcpSocket> fooSocket = std::make_unique<sf::TcpSocket>();

        if (listener.accept(*fooSocket) == sf::Socket::Done)
        {
            std::cout << "Server createdasdasdassadasdasdasdasdasdd" << std::endl;
            std::cout << "Server createdasdasdasd" << std::endl;
            socket.push_back(std::move(fooSocket));
            std::cout << socket[socket.size() - 1]->getRemoteAddress() << ": Connected" << std::endl;
            socket[socket.size() - 1]->getRemoteAddress();
        }
    }
}

void GetInput(void)
{
    std::string s;
    getline(std::cin,s);
    if(s == "exit") {
        std::cout << ": Disconnect" << std::endl;
        quit = true;
    }
    globalMutex.lock();
    msgSend = s;
    globalMutex.unlock();
}

int main()
{
    sf::Thread* serverCr = nullptr;

    serverCr = new sf::Thread(&Server);
    serverCr->launch();

    sf::Thread* thread = nullptr;

    thread = new sf::Thread(&GetInfo);
    thread->launch();

    while(!quit) {
        GetInput();
    }

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
