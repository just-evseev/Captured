#include <iostream>
#include <vector>
//#include <thread>
//#include <sstream>
#include <SFML/Network.hpp>

#include "../include/MapRender.h"

//std::vector<sf::TcpSocket> socket;
sf::TcpSocket socket;
sf::Mutex globalMutex;

std::string msgSend;
bool quit = false;

const unsigned short PORT = 5000;
const std::string IPADDRESS("172.20.10.14");//change to suit your needs

void GetInfo(void)
{
    static std::string oldMsg;
    while(!quit)
    {
        sf::Packet packetSend;
        globalMutex.lock();
        packetSend << msgSend;
        globalMutex.unlock();

        socket.send(packetSend);

        std::string msg;
        sf::Packet packetReceive;

        socket.receive(packetReceive);
        if ((packetReceive >> msg) && oldMsg != msg && !msg.empty())
        {
            std::cout << socket.getRemoteAddress() << ": " << msg << std::endl;
            oldMsg = msg;
        }
    }
}

void Server(void)
{
    std::cout << "Server created" << std::endl;
    sf::TcpListener listener;
    listener.listen(PORT);
    while (!quit) {
        listener.accept(socket);
        std::cout << socket.getRemoteAddress() << ": Connected" << std::endl;
        int a = 0, b = 0, c = 0, d = 0;
        socket.getRemoteAddress(a, b, c, d);
        std::cout << d << std::endl;
    }
}

void GetInput(void)
{
    std::string s;
    getline(std::cin,s);
    if(s == "exit") {
        std::cout << socket.getRemoteAddress() << ": Disconnect" << std::endl;
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
