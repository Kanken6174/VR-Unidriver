#include <iostream>

class Transformer{
public:
    virtual std::string transformeDonnees(float donnees, std::string type, std::string format) = 0;
    virtual std::string toTransformIn(std::string format) = 0;
};