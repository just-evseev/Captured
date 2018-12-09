//
// Created by Святослав Кряжев on 08.12.2018.
//

#include "MouseController.h"

MouseController::MouseController(std::shared_ptr<sf::RenderWindow> window)
 : window(window), origin(window->getSize().x / 2.f, window->getSize().y / 2.f) {
    std::clog << "Mouse controller: created" << std::endl;
}

MouseController::~MouseController() {
    std::clog << "Mouse controller: destroyed" << std::endl;
}


// Getters
sf::Vector2i MouseController::get_position() {
    return sf::Mouse::getPosition(*window);
}

sf::Vector2f MouseController::get_positionf() {
    return sf::Vector2f(sf::Mouse::getPosition(*window));
}

float MouseController::get_angle() {
    sf::Vector2i position = sf::Mouse::getPosition(*window);

    return atan2f(position.y - origin.y, position.x - origin.x);
}

float MouseController::get_angle_deg() {
    sf::Vector2i position = sf::Mouse::getPosition(*window);

    return atan2f(position.y - origin.y, position.x - origin.x) * 180.f / PI;
}

// Setters
void MouseController::set_origin(sf::Vector2f position) {
    origin = position;
}

void MouseController::set_origin(float x, float y) {
    origin.x = x;
    origin.y = y;
}

void MouseController::set_default_origin() {
    origin.x = window->getSize().x / 2.f;
    origin.y = window->getSize().y / 2.f;
}

void MouseController::set_position(sf::Vector2i position) {
    sf::Mouse::setPosition(position, *window);
}

void MouseController::set_position(int x, int y) {
    sf::Mouse::setPosition(sf::Vector2i(x, y), *window);
}