//
// Created by Святослав Кряжев on 08.12.2018.
//

#ifndef GRAPHICS_MOUSECONTROLLER_H
#define GRAPHICS_MOUSECONTROLLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


#define PI 3.14159265f


class MouseController {
    std::shared_ptr<sf::RenderWindow> window;
    sf::Vector2f origin;

 public:
    explicit MouseController(std::shared_ptr<sf::RenderWindow> window);
    ~MouseController();

    // Getters
    sf::Vector2i get_position();
    sf::Vector2f get_positionf();
    float get_angle();
    float get_angle_deg();

    // Setters
    void set_origin(sf::Vector2f position);
    void set_origin(float x, float y);
    void set_default_origin();

    void set_position(sf::Vector2i position);
    void set_position(int x, int y);
};


#endif //GRAPHICS_MOUSECONTROLLER_H
