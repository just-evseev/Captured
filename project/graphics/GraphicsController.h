//
// Created by Святослав Кряжев on 25.11.2018.
//

#ifndef GRAPHICS_GRAPHICSCONTROLLER_H
#define GRAPHICS_GRAPHICSCONTROLLER_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <memory>

#include "Player.h"
#include "DataPacket.h"


class GraphicsController {
 private:
    std::shared_ptr<sf::RenderWindow> window;
    sf::Vector2u size;

    std::shared_ptr<DataPacket> data;

    Player player;

 public:
    explicit GraphicsController(std::shared_ptr<sf::RenderWindow> window);
    ~GraphicsController();

    void update(std::shared_ptr<DataPacket> data);
    void draw();
};


#endif //GRAPHICS_GRAPHICSCONTROLLER_H
