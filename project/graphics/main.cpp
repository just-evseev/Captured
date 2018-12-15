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
#define FPS             60

int main() {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), PROGRAM_NAME, sf::Style::Fullscreen);

    window->setVerticalSyncEnabled(true);

    auto mouse = std::make_shared<MouseController>(window);
    mouse->set_visible(false);

    GraphicsController graph(window, mouse);

    auto data = std::make_shared<DataPacket>();
    graph.update(data);

    int speed = 3;
    int tacts = FPS / speed;
    int i = tacts;

    Move direction;

    // Main cycle
    while (window->isOpen()) {

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window->close();
        }

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
            graph.set_direction(direction);
            i = tacts;
        }

        graph.draw();

        window->display();
        i--;
    }

    return 0;
}