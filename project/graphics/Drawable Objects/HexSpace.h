//
// Created by Святослав Кряжев on 09.12.2018.
//

#ifndef GRAPHICS_HEXSPACE_H
#define GRAPHICS_HEXSPACE_H

#include <map>

#include "Hex.h"
#include "DataPacket.h"

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
    }

    void rebuild(std::shared_ptr<DataPacket> data) {
        for (auto& area : data->areas) {
            auto areaObj = std::make_unique<StationaryObject>();
            areaObj->set_up(areaTexture);

            areaObj->setPosition(pixel(area.first));

            this->areas.push(std::move(areaObj));
        }

        for (auto& tail : data->tails) {
            auto tailObj = std::make_unique<StationaryObject>();
            tailObj->set_up(areaTexture);
            tailObj->set_alpha();

            tailObj->setPosition(pixel(tail.first));

            this->areas.push(std::move(tailObj));
        }

        for (auto& player : data->players) {
            playerObj = std::make_unique<MovingObject>();
            playerObj->set_up(playerTexture);

            playerObj->setPosition(pixel(player.first));

            playerObj->set_move(UP);
            playerObj->set_color();
            this->players.push(std::move(playerObj));
        }
    }

    void drop() {
        areas.drop();
        players.drop();
        tails.drop();
    };

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

        auto guide = [](Move prev, Move cur) -> TailType {
            if (prev == UP)
                switch ( cur) {
                    case UP:
                        return STRAIGHT_1;

                    case RIGHT_UP:
                        return OBTUSE_2;

                    case RIGHT_DOWN:
                        return SHARP_3;

                    case LEFT_DOWN:
                        return SHARP_4;

                    case LEFT_UP:
                        return OBTUSE_4;
                }

            if (prev == RIGHT_UP)
                switch (cur) {
                    case UP:
                        return OBTUSE_5;

                    case RIGHT_UP:
                        return STRAIGHT_2;

                    case RIGHT_DOWN:
                        return OBTUSE_3;

                    case DOWN:
                        return SHARP_4;

                    case LEFT_UP:
                        return SHARP_5;
                }

            if (prev == RIGHT_DOWN)
                switch (cur) {
                    case UP:
                        return SHARP_6;

                    case RIGHT_UP:
                        return OBTUSE_6;

                    case RIGHT_DOWN:
                        return STRAIGHT_3;

                    case DOWN:
                        return OBTUSE_4;

                    case LEFT_DOWN:
                        return SHARP_5;
                }

            if (prev == DOWN)
                switch (cur) {
                    case RIGHT_UP:
                        return SHARP_1;

                    case RIGHT_DOWN:
                        return OBTUSE_1;

                    case DOWN:
                        return STRAIGHT_1;

                    case LEFT_DOWN:
                        return OBTUSE_5;

                    case LEFT_UP:
                        return SHARP_6;
                }

            if (prev == LEFT_DOWN)
                switch (cur) {
                    case UP:
                        return SHARP_1;

                    case RIGHT_DOWN:
                        return SHARP_2;

                    case DOWN:
                        return OBTUSE_2;

                    case LEFT_DOWN:
                        return STRAIGHT_2;

                    case LEFT_UP:
                        return OBTUSE_6;
                }

            if (prev == LEFT_UP)
                switch (cur) {
                    case UP:
                        return OBTUSE_1;

                    case RIGHT_UP:
                        return SHARP_2;

                    case DOWN:
                        return SHARP_3;

                    case LEFT_DOWN:
                        return OBTUSE_3;

                    case LEFT_UP:
                        return STRAIGHT_3;
                }
        };

        auto tail = std::make_unique<StationaryObject>();
        tail->set_up(tailTexture, 15);
        tail->choose_texture(guide(prevmove, newmove));

        tail->setPosition(window_size.x / 2.f, window_size.y / 2.f);


        //tail->set_alpha();
        tails.push(std::move(tail));
        prevmove = newmove;
    }

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(areas);
        target.draw(tails);
        //target.draw(*playerObj);
    }
};

#endif //GRAPHICS_HEXSPACE_H
