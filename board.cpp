/*
the board is built:

     0   1   2
   3   4   5    6
 7   8   9   10  11
   12  13  14  15
     16  17  18

corners are: (minimal square, corner number)

        1
    2       3

    4       5
        6

road is corner:corner

*/
#include "board.hpp"
#include "corner.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

board::board(int initiator){ // for semi-random init
    types.resize(20);
    numbers.resize(20);
    for(int i=initiator;i<19;i++){
      int x=(i+initiator)%19;
      if(x%5==0)types[i]="Wood";
      else if(x%5==1)types[i]="Bricks";
      else if(x%5==2)types[i]="Sheep";
      else if(x%5==3)types[i]="Iron";
      else if(x%5==4)types[i]="Grain";
      if(x==0)numbers[x]=5;
      if(x==1)numbers[x]=8;
      if(x==2)numbers[x]=4;
      if(x==3)numbers[x]=6;
      if(x==4)numbers[x]=3;
      if(x==5)numbers[x]=11;
      if(x==6)numbers[x]=10;
      if(x==7)numbers[x]=9;
      if(x==8)numbers[x]=11;
      if(x==9)numbers[x]=0;
      if(x==10)numbers[x]=3;
      if(x==11)numbers[x]=8;
      if(x==12)numbers[x]=2;
      if(x==13)numbers[x]=6;
      if(x==14)numbers[x]=4;
      if(x==15)numbers[x]=5;
      if(x==16)numbers[x]=10;
      if(x==17)numbers[x]=12;
      if(x==18)numbers[x]=9;
    }
    types[9]="Desert";
    corners.resize(54, corner(std::vector<int>(), std::vector<int>()));
    corners[0] = corner({0, -1, -1}, {3, 4, -1});
    corners[1] = corner({1 , -1, -1}, {4, 5, -1});
    corners[2] = corner({2 , -1, -1}, {5, 6, -1});

    corners[3] = corner({0, -1, -1}, {0, 7, -1});
    corners[4] = corner({0, 1, -1}, {0, 1, 8});
    corners[5] = corner({1, 2, -1}, {1, 2, 9});
    corners[6] = corner({2, -1, -1}, {2, 10, -1});

    corners[7] = corner({0, 3, -1}, {3, 11, 12});
    corners[8] = corner({0, 1, 4}, {4, 12, 13});
    corners[9] = corner({1, 2, 5}, {5, 13, 14});
    corners[10] = corner({2, 6, -1}, {6, 14, 15});

    corners[11] = corner({3, -1, -1}, {7, 16, -1});
    corners[12] = corner({0, 3, 4}, {7, 8, 17});
    corners[13] = corner({1, 4, 5}, {8, 9, 18});
    corners[14] = corner({2, 5, 6}, {9, 10, 19});
    corners[15] = corner({6, -1, -1}, {10, 20, -1});

    corners[16] = corner({3, 7, -1}, {11, 21, 22});
    corners[17] = corner({3, 4, 8}, {12, 22, 23});
    corners[18] = corner({4, 5, 9}, {13, 23, 24});
    corners[19] = corner({5, 6, 10}, {14, 24, 25});
    corners[20] = corner({6, 11, -1}, {15, 25, 26});

    corners[21] = corner({7, -1, -1}, {16, 27, -1});
    corners[22] = corner({3, 7, 8}, {16, 17, 28});
    corners[23] = corner({4, 8, 9}, {17, 18, 29});
    corners[24] = corner({5, 9, 10}, {18, 19, 30});
    corners[25] = corner({6, 10, 11}, {19, 20, 31});
    corners[26] = corner({11, -1, -1}, {20, 32, -1});

    corners[27] = corner({7, -1, -1}, {21, 33, -1});
    corners[28] = corner({7, 8, 12}, {22, 33, 34});
    corners[29] = corner({8, 9, 13}, {23, 34, 35});
    corners[30] = corner({9, 10, 14}, {24, 35, 36});
    corners[31] = corner({10, 11, 15}, {25, 36, 37});
    corners[32] = corner({11, -1, -1}, {26, 37, -1});

    corners[33] = corner({7, 12, -1}, {27, 28, 38});
    corners[34] = corner({8, 12, 13}, {28, 29, 39});
    corners[35] = corner({9, 13, 14}, {29, 30, 40});
    corners[36] = corner({10, 14, 15}, {30, 31, 41});
    corners[37] = corner({11, 15, -1}, {31, 32, -42});

    corners[38] = corner({12, -1, -1}, {33, 43, -1});
    corners[39] = corner({12, 13, 16}, {34, 43, 44});
    corners[40] = corner({13, 14, 17}, {35, 44, 45});
    corners[41] = corner({14, 15, 18}, {36, 45, 46});
    corners[42] = corner({15, -1, -1}, {37, 46, -1});

    corners[43] = corner({12, 16, -1}, {38, 39, 47});
    corners[44] = corner({13, 16, 17}, {39, 40, 48});
    corners[45] = corner({14, 17, 18}, {40, 41, 49});
    corners[46] = corner({15, 18, -1}, {41, 42, 50});

    corners[47] = corner({16, -1, -1}, {43, 51, -1});
    corners[48] = corner({16, 17, -1}, {44, 51, 52});
    corners[49] = corner({17, 18, -1}, {45, 52, 53});
    corners[50] = corner({18, -1, -1}, {46, 50, -1});

    corners[51] = corner({16, -1, -1}, {47, 48, -1});
    corners[52] = corner({17, -1, -1}, {48, 49, -1});
    corners[53] = corner({18, -1, -1}, {49, 50, -1});
    this->ways = std::vector<std::vector<int>>(54, std::vector<int>(54, 0));
}
void board::build(char obj, int p, int corner_index, bool gameinit){//C=City, V=Vilige
    std::vector<int> links = this->corners[corner_index].getLinks();
    bool linked = false;
    for(int i=0;i<3;i++){if(links[i]==p)linked=true;}
    if(!gameinit && !linked)throw std::runtime_error("Can't build in corner "+std::to_string(corner_index)+" since it is not linked to any of player"+std::to_string(p)+"'s roads.");
    if(!corners[corner_index].hasContant('V',p) && obj=='C')throw std::runtime_error("Can't build a city in corner "+std::to_string(corner_index)+" since player "+std::to_string(p)+" have no Vilige in it.");
    if(!corners[corner_index].hasContant('E',0) && obj=='V')throw std::runtime_error("Can't build a settalment in corner "+std::to_string(corner_index)+" since it isn't empty. ("+corners[corner_index].contantToString()+")");
    corners[corner_index].setContant(obj,p);
}
void board::build_road(int p, int corner1_index, int corner2_index, bool initGame){
    if(ways[corner1_index][corner2_index]!=0)throw std::runtime_error("Player "+std::to_string(ways[corner1_index][corner2_index])+" allrady placed a road in the location : ("+std::to_string(corner1_index)+","+std::to_string(corner1_index)+").");
    if(!corners[corner1_index].belongsTo(p) && !corners[corner2_index].belongsTo(p) && !initGame)throw std::runtime_error("Player "+std::to_string(p)+" have no controle over corners "+std::to_string(corner1_index)+" or "+std::to_string(corner2_index)+".");
    ways[corner1_index][corner2_index]=p;
}
std::string board::gives(int index, int roll){
    if(numbers[index]==roll && this->types[index]!="Desert")return this->types[index];
    else return "";
}
std::vector<corner>& board::getCorners(){return corners;}