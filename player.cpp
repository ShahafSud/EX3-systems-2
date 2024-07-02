#include "player.hpp"
#include "catan.hpp"
#include "board.hpp"
#include <random>
#include <iostream>
#include <stdexcept>

std::random_device player::dice;
std::mt19937 player::generator(player::dice());
std::uniform_int_distribution<> player::distribution(1, 6);
std::string player::getName(){return this->name;}
player::player(std::string Name, int p_num){
    if(p_num==0)throw std::runtime_error("Player number must !=0.");
    this->num = p_num;
    this->name = Name;
    this->resorces = std::vector<int> (5, 0);
    this->knights = 0;
    this->points = 0;
}
void player::placeSettelemnt(int corner_index, board& B, int turnIndex, bool initGame){
    if(turnIndex!=this->num)throw std::runtime_error("This is the turn of player " + std::to_string(turnIndex) + " not " +  std::to_string(this->num)+".");
    if((resorces[0]<1 || resorces[2]<1 || resorces[3]<1 || resorces[4]<1) && !initGame)throw std::runtime_error("Player"+std::to_string(this->num)+" can't build a Vilige due to lack of recorses.");
    B.build('V', this->num, corner_index, initGame);
    if(!initGame)resorces[0]--;
    if(!initGame)resorces[2]--;
    if(!initGame)resorces[3]--;
    if(!initGame)resorces[4]--;
    this->points++;
}
void player::placeCity(int corner_index, board& B, int turnIndex){
    if(turnIndex!=this->num)throw std::runtime_error("This is the turn of player " + std::to_string(turnIndex) + " not " +  std::to_string(this->num)+".");
    if(resorces[1]<3 || resorces[2]<2)throw std::runtime_error("Player"+std::to_string(this->num)+" can't build a City due to lack of recorses.");
    B.build('C', this->num, corner_index);
    resorces[1] -= 3;
    resorces[2] -= 2;
    points++;
}
void player::placeRoad(int corner1_index, int corner2_index, board& B, int turnIndex, bool initGame){
    if(turnIndex!=this->num)throw std::runtime_error("This is the turn of player " + std::to_string(turnIndex) + " not " +  std::to_string(this->num)+".");
    if((resorces[0]<1 || resorces[3]<1) && !initGame)throw std::runtime_error("Player"+std::to_string(this->num)+" can't build a Vilige due to lack of recorses.");
    B.build_road(this->num, corner1_index, corner2_index, initGame);
    if(!initGame)resorces[0]--;
    if(!initGame)resorces[3]--;
}
void player::buyDevelopmentCard(int turnIndex){
    if(turnIndex!=this->num)throw std::runtime_error("This is the turn of player " + std::to_string(turnIndex) + " not " +  std::to_string(this->num)+".");
    if(resorces[1]<1 || resorces[2]<1 || resorces[4]<1)throw std::runtime_error("Player"+std::to_string(this->num)+" can't buy a development card due to lack of recorses.");
    resorces[1]--;
    resorces[2]--;
    resorces[4]--;
    int randomness = distribution(generator);
    if(randomness<5)knights++;
    else points++;
    }
int player::rollDice(int turnIndex){
    if(this->num != turnIndex)throw std::runtime_error("This is the turn of player " + std::to_string(turnIndex) + " not " +  std::to_string(this->num)+".");
    return distribution(generator) + distribution(generator);
}
void player::trade(player& other, std::string giveRecorce, std::string takeRecorce, int give, int take, int turnIndex){
    int giveIndex=-1;
    int takeIndex=-1;
    if(this->num != turnIndex)throw std::runtime_error("This is the turn of player " + std::to_string(turnIndex) + " not " +  std::to_string(this->num)+".");
    if(giveRecorce=="Bricks")giveIndex=0;
    if(takeRecorce=="Bricks")takeIndex=0;
    if(giveRecorce=="Iron")giveIndex=1;
    if(takeRecorce=="Iron")takeIndex=1;
    if(giveRecorce=="Grain")giveIndex=2;
    if(takeRecorce=="Grain")takeIndex=2;
    if(giveRecorce=="Wood")giveIndex=3;
    if(takeRecorce=="Wood")takeIndex=3;
    if(giveRecorce=="Sheep")giveIndex=4;
    if(takeRecorce=="Sheep")takeIndex=4;
    if(giveIndex==-1 || takeIndex==-1)throw std::runtime_error("Invalid input error: ("+giveRecorce+","+takeRecorce+")");
    if(this->resorces[giveIndex]<give)throw std::runtime_error("Insufitint "+giveRecorce+".");
    if(other.resorces[takeIndex]<take)throw std::runtime_error("Insufitint "+takeRecorce+".");
    this->resorces[giveIndex] -= give;
    other.resorces[giveIndex] += give;
    this->resorces[takeIndex] += take;
    other.resorces[takeIndex] -= take;
}
void player::printPoints(){
    std::cout<< this->name << " have " << std::to_string(this->points) << "-points and " << std::to_string(this->knights) << " knights." << std::endl;
}
void player::printName(){
    std::cout<< this->name << std::endl;;
}
int player::getPoints(){return this->points;}
int player::getKnights(){return this->knights;}
void player::gain(std::string name, int n){
    if(n<1)throw std::runtime_error("Invalid input. Recived n<=0. (" + std::to_string(n)+")");
    bool gained = false;
    if(name=="Bricks"){gained=true;this->resorces[0] += n;}
    if(name=="Iron"){gained=true;this->resorces[1] += n;}
    if(name=="Grain"){gained=true;this->resorces[2] += n;}
    if(name=="Wood"){gained=true;this->resorces[3] += n;}
    if(name=="Sheep"){gained=true;this->resorces[4] += n;}
    if(!gained)throw std::runtime_error("Invalid input. No such resorce as " + name);
}