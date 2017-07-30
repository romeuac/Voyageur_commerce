#ifndef CRODPX_H
#define CRODPX_H

#include <vector>
#include <string>
#include "ville.h"
#include "chemin.h"
#include "foncAux.h" // pour le compare et pous le cheminRandom
#include <iostream>
#include "algGen.h"

class croDPX : public algGen
{
public:
    explicit croDPX();

    /**
     * @brief Cette fonction fait l'identification des morceaux en commun entre les peres et les mettre dans un vector<vector<string>>
     *
     * @param Pere Le Pere choisi avant pour faire le croisement
     * @param Mere La Mere choisie avant pour faire le croisement
     * @return std::vector<std::vector<std::string> > Morceaux en commun entre les peres
     */
   std::vector<std::vector<std::string> > BlocsChe (const std::vector<std::string> &Pere, const std::vector<std::string> &Mere);

    /**
     * @brief Il cree un vecteur de strings avec les extremitees de chaque bloc pour choisir le debut de la solution et aussi mesurer las
     * distances entre la extremitee d'un bloc 'a l'autre
     *
     * @param BlocsChe Blocs Morceaux en commun entre les peres qui sont mis dans un vector<vector<string>>
     * @return std::vector<string> Il retourne le vector avec les extremitees des blocs (sous-ensembles communs aux Pere et Mere)
     */
    std::vector < string > ExtremBlocs (std::vector<std::vector<std::string> >  &BlocsChe);

    /**
     * @brief Il continue la nouvelle solution, "Fils", avec la continuation du bloc de la ville choisi, si elle est dans le millieu 'a la fin
     * on prendre la direction inverse
     *
     * @param fils La nouvelle solution qui est train d'etre produit pour le CroisementDPX
     * @param VilleChoisie C'est la ville choisie pour etre ajoutee 'a "fils"
     * @param Blocs Morceaux en commun entre les peres qui sont mis dans un vector<vector<string>>
     */
     void CompleterChe (std::vector < std::string > &fils, std::string VilleChoisie, std::vector< std::vector < std::string > > &Blocs);

    /**
     * @brief Cette fonction dit si la Derniere ville mise en "Fils" (VilleDer) est 'a cote de la Prochaine Ville (VillePro) choisie pour mettre
     * dans "Fils" dans le vector "Pere". Parce que selon le methode DPX il doit pas etre a cote pour ne pas repeter la meme structure
     * de son Pere.
     *
     * @param Pere Le Pere choisi avant pour faire le croisement
     * @param VilleDer Derniere ville de la nouvelle solution "Fils"
     * @param VillePro La ville choisie pour continuer le vector de la nouvelle solution
     * @return int Si la VillePro n'est pas 'a cote de la VilleDer dans le Pere ou la Mere la fonction retourne 0, si non 1
     */
  int VilleACote (const std::vector < std::string > &Pere, std::string VilleDer, std::string VillePro);

    /**
     * @brief Elle retourne la ville qui est dans la extremitee oposee de une certaine ville (ville) dedans son bloc (qui est dans "Blocs")
     *
     * @param Blocs Morceaux en commun entre les peres qui sont mis dans un vector<vector<string>>
     * @param ville C'est la premiere extremitee du bloc qui est utilisee pour trouver l'autre
     * @return std::string C'est l'autre extremitee du bloc
     */
  std::string VilOposee (std::vector< std::vector < std::string > > &Blocs, std::string ville);

    /**
     * @brief Cette fonction enleve la "villeEnle" et la oposee 'a cette ville (dedans son bloc) de l'ensemble de ville qui sont les extremitees
     * des blocs (Extrem)
     *
     * @param Extrem Un vector avec les strings qui sont les extremitees de chaque Bloc (sous ensemble du vector Blocs)
     * @param villeEnle C'est la ville qu'on doit enlever du vector "Extrem" parce que elle sera mise dans la nouvelle solution
     * et elle ne peut plus etre dans le vetor de extremitees des blocs qui manquent encore 'a etre mis dans le "Fils".
     * @param Blocs Morceaux en commun entre les peres qui sont mis dans un vector<vector<string>>
     */
      void EnleveDeExtr (std::vector < std::string > &Extrem, std::string villeEnle, std::vector< std::vector < std::string > > &Blocs);

    /**
     * @brief C'est algorithme voir la derniere string(une ville) de Fils et chercher la plus proche ville parmi les ExtreBlocs, cette ville ne peut pas etre la meme qui est
     * 'a cote de la ville choisie dans les peres. Cette fonction retourne cette ville, mais dans quelques cas elle sera la meme qui
     *  est 'a cote de la ville choisie dans ses peres parce que il n'y a pas d'autre possibilite de choix parmis les villes.
     *
     * @param Pere Le Pere choisi avant pour faire le croisement
     * @param Mere La Mere choisie avant pour faire le croisement
     * @param VilleDer La derniere ville de la nouvelle solution (Fils)
     * @param Extrem Un vector avec les strings qui sont les extremitees de chaque Bloc (sous ensemble du vector Blocs)
     * @param Blocs Morceaux en commun entre les peres qui sont mis dans un vector<vector<string>>
     * @return std::string Il retourne la ville choisie pour continuer le vector de la nouvelle solution
     */
 std::string VilleProche (const std::vector < std::string > &Pere, const std::vector < std::string > &Mere, std::string VilleDer, std::vector < std::string > &Extrem, std::vector< std::vector < std::string > > &Blocs);

    /**
     * @brief C'est l'algorithme de croisement "Distance Preserving Crossover" qui prend deux Peres dans le code et produit un fils.
     *  C'est la fonction principale pour ce croisement. C'est ici ou' on appelle les sous fonctions de ce croisement et on decide
     *  combien de fois il aura et les insertions de nouveaux fils et enlevement des pires.
     *
     * @param che Population de chemins
     * @param p Le parmetre responsable pour la probabilite de l'execution de la mutation
     * @param mut Choix du algorithme de mutation
     */
 void CroisementDPX(std::vector<Chemin*> &che, float p, const char *mut);

};

#endif // CRODPX_H
