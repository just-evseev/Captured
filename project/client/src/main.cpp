#include <iostream>
#include <SFML/Network.hpp>
#include <thread>
#include <map>

#include "../include/Hex.h"

const unsigned short PORT = 5001;
const std::string IPADDRESS = "172.20.10.14";

sf::TcpSocket socket;
bool quit = false;

typedef std::vector<Hex> PlayerArea;
typedef std::vector<Hex> PlayerTails;

struct Person {
    int move;
    Hex point;
    PlayerArea playerArea;
    PlayerTails playerTails;
    Person(Hex point)
            :move(0), point(point) {};
};

typedef std::map<int, Person> Persons;

void Client()
{
    while(!quit)
    {
//        int s = 0;
//        std::cin >> s; // залочить ввод
////        s = getEnum();
//        sf::Packet packetSend;
//        packetSend << s;
//        sf::Socket::Status status = socket.send(packetSend);
//        if (status != sf::Socket::Done) {
//
//        }

        sf::Packet packet;
        sf::Socket::Status Status = socket.receive(packet);
        if (Status == sf::Socket::Done) {
            Persons persons;

            int idCount = 0;
            int currId = 0;
            int currMove = 0;
            int currQ = 0;
            int currR = 0;
            packet >> idCount >> currId;
            for (int i = 0; i < idCount; ++i) {
                int areaSize = 0;
                int tailsSize = 0;
                int thisId = 0;
                packet >> thisId >> currQ >> currR >> currMove >> areaSize;
                Person person(Hex(currQ, currR));
                persons.emplace(thisId, person);
                persons.at(thisId).move = currMove;
                for (int k = 0; k < areaSize; ++k) {
                    packet >> currQ >> currR;
                    persons.at(thisId).playerArea.push_back(Hex(currQ, currR));
                }
                packet >> tailsSize;
                for (int k = 0; k < tailsSize; ++k) {
                    packet >> currQ >> currR;
                    persons.at(thisId).playerTails.push_back(Hex(currQ, currR));
                }
            }
            std::cout << " + " << persons.size() << persons.at(currId).point.q << ":" << persons.at(currId).point.r
                      << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    if(socket.connect(IPADDRESS, PORT) != sf::Socket::Done)
    {
        std::cout << "Connection Failed" << std::endl;
        return -1;
    }
    std::cout << "Connected" << std::endl;

    socket.setBlocking(false);

    Client();

    return 0;
}