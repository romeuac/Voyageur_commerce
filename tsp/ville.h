#ifndef VILLE_H
#define VILLE_H

#include <iostream>
#include <cmath>

/**
 * @brief Ville Class
 *
 * L'objet de la classe "ville" a un ID et sa position x/y. On a dans cette classe les fonctions pour
 * prendre les parametres et aussi le fonction pour prendre la distance entre deux villes.
 *
 */
class Ville
{

    private:
        std::string ID; /**< TODO */
        float x; /**< TODO */
        float y; /**< TODO */

    public:
        /**
         * @brief Constructeur de l'objet ville
         * En utilisant le "explicit" nous prevenos la construction de l'objet avec conversion
         * implicite de type
         *
         * @param nom String d'indentification de la ville
         * @param cordX X coordonner de la ville
         * @param cordY Y coordonner de la ville
         */
        explicit Ville (std::string nom, float cordX, float cordY);


        /**
         * @brief Il returne la coordonner X
         *
         * @return float
         */
        float getX() const;
        /**
         * @brief Il returne la coordonner X
         *
         * @return float
         */
        float getY() const;
        /**
         * @brief Il prendre la distance Euclidienne entre deux villes
         *
         * L'objet appelle la fonction avec une autre ville comme parametre pour prendre la distance
         * jusq'ua celui.
         *
         * @param v Le ville pour lequelle on calcule la distance
         * @return float
         */
        float prendreDistVoisin (Ville v);

        /**
         * @brief Il returne la string d'identification de la ville
         *
         * @return std::string
         */
        std::string getID();
};

#endif
