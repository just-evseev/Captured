//
//
//

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GraphicsController.h"
#include "DataPacket.h"


#define PROGRAM_NAME    "Captured: client"
#define WIDTH           2880
#define HEIGHT          1800

int main() {
    auto windowObj = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), PROGRAM_NAME, sf::Style::Fullscreen);
    auto& window = *windowObj;

    window.setVerticalSyncEnabled(true);

    GraphicsController graph(windowObj);

    auto data = std::make_shared<DataPacket>();

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
        graph.update(data);
        graph.draw();

        window.display();
    }

    return 0;
}