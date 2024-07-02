#include <vector>
#include <string>

#ifndef CORNER_HPP
#define CORNER_HPP

class corner{
    std::vector<int> links;
    std::vector<int> linked;
    char contant;
    int owner;
    public:
        corner(const std::vector<int>& L, const std::vector<int>& N);
        std::vector<int> getLinks();
        std::vector<int> getLinked();
        bool hasContant(char c, int o);
        void setContant(char c, int o);
        std::string contantToString();
        bool belongsTo(int p);
        int getOwner();
        int gives();
};
#endif // CORNER_HPP