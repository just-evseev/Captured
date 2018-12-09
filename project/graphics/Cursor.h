//
// Created by Святослав Кряжев on 08.12.2018.
//

#ifndef GRAPHICS_CURSOR_H
#define GRAPHICS_CURSOR_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "MouseController.h"

class Cursor : public sf::Drawable, public sf::Transformable {
    sf::Texture texture;
    sf::Sprite sprite;

    std::shared_ptr<MouseController> mouse;

 public:
    explicit Cursor(std::shared_ptr<MouseController> mouse);
    ~Cursor();

    void update();

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif  // GRAPHICS_CURSOR_H
