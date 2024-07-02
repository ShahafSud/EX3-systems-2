#include "catan.hpp"
#include "player.hpp"
#include "corner.hpp"
#include <iostream>
#include <stdexcept>

// Assuming player has a method printName()
void catan::howIsFirst() {p1.printName();}
int catan::getTurn(){return this->turn;}
board& catan::getBoard() {return B;}
catan::catan(player& P1, player& P2, player& P3, int seed): B(board(seed)), p1(P1), p2(P2), p3(P3), turn(1){}
void catan::end_turn(){this->turn++;if(this->turn==4)this->turn=1;}
void catan::printWinner(){
    std::vector<int> points = calculate_points();
    if(points[0]>points[1] && points[0]>points[2])std::cout<<p1.getName()<<" (player 1) wins." << std::endl;
    if(points[1]>points[0] && points[1]>points[2])std::cout<<p2.getName()<<" (player 2) wins." << std::endl;
    if(points[2]>points[1] && points[2]>points[0])std::cout<<p3.getName()<<" (player 3) wins." << std::endl;
    if(points[0]==points[1] && points[0]>points[2])std::cout<<p1.getName()<< "and" << p2.getName() <<" (players 1,2) wins in a drow." << std::endl;
    if(points[0]==points[2] && points[0]>points[1])std::cout<<p1.getName()<< "and" << p3.getName() <<" (players 1,3) wins in a drow." << std::endl;
    if(points[2]==points[1] && points[1]>points[0])std::cout<<p2.getName()<< "and" << p3.getName() <<" (players 2,3) wins in a drow." << std::endl;
    if(points[0]==points[1] && points[1]==points[2])std::cout<<" all 3 players are in a drow." << std::endl;
}
std::vector<int> catan::calculate_points(){
    int k1 = this->p1.getKnights();
    int k2 = this->p2.getKnights();
    int k3 = this->p3.getKnights();
    int s1 = this->p1.getPoints();
    int s2 = this->p2.getPoints();
    int s3 = this->p3.getPoints();
    if(k1>=3 && k1>k2 && k1>k3)s1+=2;
    if(k2>=3 && k2>k1 && k2>k3)s2+=2;
    if(k3>=3 && k3>k2 && k3>k1)s3+=2;
    if(k1>=3 && k1==k2 && k1>k3){s1++;s2++;};
    if(k1>=3 && k1==k3 && k1>k2){s1++;s3++;};
    if(k2>=3 && k2==k3 && k2>k1){s2++;s3++;};
    std::vector<int> ans = {s1,s2,s3};
    return ans;
}
void catan::split_resorces(int roll){
    if(roll>12||roll<1)throw std::runtime_error("Invalid roll input. rolled: " + std::to_string(roll)+".");
    std::string resorce;
    for(int square=0;square<20;square++){
        resorce = this->B.gives(square, roll);
        if(resorce=="")continue;
        std::vector<corner>& C = this->B.getCorners();
        int amount;
        for(int i=0;i<54;i++){
            amount = C[i].gives();
            if(amount==0)continue;
            int owner = C[i].getOwner();
            if(owner==1)this->p1.gain(resorce, amount);
            if(owner==2)this->p2.gain(resorce, amount);
            if(owner==3)this->p3.gain(resorce, amount);
        }     
    }
}

