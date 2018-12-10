//
// Created by Святослав Кряжев on 05.12.2018.
//

#ifndef GRAPHICS_HEX_H
#define GRAPHICS_HEX_H

class Hex {
public:
    Hex(int q, int r)
            : q(q), r(r) {};

    int q;
    int r;

    void updateCoord(int q, int r) {
        this->q = q;
        this->r = r;
    }
};

/*
 * Use it like std::map<Hex, int>;
 */

#endif //GRAPHICS_HEX_H
