//
// Created by Святослав Кряжев on 10.12.2018.
//

#ifndef GRAPHICS_PLAYERSIMITATION_H
#define GRAPHICS_PLAYERSIMITATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <forward_list>
#include <utility>

#include "MovingObject.h"
#include "Hex.h"


class PlayersImitation : public sf::Drawable {
    std::vector<MovingObject> players;
    std::vector<std::list<Move>::const_iterator> I;
    std::vector<std::forward_list<Move>> behaviors;

    sf::Texture texture;


 public:
    PlayersImitation() {
        texture.loadFromFile("./Contents/sprites/Igrok.png");

        std::forward_list<Move> list1 = {UP, RIGHT_UP, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT_UP};
        std::forward_list<Move> list2 = {UP, RIGHT_UP, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT_UP,
                                         LEFT_UP, LEFT_DOWN, DOWN, RIGHT_DOWN, RIGHT_UP, UP};
        std::forward_list<Move> list3 = {RIGHT_DOWN, LEFT_DOWN, RIGHT_DOWN, LEFT_DOWN, RIGHT_DOWN, LEFT_DOWN,
                                         LEFT_UP, LEFT_UP, LEFT_UP, RIGHT_UP, RIGHT_UP, RIGHT_UP};

        behaviors.push_back(list1);
        behaviors.push_back(list2);
        behaviors.push_back(list3);
    }

    void add_player(sf::Vector2f pos, int behavior) {
        MovingObject player;
        player.set_texture(texture);

        player.setPosition(pos);

        players.push_back(player);

        std::list<Move>::const_iterator I1 = behaviors.at(behavior).front();

        I.push_back(I1);
    }

    void move(Move direction, float distance) {
        std::vector<MovingObject>::const_iterator i1;
        std::vector<std::list<Move>::const_iterator>::const_iterator i2;
        for( i1 = players.begin(), i2 = I.begin();
             i1 < players.end() && i2 < I.end();
             ++i1, ++i2 )
        {
            i1.set
        }
    }
};

#endif //GRAPHICS_PLAYERSIMITATION_H
