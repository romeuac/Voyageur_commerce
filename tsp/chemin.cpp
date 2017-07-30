#include "chemin.h"


Chemin::Chemin (std::vector<std::string> vnom, float a, int b):
                v(vnom), ccout(a), compteur(b) {}

float Chemin::getCout() const {
    return ccout;
}

std::vector<std::string> Chemin::getStr() const {
    return v;
}

int Chemin::getComp() const {
    return compteur;
}

void Chemin::setCout(int uneValeur){
    ccout = uneValeur;
}

void Chemin::setComp(int uneValeur){
    compteur = uneValeur;
}

void Chemin::AugCompt (){
    compteur++;
}
