//
// Created by Святослав Кряжев on 09.12.2018.
//

/*
 * This type of object is movable to the map
 * and movable to the window
 */

#ifndef GRAPHICS_MOVINGOBJECT_H
#define GRAPHICS_MOVINGOBJECT_H

#include "Object.h"

class MovingObject : public Object {
 protected:
    Move current_direction;

 public:
    using Object::Object;

    void move(Move direction, float distance) {
        float alpha = ANGLE_UNIT * direction;
        float beta = ANGLE_UNIT * direction;

        float dx = (sin(beta) - sin(alpha)) * distance;
        float dy = (cos(beta) - cos(alpha)) * distance;

        sprite.move(dx, dy);
    }
};

#endif //GRAPHICS_MOVINGOBJECT_H
