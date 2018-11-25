//
// Created by Ilya on 25/11/2018.
//

#include <iostream>

#include "../include/Server.h"

Server::Server() {

}

Server::~Server() {

}

void Server::getInfo() {
    while(!quit)
    {
        sf::Packet packetSend;
        globalMutex.lock();
        packetSend << msgSend;
        globalMutex.unlock();

        for (int i = 0; i < socket.size(); ++i)
        {
            if (socket[i]->send(packetSend) != sf::Socket::Done) {
                puts("Error in packetSend");
                exit(1);
            }  // todo реализовать дисконнект

            std::string msg;
            sf::Packet packetReceive;

            if (socket[i]->receive(packetReceive)  != sf::Socket::Done) {
                puts("Error in receive");
                exit(1);
            }  // todo реализовать дисконнект

            if (msg == "exit")
            {
                std::cout << socket[i]->getRemoteAddress() << ": Disconnect" << std::endl;
            }  // todo реализовать дисконнек

            if ((packetReceive >> msg) && !msg.empty())
            {
                std::cout << socket[i]->getRemoteAddress() << ": " << msg << std::endl;
            }
        }
    }
}

void Server::sendInput() {
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

void Server::createServer() {
    sf::TcpListener listener;
    if (listener.listen(PORT) != sf::Socket::Done) {
        puts("Error in listen");
        exit(1);
    }
    listener.setBlocking(false);
    std::cout << "Server created" << std::endl;
    std::cout << "Write <exit> to Disconnect server" << std::endl;
    while (!quit) {
        std::unique_ptr<sf::TcpSocket> fooSocket = std::make_unique<sf::TcpSocket>();

        if (listener.accept(*fooSocket) == sf::Socket::Done)
        {
            socket.push_back(std::move(fooSocket));
            std::cout << socket[socket.size() - 1]->getRemoteAddress() << ": Connected" << std::endl;
            socket[socket.size() - 1]->getRemoteAddress();
        }

        sendInput();
    }
}