#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <random>
#include <vector>
#include <iostream>
#include "board.hpp"

class player{
    int num;
    std::string name;
    std::vector<int> resorces;// bricks, stone, weat, wood, wool
    int knights;
    int points;
    static std::random_device dice;
    static std::mt19937 generator;
    static std::uniform_int_distribution<> distribution;
    public:
        std::string getName();
        player(std::string Name, int p_num);
        void placeSettelemnt(int corner_index, board &B, int turnIndex, bool initGame=false);
        void placeCity(int corner_index, board& B, int turnIndex);
        void placeRoad(int corner1_index, int corner2_index, board& B, int turnIndex, bool initGame=false);
        int rollDice(int turnIndex);
        void addPoints(int n);
        void trade(player& other, std::string giveRecorce, std::string takeRecorce, int give, int take, int turnIndex);
        void buyDevelopmentCard(int turnIndex);
        void printPoints();
        void printName();
        int getKnights();
        int getPoints();
        void gain(std::string name, int n);
};

#endif // PLAYER_HPP