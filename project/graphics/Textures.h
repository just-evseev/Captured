//
// Created by Святослав Кряжев on 13.12.2018.
//

#ifndef GRAPHICS_TEXTURES_H
#define GRAPHICS_TEXTURES_H

#include <SFML/Graphics.hpp>
#include <map>

struct Textures {
    int textures_count;

    std::map<int, sf::Texture> playerTextures;
    std::map<int, sf::Texture> areaTextures;
    std::map<int, sf::Texture> tailTextures;

    sf::Texture gridTexture;
    sf::Texture backgroundTexture;
    sf::Texture cursorTexture;

    int hex_size;
};

#endif //GRAPHICS_TEXTURES_H
