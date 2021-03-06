//
// Created by Святослав Кряжев on 05.12.2018.
//

#ifndef GRAPHICS_HEX_H
#define GRAPHICS_HEX_H

class Hex {
    struct decart {
        decart(float x, float y)
                : x(x), y(y) {};

        float x;
        float y;
    };

    Hex::decart level() const {
        float x = q;
        float y = r + q / 2.f;

        return Hex::decart(x, y);
    }
public:
    Hex(int q, int r)
            : q(q), r(r) {};

    int q;
    int r;

    void updateCoord(int q, int r) {
        this->q = q;
        this->r = r;
    }
    bool operator<(const Hex& right) const {
        Hex::decart l = level();
        Hex::decart r = right.level();

        if (l.y < r.y)
            return true;

        if (l.y > r.y)
            return false;

        return l.x < r.x;

    }
};

/*
 * Use it like std::map<Hex, int>;
 */

#endif //GRAPHICS_HEX_H
