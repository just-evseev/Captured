#include <iostream>
#include <vector>
#include <SFML/Network.hpp>

#include "../include/RenderManager.h"

const unsigned short PORT = 5001;

bool quit = false;

void serverCycle() {
    sf::TcpListener listener;
    if (listener.listen(PORT) != sf::Socket::Done) {
        puts("SERVER DONT CREATED");
        exit(1);
    }
    listener.setBlocking(false);
    std::cout << "Server created" << std::endl;

    std::vector<std::unique_ptr<sf::TcpSocket>> sockets;
    std::vector<int> playersId;
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
            playersId.push_back(personId);
            personId += 1;
        }

        for (int i = 0; i < sockets.size(); ++i) {

            sf::Packet packetReceive;
            sf::Socket::Status Status = sockets[i]->receive(packetReceive);

            if (Status == sf::Socket::Disconnected) {
                std::cout << sockets[i]->getRemoteAddress() << ": Disconnect (id = " << ")" << std::endl;
                sockets.erase(sockets.begin() + i);
                for (auto kek : rM.tails) {
                    if (kek.second.id == playersId[i]) {
                        rM.tails.erase(kek.first);
                    }
                }
                for (auto kek : rM.areas) {
                    if (kek.second == playersId[i]) {
                        rM.tails.erase(kek.first);
                    }
                }
                rM.persons.erase(playersId[i]);
                playersId.erase(playersId.begin() + i);
                continue;
            }

            if (Status != sf::Socket::Done) {
                continue;
            }

            int msg;

            if (packetReceive >> msg) {
//                std::cout << std::endl << sockets[i]->getRemoteAddress() << ": " << msg << std::endl;
                switch (msg) {
                case 0:
                    rM.updateEnum(playersId[i], Move::UP);
                    break;
                case 1:
                    rM.updateEnum(playersId[i], Move::RIGHT_UP);
                    break;
                case 2:
                    rM.updateEnum(playersId[i], Move::RIGHT_DOWN);
                    break;
                case 3:
                    rM.updateEnum(playersId[i], Move::DOWN);
                    break;
                case 4:
                    rM.updateEnum(playersId[i], Move::LEFT_DOWN);
                    break;
                case 5:
                    rM.updateEnum(playersId[i], Move::LEFT_UP);
                    break;
                default:
                    std::cout << playersId[i] << ": Incorrect value" << std::endl;
                    break;
                }

            }
        }

        sf::Time time = clock.getElapsedTime();
        auto timeInMS = time.asMilliseconds();

        if (timeInMS >= 333) {
            clock.restart();
            auto size = (int)sockets.size();
            for (int i = 0; i < sockets.size(); ++i) {
//                std::cout << "Перемещение игрока " << playersId[i] << " = " << rM.persons.at(playersId[i]).move << std::endl;
                sf::Packet packet;
                packet << size << playersId[i];
                for (int j = 0; j < size; ++j) {
                    auto areaSize = (int)rM.persons.at(playersId[j]).playerArea.size();
                    auto tailsSize = (int)rM.persons.at(playersId[j]).playerTails.size();
                    packet << playersId[j] << rM.persons.at(playersId[j]).point.q << rM.persons.at(playersId[j]).point.r;
                    packet << rM.persons.at(playersId[j]).move << areaSize;
                    for (int k = 0; k < areaSize; ++k) {
                        packet << rM.persons.at(playersId[j]).playerArea.at(k).q << rM.persons.at(playersId[j]).playerArea.at(k).r;
                    }
                    packet << tailsSize;
                    for (int k = 0; k < tailsSize; ++k) {
                        packet << rM.persons.at(playersId[j]).playerTails.at(k).q << rM.persons.at(playersId[j]).playerTails.at(k).r;
                    }
                }
                sf::Socket::Status Status = sockets[i]->send(packet);
                if (Status != sf::Socket::Done) {
                    std::cout << "Error in send packet to user with id " << i << std::endl;
                }
            }
            for (int i = 0; i < sockets.size(); ++i) {
                rM.updateAt(playersId[i]);
            }
            for (int i = 0; i < size; ++i) {
                if (rM.persons.at(playersId[i]).bonusEffect == 1) {
                    sockets.erase(sockets.begin() + i);
                    for (auto kek : rM.tails) {
                        if (kek.second.id == playersId[i]) {
                            rM.tails.erase(kek.first);
                        }
                    }
                    for (auto kek : rM.areas) {
                        if (kek.second == playersId[i]) {
                            rM.tails.erase(kek.first);
                        }
                    }
                    rM.persons.erase(playersId[i]);
                    playersId.erase(playersId.begin() + i);
                }
            }
        }
    }
}

int main() {

    serverCycle();

    return 0;

}
