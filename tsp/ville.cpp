# include "ville.h"


Ville::Ville (std::string nom, float cordX, float cordY):
        ID (nom), x (cordX), y (cordY)    {}

float Ville::getX() const
{
    return x;
}

float Ville::getY() const
{
    return y;
}

std::string Ville::getID()
{
    return ID;
}

float Ville::prendreDistVoisin(Ville v)
{
    return sqrt ( pow((v.getX() - getX()),2) + pow((v.getY() - getY()),2) );	//retorna a distância entre a vila
}
