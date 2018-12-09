//
// Created by Святослав Кряжев on 09.12.2018.
//

#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Move.h"

#define ANGLE_UNIT 60.f


class Object : public sf::Drawable, public sf::Transformable {
 protected:
    sf::Sprite sprite;

 public:
    /*explicit Object(sf::Texture& texture) : sprite(texture) {
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    };*/

    virtual void move(Move direction, float distance) = 0;

    void set_texture(sf::Texture& texture) {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    }

    void set_position(float x, float y) {
        sprite.setPosition(x, y);
    }

    void set_position(sf::Vector2f pos) {
        sprite.setPosition(pos);
    }

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();

        target.draw(sprite, states);
    }
};

#endif //GRAPHICS_OBJECT_H
