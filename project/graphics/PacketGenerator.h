//
// Created by Святослав Кряжев on 10.12.2018.
//

#ifndef GRAPHICS_PACKETGENERATOR_H
#define GRAPHICS_PACKETGENERATOR_H

#include <iostream>
#include <fstream>

#include "Move.h"
#include "client2server.pb.h"

class PacketGenerator {
 public:
    PacketGenerator() {};

    void pack(Move direction) {
        GOOGLE_PROTOBUF_VERIFY_VERSION;

        client2server::Packet packet;

        packet.set_direction(client2server::Move(direction));

        std::fstream output("./2server.pbp", std::ios::out | std::ios::trunc | std::ios::binary);
        if (!packet.SerializeToOstream(&output))
            std::cout << "BAD!";

        // Clear up
        google::protobuf::ShutdownProtobufLibrary();
    }

    void unpack() {
        GOOGLE_PROTOBUF_VERIFY_VERSION;

        client2server::Packet packet;

        std::fstream input("./2server.pbp", std::ios::in | std::ios::binary);
        if (!packet.ParseFromIstream(&input))
            std::cout << "BAD!";

        Move direction = Move(packet.direction());

        std::cout << direction << std::endl;

        // Clear up
        google::protobuf::ShutdownProtobufLibrary();
    }
};

#endif //GRAPHICS_PACKETGENERATOR_H
