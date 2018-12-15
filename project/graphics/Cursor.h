//
// Created by Святослав Кряжев on 08.12.2018.
//

#ifndef GRAPHICS_CURSOR_H
#define GRAPHICS_CURSOR_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "MouseController.h"

class Cursor : public sf::Drawable {
    sf::Sprite sprite;

    std::shared_ptr<MouseController> mouse;

 public:
    explicit Cursor(std::shared_ptr<MouseController> mouse)
                                              : mouse(mouse) {};

    void set_texture(sf::Texture& texture) {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    };

    void update() {
        sprite.setPosition(mouse->get_positionf());
    };

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite);
    };
};


#endif  // GRAPHICS_CURSOR_H
