//
// Created by Святослав Кряжев on 09.12.2018.
//

#ifndef GRAPHICS_HEXSPACE_H
#define GRAPHICS_HEXSPACE_H

#include <map>

#include "Hex.h"

#include "ObjectArray.h"
#include "MovingObject.h"
#include "StationaryObject.h"
#include "StaticObject.h"


class HexSpace : public sf::Drawable {
    // Window parameters
    sf::Vector2u window_size;
    int hex_size;

    // Drawable objects
    ObjectArray areas;
    ObjectArray players;

    sf::Texture areaTexture;

    // Helpful methods
    sf::Vector2f pixel(Hex hex) {
        float x = window_size.x / 2.f + hex_size * 3.f / 2.f * hex.q;
        float y = window_size.y / 2.f + hex_size * sqrt(3.f) * (hex.r + hex.q / 2.f);

        return sf::Vector2f(x, y);
    }

 public:
    HexSpace(sf::Vector2u window_size, int hex_size)
    : window_size(window_size), hex_size(hex_size) {
        areaTexture.loadFromFile("./Contents/sprites/territoria_bez_sveta.png");
    }

    void rebuild(std::map<Hex, int>& areas) {
        for (auto& area : areas) {
            auto areaObj = std::make_unique<StationaryObject>();
            areaObj->set_texture(areaTexture);

            areaObj->setPosition(pixel(area.first));

            this->areas.push(std::move(areaObj));
        }
    }

    void move(Move direction, float distance) {
        areas.move(direction, distance);
    }

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(areas);
    }
};

#endif //GRAPHICS_HEXSPACE_H
