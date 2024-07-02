#ifndef CATAN_HPP
#define CATAN_HPP

#include "board.hpp"
#include "player.hpp"
#include "corner.hpp"
#include <iostream>

class catan {
    board B;
    player& p1;
    player& p2;
    player& p3;
    int turn;

    public:
        void howIsFirst();
        board& getBoard();
        int turnOf();
        catan(player& P1, player& P2, player& P3, int seed=0);
        void end_turn();
        int getTurn();
        void printWinner();
        void split_resorces(int roll);
    private:
        std::vector<int> calculate_points();
};

#endif // CATAN_HPP
