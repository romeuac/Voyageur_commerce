#ifndef ALGGEN_H
#define ALGGEN_H

#include <vector>
#include <string>
#include "ville.h"
#include "chemin.h"
#include "foncAux.h" // pour le compare et pous le cheminRandom
#include <cstdlib> // pour le srand()
#include <iostream>
#include <map>
#include "omp.h"

using namespace std;

/**
 * @brief Classe du algorithme genetique, contient les fonctions pour la reproduction, mutation,
 * terminaison et ses fonctions auxiliaires.
 *
 */
class algGen
{
    protected:
        //
        float ** mat; /**< Matrice avec les distances entre les villes, elle est symétrique avec diaggonal principal nulle */
        //
        std::vector<std::string> vectcor; /**< Ce vecteur a les noms de ville dans la même ordre que les villes dans la matrice "mat", il fait la correspondance */
        //
        int comptIter; /**< Compteur d'iteration fait depuis le début */
        //
        int comptTemps; /**< Compteur de temps fait depuis le début */

    public:

        void setMat(float **m);


        /**
         * @brief Constructeur de l'objet
         *
         */
        explicit algGen ();

        /**
         * @brief Returne la matrice de couts
         *
         * @return float
         */
        float **getMat();

        /**
         * @brief Le cout de chaque chemin (solution) / Il accede un vecteur de
         * string et retourne le valeur du chemin
         *
         * @param a position de la ligne de la matrice
         * @param b position de la colonne de la matrice
         * @return float
         */
       float getPosMat(int a, int b) const ;

        //Il augment le compteur d'iterations
        /**
         * @brief Compteur du nombre des iterations du boucle principal
         *
         */
       void AugCompIte ();

        /**
         * @brief Il returne le compteur des iterations
         *
         * @return int
         */
        int getComptIter ();

        /**
         * @brief Il returne le vecteur de correspondance des villes.
         *
         * @return std::vector<std::string>
         */
        std::vector<std::string> getVectcor();

        void setVectcor(std::vector <std::string> vec);

    //Méthodes generales

         /**
         * @brief Création de la grand matrice et Création de vecteur de correspondence
         *
         * @param vil Ensemble de villes qui on utilise pour contruire la matrice
         */
        void creerMat (const vector<Ville*> & vil);

        /**
         * @brief Le coût de chaque chemin (solution) / Il accède un vecteur de
         * string et retourne le valeur du chemin
         *
         * @param str Chemin pour lequel on va calculer le cout total
         * @return float
         */
      float coutChemin (const vector<string> &str);


    //Méthodes genétiques

        /**
         * @brief Initialisation du vecteur de chemins qui vient déj  du main par reference
         *
         * @param vche Ensemble de villes
         * @param n Taille de la population
         */
      void IniVecChemin(vector<Chemin*> &vche, int n);

        /**
         * @brief Pour ameliorer l'ensemble de Chemins initiales
         *
         * @param vche Ensemble de villes
         * @param n Taille de la population
         */
     void IniModifChemin(vector<Chemin*> &vche, int n);



        /**
         * @brief Mutation des chemins. L'inversion de deux villes
         *
         * @param fils Chemin qui va souffrir mutation
         * @param p Probabilité pour sortir de minimum local
         */
     void Mutation(vector<string> &fils, float p);

        /**
         * @brief Mutation des chemins. L'inversion de deux villes
         *
         */
       void Mutation2(std::vector<std::string> &fils);
        /**
         * @brief Mutation des chemins. L'inversion d'un morceau dans le chemin
         *
         */
       void Mutation3(std::vector<std::string> &fils);

        /**
         * @brief Mutation des chemins. L'inversion d'un morceau dans le chemin suivre d'une echange
         * de deux villes
         *
         */
     void Mutation4(std::vector<std::string> &fils, float p);

        /**
         * @brief Fonction auxiliaire du Deuxopt
         *
         */
        std::vector<std::string> DeuxoptSwap(std::vector<std::string> &fils, int i, int k);

        /**
         * @brief C'est une tentative de implementer le algorithme 2-opt pour aider dans le croisement
         * mais qui ne marche pas bien
         *
         */
        void Deuxopt(std::vector<std::string> &fils, float p);

        /**
         * @brief Il vérifie si les conditions d'arrêt sont atteints
         *
         * @param che Population de chemins
         * @param temps Temps courant du programme en execution
         * @param temp Condition de temps d'arrete
         * @param repet Condition de nombre de repetion
         * @return int
         */
         int Terminaison(vector<Chemin*> &che, int temps, const char *temp, const char *repet);


         /**
          * @brief Cette fonction fait la deallocation de la matrice de couts et du vectcor
          *
          */
         void desaloca ();
};

#endif

