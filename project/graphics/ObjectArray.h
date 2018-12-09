//
// Created by Святослав Кряжев on 09.12.2018.
//

#ifndef GRAPHICS_OBJECTARRAY_H
#define GRAPHICS_OBJECTARRAY_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Object.h"
#include "Move.h"

class ObjectArray : public sf::Drawable, public sf::Transformable {
 protected:
    std::vector<std::unique_ptr<Object>> objects;

 public:
    void move(Move direction, float distance) {
        for (auto& object : objects)
            object->move(direction, distance);
    }

    void push(std::unique_ptr<Object>&& object) {
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
