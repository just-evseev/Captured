//
// Created by Святослав Кряжев on 09.12.2018.
//

#ifndef GRAPHICS_HEXSPACE_H
#define GRAPHICS_HEXSPACE_H

#include <map>

#include "Hex.h"

#include "TextureOwner.h"
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
    sf::Texture tailTexture;

    sf::Texture areaT[7];

    Move prevmove;


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
        tailTexture.loadFromFile("./textures/source/Neon/tails/1.png");

        areaT[0].loadFromFile("./Contents/пути - непрозрачные/120x120/obtuse_4.png");
        areaT[1].loadFromFile("./Contents/пути - непрозрачные/120x120/straight_1.png");
        areaT[2].loadFromFile("./Contents/пути - непрозрачные/120x120/straight_1.png");
        areaT[3].loadFromFile("./Contents/пути - непрозрачные/120x120/obtuse_3.png");
        areaT[4].loadFromFile("./Contents/пути - непрозрачные/120x120/sharp_2.png");
        areaT[5].loadFromFile("./Contents/пути - непрозрачные/120x120/sharp_6.png");
        areaT[6].loadFromFile("./Contents/пути - непрозрачные/120x120/obtuse_4.png");
    }

    void rebuild(std::map<Hex, int>& areas, std::map<Hex, int>& players) {
        int i = 0;
        for (auto& area : areas) {
            auto areaObj = std::make_unique<StationaryObject>();
            areaObj->set_up(areaT[i]);

            areaObj->setPosition(pixel(area.first));

            this->areas.push(std::move(areaObj));
            i++;
        }

        for (auto& player : players) {
            playerObj = std::make_unique<MovingObject>();
            playerObj->set_up(playerTexture);

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

    void freak(Move newmove) {
        if (i == 24)
            i = 0;
        playerObj->set_move(ii[i]);
        i++;

        auto guide = [](Move prevmove, Move newmove) -> TailType {
            if (abs(prevmove - newmove == 0)) {
                if (prevmove == UP || prevmove == DOWN)
                    return TailType::STRAIGHT_1;

                if (prevmove == LEFT_UP || prevmove == RIGHT_DOWN)
                    return TailType::STRAIGHT_2;

                if (prevmove == RIGHT_UP || prevmove == LEFT_DOWN)
                    return TailType::STRAIGHT_3;
            }

            if ((prevmove == UP && newmove == RIGHT_UP) || (newmove == DOWN && prevmove == LEFT_DOWN))
                return TailType::OBTUSE_1;

            if ((prevmove == RIGHT_UP && newmove == RIGHT_DOWN) || (newmove == RIGHT_UP && prevmove == RIGHT_DOWN))
                return TailType::SHARP_2;

            if ((prevmove == RIGHT_DOWN && newmove == DOWN) || (newmove == RIGHT_DOWN && prevmove == DOWN))
                return TailType::SHARP_3;

            if ((prevmove == DOWN && newmove == LEFT_DOWN) || (newmove == DOWN && prevmove == LEFT_DOWN))
                return TailType::SHARP_4;

            if ((prevmove == LEFT_DOWN && newmove == LEFT_UP) || (newmove == LEFT_DOWN && prevmove == LEFT_UP))
                return TailType::SHARP_5;

            if ((prevmove == LEFT_UP && newmove == UP) || (newmove == LEFT_UP && prevmove == UP))
                return TailType::SHARP_6;

            if ((prevmove == UP && newmove == RIGHT_DOWN) || (newmove == UP && prevmove == RIGHT_DOWN))
                return TailType::OBTUSE_1;

            if ((prevmove == RIGHT_UP && newmove == DOWN) || (newmove == RIGHT_UP && prevmove == DOWN))
                return TailType::OBTUSE_2;

            if ((prevmove == RIGHT_DOWN && newmove == LEFT_DOWN) || (newmove == RIGHT_DOWN && prevmove == LEFT_DOWN))
                return TailType::OBTUSE_3;

            if ((prevmove == DOWN && newmove == LEFT_UP) || (newmove == DOWN && prevmove == LEFT_UP))
                return TailType::OBTUSE_4;

            if ((prevmove == LEFT_DOWN && newmove == UP) || (newmove == LEFT_DOWN && prevmove == UP))
                return TailType::OBTUSE_5;

            if ((prevmove == LEFT_UP && newmove == RIGHT_UP) || (newmove == LEFT_UP && prevmove == RIGHT_UP))
                return TailType::OBTUSE_6;
        };

        auto tail = std::make_unique<StationaryObject>();
        tail->set_up(tailTexture, 15);
        tail->choose_texture(guide(prevmove, newmove));

        tail->setPosition(window_size.x / 2.f, window_size.y / 2.f);

        std::cout << newmove << std::endl;

        // tail->set_alpha();
        tails.push(std::move(tail));
        prevmove = newmove;
    }

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(areas);
        target.draw(tails);
        target.draw(*playerObj);
    }
};

#endif //GRAPHICS_HEXSPACE_H
