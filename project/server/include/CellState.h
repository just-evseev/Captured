//
// Created by Ilya on 10/12/2018.
//

#ifndef SERVER_CELLSTATE_H
#define SERVER_CELLSTATE_H


class CellState {
public:
    CellState(int id, int state)
            : id(id), state(state) {};

    int id;
    int state;

    void updateCellState(int id, int state) {
        this->id = id;
        this->state = state;
    }
};


#endif //SERVER_CELLSTATE_H
