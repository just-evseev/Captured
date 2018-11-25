#include <iostream>
//#include <thread>
//#include <sstream>
#include <SFML/Network.hpp>

#include "MapRender.h"

sf::TcpSocket socket;
sf::Mutex globalMutex;

std::string msgSend;

bool quit = false;

const unsigned short PORT = 5000;
const std::string IPADDRESS("192.168.0.100");//change to suit your needs

void DoStuff(void)
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
            std::cout << msg << std::endl;
            oldMsg = msg;
        }
    }
}

void Server(void)
{
    sf::TcpListener listener;
    listener.listen(PORT);
    listener.accept(socket);
    std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
}

void GetInput(void)
{
    std::string s;
    std::cout << "\nEnter \"exit\" to quit or message to send: ";
    getline(std::cin,s);
    if(s == "exit")
        quit = true;
    globalMutex.lock();
    msgSend = s;
    globalMutex.unlock();
}

int main() {
//    Socket s;
//    s.bind(5000);
//    s.listen();
//
//    while (true) {
//        ClientSocket client = s.accept();
//        std::thread t(client_handler, std::move(client));
//        t.detach();
//    }
    Server();
    sf::Thread* thread = 0;
    thread = new sf::Thread(&DoStuff);
    thread->launch();

    while(!quit)
    {
        GetInput();
    }

    if(thread)
    {
        thread->wait();
        delete thread;
    }
    return 0;

}
