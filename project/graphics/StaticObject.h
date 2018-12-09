//
// Created by Святослав Кряжев on 09.12.2018.
//

/*
 * This type of object is stationary to the window
 */

#ifndef GRAPHICS_STATICOBJECT_H
#define GRAPHICS_STATICOBJECT_H

#include <iostream>

#include "Object.h"

class StaticObject : public Object {
 public:
    using Object::Object;

    void move(Move direction, float distance) override {
        std::cerr << "Error: trying to move static object" << std::endl;
    }

};

#endif //GRAPHICS_STATICOBJECT_H
