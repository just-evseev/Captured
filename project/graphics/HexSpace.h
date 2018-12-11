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


class HexSpace : public sf::Drawable {
    // Window parameters
    sf::Vector2u window_size;
    int hex_size;

    // Drawable objects
    MovableObjectArray areas;
    MovableObjectArray players;
    MovableObjectArray tails;

    sf::Texture areaTexture;
    sf::Texture playerTexture;

    int i = 0;
    Move ii[24] = {RIGHT_DOWN, LEFT_DOWN, RIGHT_DOWN, LEFT_DOWN, RIGHT_DOWN, LEFT_DOWN,
            LEFT_UP, LEFT_UP, LEFT_UP, RIGHT_UP, RIGHT_UP, RIGHT_UP,
            UP, RIGHT_UP, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT_UP,
                   LEFT_UP, LEFT_DOWN, DOWN, RIGHT_DOWN, RIGHT_UP, UP};

    std::unique_ptr<MovingObject> playerObj;

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
        playerTexture.loadFromFile("./Contents/sprites/Igrok.png");
    }

    void rebuild(std::map<Hex, int>& areas, std::map<Hex, int>& players) {
        for (auto& area : areas) {
            auto areaObj = std::make_unique<StationaryObject>();
            areaObj->set_texture(areaTexture);

            areaObj->setPosition(pixel(area.first));

            this->areas.push(std::move(areaObj));
        }

        for (auto& player : players) {
            playerObj = std::make_unique<MovingObject>();
            playerObj->set_texture(playerTexture);

            playerObj->setPosition(pixel(player.first));

            playerObj->set_move(UP);
            playerObj->set_color();
            //this->players.push(std::move(playerObj));
        }
    }

    void set_movement(Move direction, float distance) {
        areas.set_movement(direction, distance);
        tails.set_movement(direction, distance);
        playerObj->set_movement(direction, distance);
    }

    void move() {
        areas.move();
        tails.move();
        playerObj->move();
    }

    void freak() {
        if (i == 24)
            i = 0;
        playerObj->set_move(ii[i]);
        i++;

        auto tail = std::make_unique<StationaryObject>();
        tail->set_texture(areaTexture);

        tail->setPosition(window_size.x / 2.f, window_size.y / 2.f);

        tail->set_alpha();
        tails.push(std::move(tail));
    }

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(areas);
        target.draw(tails);
        target.draw(*playerObj);
    }
};

#endif //GRAPHICS_HEXSPACE_H
