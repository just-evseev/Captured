#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <thread>

#include "../include/MapRender.h"

//static sf::Mutex globalMutex;

const unsigned short PORT = 5000;

bool quit = false;

std::vector<std::unique_ptr<sf::TcpSocket>> socket;

void getInfo() {
    sf::TcpListener listener;
    if (listener.listen(PORT) != sf::Socket::Done) {
        puts("Error in listen");
        exit(1);
    }
    listener.setBlocking(false);
    std::cout << "Server created" << std::endl;

    MapRender mapRender;

    while(!quit) {
        std::unique_ptr<sf::TcpSocket> fooSocket = std::make_unique<sf::TcpSocket>();

        if (listener.accept(*fooSocket) == sf::Socket::Done) {
            (*fooSocket).setBlocking(false);
            socket.push_back(std::move(fooSocket));
            std::cout << socket[socket.size() - 1]->getRemoteAddress() << ": Connected" << std::endl;
        }

        for (int i = 0; i < socket.size(); ++i) {

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

            int msg;

            if (packetReceive >> msg) {
//                if (msg == "exit") {
//                    std::cout << socket[i]->getRemoteAddress() << ": Disconnect" << std::endl;
//                    socket.erase(socket.end() - 1);
//                    continue;
//                }
                std::cout << socket[i]->getRemoteAddress() << ": " << msg << std::endl;

                switch (msg) {
                    case 0:
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    default:
                        std::cout << socket[i]->getRemoteAddress() << ": Incorrect value" << std::endl;
                        break;
                }
            }

        }
    }
}

int main() {

    getInfo();

    return 0;

}
