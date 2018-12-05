//
// Created by Святослав Кряжев on 05.12.2018.
//

#ifndef GRAPHICS_HEXMAP_H
#define GRAPHICS_HEXMAP_H

#include <SFML/Graphics.hpp>
#include <queue>
#include <map>
#include <math.h>

#include "Hex.h"

class HexMap : public sf::Drawable, public sf::Transformable {
 public:
    explicit HexMap(std::shared_ptr<sf::RenderWindow> window);
    ~HexMap() = default;

    void prepare(std::map<Hex, int>& areas);



 private:
    // Fields
    std::shared_ptr<sf::RenderWindow> window;

    sf::Vector2u window_size;

    float hex_size = 59;

    mutable std::queue<sf::Sprite> areaTiles;
    std::queue<sf::Sprite> tailTiles;

    sf::Texture areaTexture;

    // Methods
    sf::Vector2f pixel(Hex hex);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //GRAPHICS_HEXMAP_H
