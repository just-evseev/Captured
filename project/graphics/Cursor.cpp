//
// Created by Святослав Кряжев on 08.12.2018.
//

#include "Cursor.h"

Cursor::Cursor(std::shared_ptr<MouseController> mouse)
                        : mouse(mouse) {
    std::clog << "Cursor: created" << std::endl;

    texture.loadFromFile("./Contents/sprites/Kursor.png");

    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}

Cursor::~Cursor() {
    std::clog << "Cursor: destroyed" << std::endl;
}

void Cursor::update() {
    sprite.setPosition(mouse->get_positionf());
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}