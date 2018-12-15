//
// Created by Святослав Кряжев on 10.12.2018.
//

#ifndef GRAPHICS_MOVABLEOBJECT_H
#define GRAPHICS_MOVABLEOBJECT_H

#include "Object.h"

class MovableObject : public Object {
 protected:
    float dx;
    float dy;

 public:
    virtual void set_movement(Move direction, float distance) = 0;

    void move() {
        sprite.move(dx, dy);
    };
};

#endif //GRAPHICS_MOVABLEOBJECT_H
