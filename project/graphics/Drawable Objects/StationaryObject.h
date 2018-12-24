//
// Created by Святослав Кряжев on 09.12.2018.
//

/*
 * This type of object is stationary to the map
 * but is movable to the window
 */

#ifndef GRAPHICS_STATIONARYOBJECT_H
#define GRAPHICS_STATIONARYOBJECT_H

#include "MovableObject.h"

#define PI 3.14159265f

class StationaryObject : public MovableObject {
 public:
    void set_movement(Move direction, float distance) override {
        float alpha = (ANGLE_UNIT * PI) / 180 * direction;

        dx = -distance * sin(alpha);
        dy = distance * cos(alpha);
    }

    void set_color() {
        sprite.setColor(sf::Color(0, 255, 0));
    }

    void set_alpha() {
        sprite.setColor(sf::Color(255, 255, 255, 128));
    }

};

#endif //GRAPHICS_STATIONARYOBJECT_H
