#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <thread>

#include "../include/MapRender.h"

static sf::Mutex globalMutex;

const unsigned short PORT = 5001;

std::string msgSend;
bool quit = false;

std::vector<std::unique_ptr<sf::TcpSocket>> socket;

void getInfo() {
    while(!quit) {
        for (int i = 0; i < socket.size(); ++i) {

            if (!msgSend.empty()) {
                sf::Packet packetSend;
                globalMutex.lock();
                packetSend << msgSend;
                msgSend = "";
                globalMutex.unlock();

                if (socket[i]->send(packetSend) != sf::Socket::Done) {
                    std::cout << socket[i]->getRemoteAddress() << ": Disconnect" << std::endl;
                    puts("Error in packetSend");
                    socket.erase(socket.end() - 1);
                    continue;
                }
            }

            std::string msg;
            sf::Packet packetReceive;

            if (socket[i]->receive(packetReceive)  != sf::Socket::Done) {
                std::cout << socket[i]->getRemoteAddress() << ": Disconnect" << std::endl;
                puts("Error in receive");
                socket.erase(socket.end() - 1);
                continue;
            }

            if (msg == "exit") {
                std::cout << socket[i]->getRemoteAddress() << ": Disconnect" << std::endl;
                socket.erase(socket.end() - 1);
                continue;
            }

            if ((packetReceive >> msg) && !msg.empty()) {
                std::cout << socket[i]->getRemoteAddress() << ": " << msg << std::endl;
            }
        }
    }
}

void sendInput() {
    std::string s;
    getline(std::cin,s);
    std::cout << s << std::endl;
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
//    listener.setBlocking(false);
    std::cout << "Server created" << std::endl;
    std::cout << "Write <exit> to Disconnect server" << std::endl;
    while (!quit) {
        std::unique_ptr<sf::TcpSocket> fooSocket = std::make_unique<sf::TcpSocket>();
        std::cout << "asd" << std::endl;

        if (listener.accept(*fooSocket) == sf::Socket::Done) {
            std::cout << "asd123" << std::endl;
            socket.push_back(std::move(fooSocket));
            std::cout << socket[socket.size() - 1]->getRemoteAddress() << ": Connected" << std::endl;
            socket[socket.size() - 1]->getRemoteAddress();
        }
        sendInput();
    }
}

int main() {
    sf::Thread* serverCr = nullptr;
    serverCr = new sf::Thread(&createServer);
    serverCr->launch();

    sf::Thread * thread = nullptr;
    thread = new sf::Thread(&getInfo);
    thread->launch();

    if(serverCr) {
        thread->wait();
        delete thread;
    }

    if(thread) {
        thread->wait();
        delete thread;
    }

    return 0;

}
