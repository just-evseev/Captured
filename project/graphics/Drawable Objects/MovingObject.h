//
// Created by Святослав Кряжев on 09.12.2018.
//

/*
 * This type of object is movable to the map
 * and movable to the window
 */

#ifndef GRAPHICS_MOVINGOBJECT_H
#define GRAPHICS_MOVINGOBJECT_H

#include "MovableObject.h"

#define PI 3.14159265f

class MovingObject : public MovableObject {
 protected:
    Move current_direction;

 public:
    void set_movement(Move direction, float distance) override {
        float alpha = (ANGLE_UNIT * PI) / 180 * direction;
        float beta = (ANGLE_UNIT * PI) / 180 * current_direction;

        dx = (sin(beta) - sin(alpha)) * distance;
        dy = (-cos(beta) + cos(alpha)) * distance;
    }

    void set_move(Move move) {
        current_direction = move;
    }

    void set_color() {
        sprite.setColor(sf::Color(0, 255, 0));
    }
};

#endif //GRAPHICS_MOVINGOBJECT_H
