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

#include "DataPacket.h"
#include "Cursor.h"
#include "MouseController.h"

#include "ObjectArray.h"
#include "MovingObject.h"
#include "StationaryObject.h"

#include "HexSpace.h"

#include "TextureOwner.h"


class GraphicsController {
    std::shared_ptr<sf::RenderWindow> window;
    sf::Vector2u size;

    std::shared_ptr<DataPacket> data;

    std::shared_ptr<MouseController> mouse;
    Cursor cursor;

    HexSpace hexSpace;

    StationaryObject grid;
    Object background;
    Object player;
    Object light;
    Object reflection;

    sf::Texture lightT;
    sf::Texture reflectionT;

    TextureOwner texturePack;

    Move mov;
    int i = 0;


 public:
    explicit GraphicsController(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MouseController> mouse);
    ~GraphicsController();

    void update(std::shared_ptr<DataPacket> data);
    void draw();
};


#endif //GRAPHICS_GRAPHICSCONTROLLER_H
