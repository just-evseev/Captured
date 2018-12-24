//
// Created by Святослав Кряжев on 09.12.2018.
//

#ifndef GRAPHICS_OBJECTARRAY_H
#define GRAPHICS_OBJECTARRAY_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "MovableObject.h"
#include "Move.h"

class MovableObjectArray : public sf::Drawable, public sf::Transformable {
 protected:
    std::vector<std::unique_ptr<MovableObject>> objects;

 public:
    void set_movement(Move direction, float distance) {
        for (auto& object : objects)
            object->set_movement(direction, distance);
    }

    void move() {
        for (auto& object : objects)
            object->move();
    }

    void push(std::unique_ptr<MovableObject>&& object) {
        objects.push_back(std::move(object));
    }

    void drop() {
        objects.clear();
    }

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        for (auto& object : objects)
            target.draw(*object);
    }
};

#endif //GRAPHICS_OBJECTARRAY_H
