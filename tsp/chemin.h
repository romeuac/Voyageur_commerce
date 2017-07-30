#ifndef CHEMIN_H
#define CHEMIN_H

#include <vector>
#include <string>


/**
 * @brief L'objet de cette classe est un chemin en ligand tous les villes.
 *
 */
class Chemin
{
    private:

        std::vector<std::string> v; /**< TODO */
        float ccout; /**< TODO */
        int compteur; /**< TODO */

    public:
        /**
         * @brief Constructeur de l'objet
         *
         * @param vnom Vecteur de string en contient tous les villes
         * @param a Cout du chemin (somme des distances entre les villes)
         * @param b Compteur du nombre de fois que le chemin est dans la population
         */
        explicit Chemin (std::vector<std::string> vnom, float a, int b);

        /**
         * @brief Il returne le cout du chemin
         *
         * @return float
         */

        float getCout() const;

        /**
         * @brief Il returne le vecteur de strings de villes
         *
         * @return std::vector<std::string>
         */
        std::vector<std::string> getStr() const;

        /**
         * @brief Il returne le compteur du chemin
         *
         * @return int
         */
        int getComp() const;
        /**
         * @brief Il mettre le cout du chemin
         *
         * @param uneValeur Valeur qui sera ecrit
         */
        void setCout(int uneValeur);

        /**
         * @brief Incremente le compteur en 1
         *
         * @param uneValeur Valeur qui sera ecrit
         */

        void AugCompt ();

        void setComp(int uneValeur);
};

#endif
