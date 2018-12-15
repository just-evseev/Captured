//
//
//

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GraphicsController.h"
#include "MouseController.h"
#include "Client2ServerParser.h"
#include "Server2ClientParser.h"
#include "DataPacket.h"
#include "Move.h"

#include "TextureOwner.h"



#define PROGRAM_NAME    "Captured: client"
#define WIDTH           2880
#define HEIGHT          1800

int main() {
    auto windowObj = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), PROGRAM_NAME, sf::Style::Fullscreen);
    auto& window = *windowObj;

//    PacketGenerator pg;
//    pg.pack(Move::LEFT_DOWN);
//    pg.unpack();

    window.setVerticalSyncEnabled(true);

    window.setMouseCursorVisible(false); // Hide cursor
    auto mouse = std::make_shared<MouseController>(windowObj);


    GraphicsController graph(windowObj, mouse);

    auto data = std::make_shared<DataPacket>();
    graph.update(data);


    // Main cycle
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }



        // Draw part
        graph.draw();

        window.display();
    }

    return 0;
}