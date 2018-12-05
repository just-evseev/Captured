//
// Created by Святослав Кряжев on 25.11.2018.
//

#include "GraphicsController.h"


GraphicsController::GraphicsController(std::shared_ptr<sf::RenderWindow> window)
                            : window(window), size(window->getSize()),
                              hexMap(window), data(nullptr) {

    backgroundTexture.loadFromFile("./Contents/sprites/Fon.png");

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0.f, 0.f);

    gridTexture.loadFromFile("./Contents/sprites/grid.png");

    gridSprite.setTexture(gridTexture);

    sf::Vector2f size1(gridTexture.getSize());

    gridSprite.setOrigin(size1.x / 2.f, size1.y / 2.f);
    gridSprite.setPosition(this->size.x / 2.f, this->size.y / 2.f);


    playerTexture.loadFromFile("./Contents/sprites/Igrok.png");

    playerSprite.setTexture(playerTexture);

    sf::Vector2f size(playerTexture.getSize());

    playerSprite.setOrigin(size.x / 2.f, size.y / 2.f);
    playerSprite.setPosition(this->size.x / 2.f, this->size.y / 2.f);

    std::clog << "GraphicsController: created" << std::endl;
}

GraphicsController::~GraphicsController() {
    std::clog << "GraphicsController: destroyed" << std::endl;
}

void GraphicsController::update(std::shared_ptr<DataPacket> data) {
    this->data = data;
    hexMap.prepare(data->areas);
}

void GraphicsController::draw() {
    window->draw(backgroundSprite);

    window->draw(gridSprite);

    window->draw(hexMap);

    window->draw(playerSprite);
}