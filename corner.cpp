#include <vector>
#include "corner.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

corner::corner(const std::vector<int>& L, const std::vector<int>& N) {
    this->links = L;
    this->linked = N;
    this->contant = 'E';
    this->owner = 0;
}
std::vector<int> corner::getLinks(){return this->links;}
std::vector<int> corner::getLinked(){return this->linked;}
bool corner::hasContant(char c, int o){return (this->contant==c && this->owner==o);}
bool corner::belongsTo(int p){return p==this->owner;}
void corner::setContant(char c, int o){this->contant=c;this->owner=o;}
std::string corner::contantToString(){return std::string(1,this->contant)+","+std::to_string(this->owner);}
int corner::gives(){
    //std::cout << "giving corner with " << this->contant << this->owner << std::endl;
    if(this->contant=='V')return 1;
    if(this->contant=='C')return 2;
    return 0;
}
int corner::getOwner(){return this->owner;}
