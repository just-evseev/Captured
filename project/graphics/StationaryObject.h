//
// Created by Святослав Кряжев on 09.12.2018.
//

/*
 * This type of object is stationary to the map
 * but is movable to the window
 */

#ifndef GRAPHICS_STATIONARYOBJECT_H
#define GRAPHICS_STATIONARYOBJECT_H

#include "Object.h"

#define PI 3.14159265f

class StationaryObject : public Object {
 public:
    //using Object::Object;

    void move(Move direction, float distance) override {
        float alpha = (ANGLE_UNIT * PI) / 180 * direction;

        float dx = distance * sin(alpha);
        float dy = distance * cos(alpha);

        sprite.move(dx, dy);
    }
};

#endif //GRAPHICS_STATIONARYOBJECT_H
