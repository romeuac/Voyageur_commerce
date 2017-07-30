#ifndef CROPMX_H
#define CROPMX_H

#include <vector>
#include <string>
#include "ville.h"
#include "chemin.h"
#include "foncAux.h" // pour le compare et pous le cheminRandom
#include <iostream>
#include "algGen.h"

class croPMX : public algGen
{

public:

    /**
     * @brief Croisement des meilleurs chemins et substitution des pires
     * ils commencent trié (30% des meilleures)
     *
     * @param che Population de chemins
     * @param p Probabilite qui a ete utilise dans la mutation
     * @param mut Choix du algorithme de mutation
     */
    void CroisementPMX(vector<Chemin*> &che, float &p, const char *mut);

    /**
     * @brief On rearrange les villes qui n'ont pas ete echanger entre les parents
     *
     * @param fils nouveaux chemin qui a ete cree
     * @param pere pere qui a genere le fils
     * @param divisa partie du chemin que a ete echange
     */
    void consertaOutraPosicao(vector<string> &fils, const vector<string> &pere, int &divisa);

    /**
     * @brief Cette fonction retourne la bonne string pour le croisement
     *
     * @param filho Vecteur fils qui on veut mettre le string
     * @param pai Vecteur pere qui on utilise pour trouver le string pour le fils
     */
    string element(vector<string> &filho, vector<string> &pai, int pos);

    explicit croPMX ();
};

#endif // CROPMX_H
