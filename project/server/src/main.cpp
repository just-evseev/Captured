#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <thread>

#include "../include/RenderManager.h"

const unsigned short PORT = 5000;

bool quit = false;

void serverCycle() {
    sf::TcpListener listener;
    if (listener.listen(PORT) != sf::Socket::Done) {
        puts("Error in listen");
        exit(1);
    }
    listener.setBlocking(false);
    std::cout << "Server created" << std::endl;

    std::vector<std::unique_ptr<sf::TcpSocket>> socket;
    RenderManager renderManager;

    int personId = 0;

    while(!quit) {
        std::unique_ptr<sf::TcpSocket> fooSocket = std::make_unique<sf::TcpSocket>();

        if (listener.accept(*fooSocket) == sf::Socket::Done) {
            (*fooSocket).setBlocking(false);
            socket.push_back(std::move(fooSocket));
            std::cout << socket[socket.size() - 1]->getRemoteAddress() << ": Connected" << std::endl;
            renderManager.acceptPlayer(personId);
            personId += 1;
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

//            sf::Packet packetSend;
//            if (msgSend.empty())
//                continue;
//            packetSend << msgSend;
//            msgSend = "";
//            socket[i]->send(packetSend);

            int msg;

            if (packetReceive >> msg) {
                std::cout << std::endl << socket[i]->getRemoteAddress() << ": " << msg << std::endl;
                switch (msg) {
                case 0:
                    renderManager.getPlayerCoord(Move::UP, i);
                    break;
                case 1:
                    renderManager.getPlayerCoord(Move::RIGHT_UP, i);
                    break;
                case 2:
                    renderManager.getPlayerCoord(Move::RIGHT_DOWN, i);
                    break;
                case 3:
                    renderManager.getPlayerCoord(Move::DOWN, i);
                    break;
                case 4:
                    renderManager.getPlayerCoord(Move::LEFT_DOWN, i);
                    break;
                case 5:
                    renderManager.getPlayerCoord(Move::LEFT_UP, i);
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

    serverCycle();

    return 0;

}
