//
// Created by Святослав Кряжев on 10.12.2018.
//

#ifndef GRAPHICS_SERVER2CLIENTPARSER_H
#define GRAPHICS_SERVER2CLIENTPARSER_H

#include <fstream>
#include <vector>
#include <map>

#include "Hex.h"
#include "server2client.pb.h"
#include "Move.h"

struct CellState {
    int id;
    int state;
};

typedef std::vector<Hex> PlayerArea;
typedef std::vector<Hex> PlayerTails;
typedef std::map<Hex, int> Areas;
typedef std::map<Hex, CellState> Tails;

struct Person {
    int area_square;
    Move direction;
    Hex point;
    int kills;
    int bonusEffect;
    PlayerArea playerArea;
    PlayerTails playerTails;
};

class Server2ClientParser {
 public:
    Server2ClientParser() {};

    void pack(std::map<int, Person> players, Areas areas, Tails tails) {
        GOOGLE_PROTOBUF_VERIFY_VERSION;

        using namespace server2client;

        Packet packet;

        // Serializing players
        for (auto& player : players) {
            Player* plr = packet.add_players();
            plr->set_id(player.first);
            plr->set_direction(server2client::Move(player.second.direction));
            plr->set_expansion(player.second.area_square);
            plr->set_kills(player.second.kills);

            plr->mutable_position()->set_q(player.second.point.q);
            plr->mutable_position()->set_r(player.second.point.r);
        }

        // Serializing areas
        for (auto& area : areas) {
            HexagonProperty* ar = packet.add_areas();
            ar->set_id(area.second);

            ar->mutable_hex()->set_q(area.first.q);
            ar->mutable_hex()->set_r(area.first.r);
        }

        // Serializing tails
        for (auto& tail : tails) {
            HexagonProperty* tl = packet.add_tails();
            tl->set_id(tail.second.id);

            tl->mutable_hex()->set_q(tail.first.q);
            tl->mutable_hex()->set_r(tail.first.r);
        }


        std::fstream output("./2client.pbp", std::ios::out | std::ios::trunc | std::ios::binary);
        if (!packet.SerializeToOstream(&output))
            std::cout << "BAD!";

        // Clear up
        google::protobuf::ShutdownProtobufLibrary();
    }
};

#endif //GRAPHICS_SERVER2CLIENTPARSER_H
