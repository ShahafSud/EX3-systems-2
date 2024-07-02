/*
the board is built:

     1   2   3
   4   5   6   7
 8   9   10  11  12
   13  14  15  16
     17  19  20

road is corner:corner

*/

#include <vector>
#include <string>
#include "corner.hpp"

#ifndef BOARD_HPP
#define BOARD_HPP

class board{
    std::vector<std::string> types;
    std::vector<int> numbers;
    std::vector<corner> corners;
    std::vector<std::vector<int>> ways;
    public:
        board(int initiator);
        void build(char obj, int p, int corner_index, bool gameinit=false);
        void build_road(int p, int corner1_index, int corner2_index, bool initGame);
        std::string gives(int index, int roll);
        std::vector<corner>& getCorners();
};
#endif // BOARD_HPP