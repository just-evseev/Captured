//
// Created by Святослав Кряжев on 05.12.2018.
//

#include "HexMap.h"

HexMap::HexMap(std::shared_ptr<sf::RenderWindow> window) : window(window) {
        areaTexture.loadFromFile("./Contents/sprites/territoria_bez_sveta.png");

        window_size = window->getSize();
};

void HexMap::prepare(std::map<Hex, int>& areas) {
    for (auto& area : areas) {
        sf::Sprite areaTile;
        areaTile.setTexture(areaTexture);

        areaTile.setOrigin(areaTexture.getSize().x / 2.f, areaTexture.getSize().y / 2.f);

        areaTile.setPosition(pixel(area.first));

        areaTiles.push_back(areaTile);
    }
}

sf::Vector2f HexMap::pixel(Hex hex) {
    float x = window_size.x / 2.f + hex_size * 3.f / 2.f * hex.q;
    float y = window_size.y / 2.f + hex_size * sqrt(3.f) * (hex.r + hex.q / 2.f);

    return sf::Vector2f(x, y);
}

void HexMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto& tile : areaTiles)
        target.draw(tile);
}