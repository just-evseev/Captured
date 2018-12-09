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
#include "HexMap.h"
#include "Cursor.h"
#include "MouseController.h"

#include "ObjectArray.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include "StationaryObject.h"

#include "HexSpace.h"


class GraphicsController {
    std::shared_ptr<sf::RenderWindow> window;
    sf::Vector2u size;

    std::shared_ptr<DataPacket> data;

    std::shared_ptr<MouseController> mouse;
    Cursor cursor;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture gridTexture;
    sf::Sprite gridSprite;

    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    sf::Texture areaTexture;

    HexMap hexMap;

    ObjectArray areas;
    ObjectArray players;

    HexSpace hexSpace;

    StationaryObject grid;

    Move mov;
    int i = 0;


 public:
    explicit GraphicsController(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MouseController> mouse);
    ~GraphicsController();

    void update(std::shared_ptr<DataPacket> data);
    void draw();
};


#endif //GRAPHICS_GRAPHICSCONTROLLER_H
