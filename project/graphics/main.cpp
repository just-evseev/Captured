#include <iostream>
#include <SFML/Network.hpp>
#include <thread>
#include <map>

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GraphicsController.h"
#include "MouseController.h"
#include "DataPacket.h"
#include "Move.h"

#define PROGRAM_NAME    "Captured: client"
#define WIDTH           2880
#define HEIGHT          1800
#define FPS             60


const unsigned short PORT = 5000;
const std::string IPADDRESS("172.20.10.14");

sf::TcpSocket socket;
bool quit = false;

typedef std::map<int, Person> Persons;

// GLOBAL VARIABLES (sh*t)

Person me(Hex(0, 0));
Move direction;

// END DECLARATION

void GetInput()
{
    while(!quit)
    {
        sf::Packet packetSend;
        packetSend << (int) direction;
        socket.send(packetSend);
    }
}

void packetParser() {
    while (!quit) {
        sf::Packet packet;
        sf::Socket::Status Status = socket.receive(packet);
        if (Status != sf::Socket::Done) {
            continue;
        }

        Persons persons;

        int idCount = 0;
        int currId = 0;
        int currMove = 0;
        int currQ = 0;
        int currR = 0;
        packet >> idCount >> currId; //>> currMove >> currQ >> currR;
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
            packet << tailsSize;
            for (int k = 0; k < tailsSize; ++k) {
                packet >> currQ >> currR;
                persons.at(thisId).playerTails.push_back(Hex(currQ, currR));
            }
        }
        std::cout << " + " << persons.at(currId).point.q << ":" << persons.at(currId).point.r << std::endl;

        me = persons.at(0);
    }
}

int main(int argc, char* argv[])
{
    if(socket.connect(IPADDRESS, PORT) != sf::Socket::Done)
    {
        std::cout << "Connection Failed" << std::endl;
        return -1;
    }
    std::cout << "Connected\n";

    sf::Thread* thread = nullptr;
    thread = new sf::Thread(&packetParser);
    thread->launch();

    GetInput();

    thread->wait();
    delete thread;

    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), PROGRAM_NAME, sf::Style::Fullscreen);

    window->setVerticalSyncEnabled(true);
    /// Use next line if speed is too fast & comment previous line
    //window->setFramerateLimit(60);

    auto mouse = std::make_shared<MouseController>(window);
    mouse->set_visible(false);

    GraphicsController graph(window, mouse);

    auto data = std::make_shared<DataPacket>();
    graph.update(data);

    int speed = 3;
    int tacts = FPS / speed;
    int i = tacts;


    // Main cycle

    while (window->isOpen()) {

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window->close();
        }

        // Getting current direction
        Move momental_direction;

        float angle = mouse->get_angle_deg();

        if (angle >= -120.f && angle < -60.f)
            momental_direction = UP;
        else if (angle >= -60.f && angle < 0.f)
            momental_direction = RIGHT_UP;
        else if (angle >= 0.f && angle < 60.f)
            momental_direction = RIGHT_DOWN;
        else if (angle >= 60.f && angle < 120.f)
            momental_direction = DOWN;
        else if (angle >= 120.f && angle < 180.f)
            momental_direction = LEFT_DOWN;
        else if (angle >= -180.f && angle < -120.f)
            momental_direction = LEFT_UP;

        if (abs(momental_direction - graph.get_direction()) != 3)
            direction = momental_direction;

        // Draw part
        if (!i) {
            data->make(me);
            graph.update(data);
            graph.set_direction(Move(me.move));
            i = tacts;
        }
        i--;

        graph.draw();

        window->display();
    }

    return 0;
}