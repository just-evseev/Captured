//
// Created by Святослав Кряжев on 11.12.2018.
//

#ifndef GRAPHICS_TEXTUREOWNER_H
#define GRAPHICS_TEXTUREOWNER_H

#include <SFML/Graphics.hpp>
#include <string>

#include "JSONParser.h"

enum TextureType {
    PLAYER,
    AREA,
    TAIL,
    GRID,
    BACKGROUND,
    CURSOR
};

enum TailType {
    STRAIGHT_1,
    STRAIGHT_2,
    STRAIGHT_3,
    OBTUSE_1,
    OBTUSE_2,
    OBTUSE_3,
    OBTUSE_4,
    OBTUSE_5,
    OBTUSE_6,
    SHARP_1,
    SHARP_2,
    SHARP_3,
    SHARP_4,
    SHARP_5,
    SHARP_6
};


class TextureOwner {
 private:
    std::string pack_path;

    Textures textures;

 public:
    TextureOwner(const char* texture_pack_info_file)
                    : pack_path(texture_pack_info_file) {};

    void load() {
        JSONParser parser(pack_path, textures);
        parser.parse();
        parser.load();
    };

    sf::Texture& get(TextureType type) {
        switch (type) {
            case PLAYER:
                return textures.playerTextures.at(1);

            case AREA:
                return textures.areaTextures.at(1);

            case TAIL:
                return textures.tailTextures.at(1);

            case GRID:
                return textures.gridTexture;

            case BACKGROUND:
                return textures.backgroundTexture;

            case CURSOR:
                return textures.cursorTexture;
        }
    };
};

#endif //GRAPHICS_TEXTUREOWNER_H
