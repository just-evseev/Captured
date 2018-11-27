//
//
//

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GraphicsController.h"
#include "DataPacket.h"


#define PROGRAM_NAME    "Captured: client"
#define WIDTH           1600
#define HEIGHT          1200

void test_fill(DataPacket& data);

int main() {
    auto windowObj = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), PROGRAM_NAME, sf::Style::Close);
    auto& window = *windowObj;

    GraphicsController graph(windowObj);

    auto dataObj = std::make_shared<DataPacket>();
    auto& data = *dataObj;

    test_fill(data);

    int task = 0;

    // Main cycle
    while (window.isOpen()) {
        switch (task) {
            case 1:
                data.move_up(-1.f);
                break;
            case 2:
                data.move_down(-1.f);
                break;
            case 3:
                data.move_right(-1.f);
                break;
            case 4:
                data.move_left(-1.f);
                break;

            default:
                break;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Up key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                task = 1;
                // std::cout << "(" << data.areas[0].points[0].x << " : " << data.areas[0].points[0].y << ")" << std::endl;
            }

            // Down key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                task = 2;
                // std::cout << "(" << data.areas[0].points[0].x << " : " << data.areas[0].points[0].y << ")" << std::endl;
            }

            // Right key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                task = 3;
                // std::cout << "(" << data.areas[0].points[0].x << " : " << data.areas[0].points[0].y << ")" << std::endl;
            }

            // Left key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                task = 4;
                // std::cout << "(" << data.areas[0].points[0].x << " : " << data.areas[0].points[0].y << ")" << std::endl;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                task = 0;
                // std::cout << "(" << data.areas[0].points[0].x << " : " << data.areas[0].points[0].y << ")" << std::endl;
            }
        }

        // Draw part
        window.clear();

        graph.update(dataObj);
        graph.draw();

        window.display();
    }

    return 0;
}

void test_fill(DataPacket& data) {
    DataPacket::Area area1;
    area1.id = 1;

    area1.points.emplace_back(sf::Vector2f(1200.f, 800.f));
    area1.points.emplace_back(sf::Vector2f(1200.f, 600.f));
    area1.points.emplace_back(sf::Vector2f(1800.f, 600.f));
    area1.points.emplace_back(sf::Vector2f(1800.f, 300.f));
    area1.points.emplace_back(sf::Vector2f(2000.f, 300.f));
    area1.points.emplace_back(sf::Vector2f(2000.f, 1600.f));
    area1.points.emplace_back(sf::Vector2f(1000.f, 1600.f));
    area1.points.emplace_back(sf::Vector2f(1000.f, 800.f));

    data.areas.push_back(area1);

    DataPacket::Area area2;
    area2.id = 2;

    area2.points.emplace_back(sf::Vector2f(400.f, 800.f));
    area2.points.emplace_back(sf::Vector2f(400.f, 700.f));
    area2.points.emplace_back(sf::Vector2f(200.f, 700.f));
    area2.points.emplace_back(sf::Vector2f(200.f, 500.f));
    area2.points.emplace_back(sf::Vector2f(-400.f, 500.f));
    area2.points.emplace_back(sf::Vector2f(-400.f, 800.f));

    data.areas.push_back(area2);
}