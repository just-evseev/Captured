#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <thread>

#include "../include/MapRender.h"

static sf::Mutex globalMutex;

const unsigned short PORT = 5002;

std::string msgSend;
bool quit = false;

std::vector<std::unique_ptr<sf::TcpSocket>> socket;

void getInfo() {
    while(!quit) {
        for (int i = 0; i < socket.size(); ++i) {
            if (!msgSend.empty()) {
                sf::Packet packetSend;
                globalMutex.lock();
                std::cout << "Msg = " << msgSend << std::endl;
                packetSend << msgSend;
                msgSend = "";
                globalMutex.unlock();

                if (socket[i]->send(packetSend) != sf::Socket::Done) {
                    std::cout << socket[i]->getRemoteAddress() << ": Disconnect" << std::endl;
                    socket.erase(socket.end() - 1);
                    continue;
                }
            }

            sf::Packet packetReceive;
            sf::Socket::Status Status = socket[i]->receive(packetReceive);

            if (Status == sf::Socket::Disconnected) {
                std::cout << socket[i]->getRemoteAddress() << ": Disconnect" << std::endl;
                socket.erase(socket.end() - 1);
                continue;
            }

            if (Status != sf::Socket::Done) {
                continue;
            }

            std::string msg;

            if ((packetReceive >> msg) && !msg.empty()) {
                if (msg == "exit") {
                    std::cout << socket[i]->getRemoteAddress() << ": Disconnect" << std::endl;
                    socket.erase(socket.end() - 1);
                    continue;
                }
                std::cout << socket[i]->getRemoteAddress() << ": " << msg << std::endl;
            }

        }
    }
}

void sendInput() {
    std::string s;
    getline(std::cin,s);
    if(s == "exit") {
        std::cout << "Server Closed" << std::endl;
        quit = true;
    }
    globalMutex.lock();
    msgSend = s;
    globalMutex.unlock();
}

void createServer() {
    sf::TcpListener listener;
    if (listener.listen(PORT) != sf::Socket::Done) {
        puts("Error in listen");
        exit(1);
    }
    listener.setBlocking(false);
    std::cout << "Server created" << std::endl;
    while (!quit) {
        std::unique_ptr<sf::TcpSocket> fooSocket = std::make_unique<sf::TcpSocket>();

        if (listener.accept(*fooSocket) == sf::Socket::Done) {
            (*fooSocket).setBlocking(false);
            socket.push_back(std::move(fooSocket));
            std::cout << socket[socket.size() - 1]->getRemoteAddress() << ": Connected" << std::endl;
        }
    }
}

int main() {
    sf::Thread* serverCr = nullptr;
    serverCr = new sf::Thread(&createServer);
    serverCr->launch();

    sf::Thread * thread = nullptr;
    thread = new sf::Thread(&getInfo);
    thread->launch();

    while (!quit) {
        sendInput();
    }

    if(serverCr) {
        serverCr->wait();
        delete serverCr;
    }

    if(thread) {
        thread->wait();
        delete thread;
    }

    return 0;

}
