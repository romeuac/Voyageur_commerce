#ifndef FONCAUX_H
#define FONCAUX_H

#include <cstdlib> // pour le rand()
#include <algorithm>
#include <iostream>
#include <vector>
#include "chemin.h"
#include "ville.h"
#include <cctype>
#include <fstream> // pour le fichier
#include <QtGui>


using namespace std;

//Groupe de fonctions auxiliaires qu'on utilise dans les autres fichier, mais on les separe dans ce espace pour
//avoir une meilleure organization de nos travail.

/**
 * @brief Il montre le matrice des couts
 *
 * @param mat Pointeur vers un pointeur d'un float
 */
void afficheMat(float **mat);

/**
 * @brief Fonction de debug
 *
 * Il montre tous les strings du vecteur. Cette fonction a ete utilise pour montrer
 * chaque ville d'un chemin
 *
 * @param str C'est un type du C++ de vecteur de strings
 */
void afficheStr(vector<string> &str);

/**
 * @brief Debug function
 *
 * Affiche tous les chemins dans la population
 *
 * @param che Vecteur des chemins qui ont ete utilise dans l'algorithme.
 */
void afficheChe(vector<Chemin*> &che);

//Auxiliaire pour cheminRandom() random generator function:
/**
 * @brief Fonction pour la generation aleatoire de chiffres
 *
 *
 */
ptrdiff_t myrandom (ptrdiff_t i);

//Ce mthode retourne une vecteur de string aleatoire, cet une possibilit de solution initiale
/**
 * @brief
 *
 * @param vectcor
 * @return vector<string>
 */
vector<string> cheminRandom(vector<string> &vectcor);

//Fonction auxiliaire
/**
 * @brief
 *
 * @param a
 * @param b
 * @return int
 */
int compare (const void * a, const void * b);


//Il calcule le temps - Il reoit le variable qu'on prends au dbut du code, dans le main.
/**
 * @brief
 *
 * @param tstart
 * @return int
 */
int Temps (time_t tstart);


/**
 * @brief
 *
 * @param fichier
 * @return std::vector<Ville *>
 */
std::vector < Ville * >lireFichier (char *fichier);
/**
 * @brief
 *
 * @param vet
 * @param a
 * @return int
 */
int contientElem(vector<string> vet, string a);

/**
 * @brief
 *
 * @param che
 */
void OrdVecteur (vector<Chemin*> &che);

void normaliza(QPointF *points, int size);



#endif
