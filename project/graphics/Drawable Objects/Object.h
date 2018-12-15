//
// Created by Святослав Кряжев on 09.12.2018.
//

#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Move.h"

#define ANGLE_UNIT 60.f

class SpriteListManager {
    uint lines = 1;
    uint cols = 1;

    sf::Vector2u single_size;
    sf::Vector2u current_position;

 public:
    SpriteListManager(sf::Vector2u single_size, uint lines, uint cols)
    : lines(lines), cols(cols), single_size(single_size),
    current_position(0, 0) {};

    sf::IntRect get(uint col, uint line) {
        return sf::IntRect(single_size.x * col, single_size.y * line, single_size.x, single_size.y);
    }

    bool compatible(uint col, uint line) {
        return col < cols && line < lines;
    }
};


class Object : public sf::Drawable, public sf::Transformable {
 protected:
    sf::Sprite sprite;
    uint lines = 1;
    uint cols = 1;

    sf::Vector2u single_size;
    sf::Vector2u current_;

    std::unique_ptr<SpriteListManager> spriteList;

 public:
    void set_up(sf::Texture& texture, uint cols = 1, uint lines = 1) {
        sprite.setTexture(texture);

        sf::Vector2u single_size = texture.getSize();

        if (lines > 1 || cols > 1) {
            single_size.x /= cols;
            single_size.y /= lines;

            spriteList = std::make_unique<SpriteListManager>(single_size, lines, cols);

            sprite.setTextureRect(sf::IntRect(0, 0, single_size.x, single_size.y));
        }

        sprite.setOrigin(single_size.x / 2.f, single_size.y / 2.f);
    }

    void choose_texture(uint col, uint line = 0) {
        if (spriteList->compatible(col, line))
            sprite.setTextureRect(spriteList->get(col, line));
    }



 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();

        target.draw(sprite, states);
    }
};

#endif //GRAPHICS_OBJECT_H
