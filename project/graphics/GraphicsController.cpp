//
// Created by Святослав Кряжев on 25.11.2018.
//

#include "GraphicsController.h"

GraphicsController::GraphicsController(std::shared_ptr<sf::RenderWindow> window)
                            : window(window), size(window->getSize()),
                            player(sf::Vector2f(size.x/2 - 30, size.y/2 - 30)),
                            data(nullptr) {

    std::clog << "GraphicsController: created" << std::endl;
}

GraphicsController::~GraphicsController() {
    std::clog << "GraphicsController: destroyed" << std::endl;
}

void GraphicsController::update(std::shared_ptr<DataPacket> data) {
    this->data = data;
}

void GraphicsController::draw() {
    for (auto& area : data->areas) {
        sf::ConvexShape convex;

        size_t count = area.points.size();
        convex.setPointCount(count);

        for (size_t i = 0; i < count; ++i)
            convex.setPoint(i, area.points.at(i));

        switch (area.id) {
            case 1:
                convex.setFillColor(sf::Color::Blue);
                break;

            case 2:
                convex.setFillColor(sf::Color::Red);
                break;

            default:
                convex.setFillColor(sf::Color::Green);
                break;
        }

        window->draw(convex);
    }

    sf::RectangleShape player(this->player.get_size());
    player.setPosition(this->player.get_pos());

    player.setFillColor(sf::Color::White);

    window->draw(player);
}