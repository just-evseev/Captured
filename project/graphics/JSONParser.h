//
// Created by Святослав Кряжев on 13.12.2018.
//

#ifndef GRAPHICS_JSONPARSER_H
#define GRAPHICS_JSONPARSER_H

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <string>
#include <fstream>
#include <iostream>

#include "Textures.h"

#define JSONPARSER_PACK_SOURCE_DIR     "./textures/source/"

#define JSONPARSER_NAME                "Name"
#define JSONPARSER_SKINS               "Skins"
#define JSONPARSER_HEX_SIZE            "HexSize"


class JSONParser {
    std::string path;
    Textures& txtr_ptr;

    rapidjson::Document doc;

 public:
    JSONParser(std::string& json_path, Textures& tex)
        : path(json_path), txtr_ptr(tex) {};

    void set_path(std::string path) {
        this->path = path;
    }

    void parse() {
        std::fstream pack_file(path, std::ios::in);
        if (!pack_file.is_open())
            std::cerr << strerror(errno) << std::endl;

        using namespace rapidjson;

        IStreamWrapper isw(pack_file);
        doc.ParseStream(isw);

        pack_file.close();

        assert(doc.IsObject());

        assert(doc.HasMember(JSONPARSER_NAME));
        assert(doc.HasMember(JSONPARSER_SKINS));
        assert(doc.HasMember(JSONPARSER_HEX_SIZE));
    }

    void load() {
        std::string pack_dir =JSONPARSER_PACK_SOURCE_DIR ;
        pack_dir.append(doc[JSONPARSER_NAME].GetString());
        int n_skins = doc[JSONPARSER_SKINS].GetInt();
        txtr_ptr.hex_size = doc[JSONPARSER_HEX_SIZE].GetInt();

        // Loading textures
        for (int i = 0; i < n_skins; ++i) {
            std::string img_name = std::to_string(i + 1) + ".png";
            sf::Texture plr_txt;
            plr_txt.loadFromFile(pack_dir + "/players/" + img_name);

            sf::Texture ar_txt;
            ar_txt.loadFromFile(pack_dir + "/areas/" + img_name);

            //sf::Texture tl_txt;
            //tl_txt.loadFromFile(pack_dir + "/tails/" + img_name);

            txtr_ptr.playerTextures.emplace(i + 1, plr_txt);
            txtr_ptr.areaTextures.emplace(i + 1, ar_txt);
            //txtr_ptr.tailTextures.emplace(i + 1, tl_txt);
        }

        txtr_ptr.gridTexture.loadFromFile(pack_dir + "/unique/grid.png");
        txtr_ptr.backgroundTexture.loadFromFile(pack_dir + "/unique/background.png");
        txtr_ptr.cursorTexture.loadFromFile(pack_dir + "/unique/cursor.png");
    }
};

#endif //GRAPHICS_JSONPARSER_H
