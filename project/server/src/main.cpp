#include <iostream>
#include <vector>
#include <SFML/Network.hpp>

#include "../include/RenderManager.h"

const unsigned short PORT = 5001;

bool quit = false;

void serverCycle() {
    sf::TcpListener listener;
    if (listener.listen(PORT) != sf::Socket::Done) {
        puts("Error in listen");
        exit(1);
    }
    listener.setBlocking(false);
    std::cout << "Server created" << std::endl;

    std::vector<std::unique_ptr<sf::TcpSocket>> sockets;
    RenderManager rM;

    int personId = 0;
    sf::Clock clock;

    while(!quit) {
        std::unique_ptr<sf::TcpSocket> fooSocket = std::make_unique<sf::TcpSocket>();

        if (listener.accept(*fooSocket) == sf::Socket::Done) {
            (*fooSocket).setBlocking(false);
            sockets.push_back(std::move(fooSocket));
            std::cout << sockets[sockets.size() - 1]->getRemoteAddress() << ": Connected with id " << personId << std::endl;
            rM.acceptPlayer(personId);
            personId += 1;
        }

        for (int i = 0; i < sockets.size(); ++i) {

            sf::Packet packetReceive;
            sf::Socket::Status Status = sockets[i]->receive(packetReceive);

            if (Status == sf::Socket::Disconnected) {
                std::cout << sockets[i]->getRemoteAddress() << ": Disconnect (id = " << ")" << std::endl;
                sockets.erase(sockets.end() - 1);
                continue;
            }

            if (Status != sf::Socket::Done) {
                continue;
            }

            int msg;

            if (packetReceive >> msg) {
                std::cout << std::endl << sockets[i]->getRemoteAddress() << ": " << msg << std::endl;
                switch (msg) {
                case 0:
                    rM.updateEnum(i, Move::UP);
                    break;
                case 1:
                    rM.updateEnum(i, Move::RIGHT_UP);
                    break;
                case 2:
                    rM.updateEnum(i, Move::RIGHT_DOWN);
                    break;
                case 3:
                    rM.updateEnum(i, Move::DOWN);
                    break;
                case 4:
                    rM.updateEnum(i, Move::LEFT_DOWN);
                    break;
                case 5:
                    rM.updateEnum(i, Move::LEFT_UP);
                    break;
                default:
                    std::cout << i << ": Incorrect value" << std::endl;
                    break;
                }

            }
        }

        sf::Time time = clock.getElapsedTime();
        auto timeInMS = time.asMilliseconds();
        if (timeInMS >= 333) {
            for (int i = 0; i < sockets.size(); ++i) {
                rM.updateAt(i);
                sf::Packet packet;
                auto size = (int)sockets.size();
                packet << size << i; //<< rM.persons.at(i).point.q << rM.persons.at(i).point.r;
                for (int j = 0; j < size; ++j) {
                    auto areaSize = (int)rM.persons.at(j).playerArea.size();
                    auto tailsSize = (int)rM.persons.at(j).playerTails.size();
                    packet << j << rM.persons.at(j).point.q << rM.persons.at(j).point.r << rM.persons.at(j).move << areaSize;
                    for (int k = 0; k < areaSize; ++k) {
                        packet << rM.persons.at(j).playerArea.at(k).q << rM.persons.at(j).playerArea.at(k).r;
                    }
                    packet << tailsSize;
                    for (int k = 0; k < tailsSize; ++k) {
                        packet << rM.persons.at(j).playerTails.at(k).q << rM.persons.at(j).playerTails.at(k).r;
                    }
                }
                sf::Socket::Status Status = sockets[i]->send(packet);
                if (Status != sf::Socket::Done) {
                    std::cout << "Error in send packet to user with id " << i << std::endl;
                }
            }
            clock.restart();
        }
    }
}

int main() {

    serverCycle();

    return 0;

}
