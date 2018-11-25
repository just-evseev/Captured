#include <iostream>
//#include <thread>
//#include <sstream>
#include <SFML/Network.hpp>

#include "../include/MapRender.h"

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
    std::cout << "Server created";
    sf::TcpListener listener;
    listener.listen(PORT);
    while (!quit) {
        listener.accept(socket);
        std::cout << socket.getRemoteAddress() << ": Connected" << std::endl;
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

int main() {
    sf::Thread* serverCreate = 0;
    serverCreate = new sf::Thread(&Server);
    serverCreate->launch();

    if(serverCreate)
    {
        serverCreate->wait();
        delete serverCreate;
    }

//    Server();
    sf::Thread* threadGet = 0;

    threadGet = new sf::Thread(&GetInfo);
    threadGet->launch();



    while(!quit)
    {
        GetInput();
    }

    if(threadGet)
    {
        threadGet->wait();
        delete threadGet;
    }
    return 0;

}
