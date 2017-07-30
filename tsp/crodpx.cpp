#include "crodpx.h"

croDPX::croDPX()
{
}

//Identification des morceaux en commun entre les peres et les mettre dans un vector<vector<string>>
    std::vector<std::vector<std::string> > croDPX::BlocsChe (const std::vector<std::string> &Pere, const std::vector<std::string> &Mere){
    std::vector <std::vector<std::string> > Block;
    std::vector<std::string>  BlockAux;

    //Mpos => C'est le index pour suivre le vector de la Mere
    unsigned Mpos;
    unsigned j;
    unsigned i;

    for (i=0; i<Pere.size(); i++){
        BlockAux.push_back(Pere[i]);
        Mpos = contientElem(Mere,Pere[i]);

        //Si la continuation du bloc est 'a droite dans le vector
        if( ( (i+1)!= Pere.size()) && (Mpos+1!= Pere.size())){
            if(Pere[i+1]==Mere[Mpos+1]){
            //On continue 'a suivre le Pere et Mere vers la direction "droite"
                for (j=1; (j+i)<Pere.size() && (j+Mpos)<Pere.size() && Pere[i+j]==Mere[Mpos+j]; j++){
                    BlockAux.push_back(Pere[i+j]);
                }
                i += j - 1;
            }
        }
        else{
            //Si la continuation du bloc est 'a gauche dans le vector
            if((i-1)!= -1 && (Mpos-1!= -1)){
                if(Pere[i-1]==Mere[Mpos-1]){
                    //On continue 'a suivre le Pere vers la direction "droite" mais vers la gauche pour la Mere
                    for (j=1; (j+i)<Pere.size() && (Mpos-j != -1) && Pere[i+j]==Mere[Mpos-j]; j++){
                        BlockAux.push_back(Pere[i+j]);
                    }
                    i += j - 1;
                }
            }

        }
        Block.push_back(BlockAux);
        BlockAux.clear();
    }
    return Block;
}

//FONCION vector<string> ExtremBlocs (&BlocsChe)
//Creer un vecteur de strings avec les extremitees de chaque bloc pour choisir le debut de la solution et aussi mesurer las
//distances entre la extremitee d'un bloc 'a l'autre
std::vector < string > croDPX::ExtremBlocs (std::vector<std::vector<std::string> > &BlocsChe){
    std::vector < string > Extremitees;
    unsigned i;
    //On passe pour tous les blocks
    for (i=0; i < BlocsChe.size(); i++){
        Extremitees.push_back(BlocsChe[i][0]);
        if (BlocsChe[i].size() != 1) Extremitees.push_back(BlocsChe[i][BlocsChe[i].size() - 1]);
    }
    return Extremitees;
}

//FONCION CompleterChe (&fils, &VilleChoisie, &BlocsChe)
//Continuer cette nouvelle solution avec la continuation du bloc de la ville choisi, si elle est dans le millieu 'a la fin
//on prendre la direction inverse
void croDPX::CompleterChe (std::vector < std::string > &fils, std::string VilleChoisie, std::vector< std::vector < std::string > > &Blocs){
    int posAux;
    int posEnleve=0;
    std::vector<std::string> BlocAux;

    for (unsigned j=0; j != Blocs.size() ; j++){
        posAux = contientElem(Blocs[j], VilleChoisie);
        if(posAux != -1){
            if(posAux == (Blocs[j].size()-1)){
                for(int i = (Blocs[j].size()-1); i != -1; i--){
                    fils.push_back(Blocs[j][i]);
                }
            }
            else {
                for(unsigned i = 0; i != Blocs[j].size(); i++) fils.push_back(Blocs[j][i]);
            }
            posEnleve = j;
        }
    }

    //On enleve le bloc dont les fils ont été ajoutés dans la variable "fils".
    BlocAux = Blocs[posEnleve];
    Blocs[posEnleve] = Blocs[Blocs.size()-1];
    Blocs[Blocs.size()-1] = BlocAux;

    Blocs.pop_back();

}

//FONCTION VilleACote (std::vector < std::string > Pere, std::string VilleDer, std::string VillePro)
//Cette fonction dit si la Derniere ville mise en "Fils" (VilleDer) est 'a cote de la Prochaine Ville (VillePro) choisie pour mettre
//dans "Fils" dans le vector "Pere". Parce que selon le methode DPX il doit pas etre a cote pour ne pas repeter la meme structure
//de son Pere.
int croDPX::VilleACote (const std::vector < std::string > &Pere, std::string VilleDer, std::string VillePro){
    int aux = contientElem(Pere,VilleDer);
    if ( (aux + 1)!= Pere.size()){
        if(Pere[aux+1] == VillePro) return 1;
    }
    if ( (aux - 1)!= -1 ){
        if( Pere[aux-1] == VillePro ) return 1;
    }

    //Si la VillePro n'est pas 'a cote de la VilleDer dans le Pere ou la Mere la fonction retourne 0, si non 1
    return 0;
}

//FONCTION std::string VilOposee (std::vector< std::vector < std::string > > &Blocs, std::string ville)
//Elle retourne la ville qui est dans la extremitee oposee de une certaine ville (ville) dedans son bloc
std::string croDPX::VilOposee (std::vector< std::vector < std::string > > &Blocs, std::string ville){
    int posAux;
    for (std::vector< std::vector <std::string > >::iterator Bit=Blocs.begin(); Bit!=Blocs.end() ; ++Bit){
        posAux = contientElem(*Bit, ville);
        if(posAux != -1){
            if(posAux == 0 && (*Bit).size()!= 1) return (*Bit)[(*Bit).size() - 1];
            return (*Bit)[0];
        }
    }
    return ville;
}

//FONCTION void EnleveDeExtr (std::vector < std::string > &Extrem, std::string villeEnle)
//Cette fonction enleve la "villeEnle" et la oposee 'a cette ville (dedans son bloc) de l'ensemble de ville qui sont les extremitees
//des blocs (Extrem)
void croDPX::EnleveDeExtr (std::vector < std::string > &Extrem, std::string villeEnle, std::vector< std::vector < std::string > > &Blocs){
    std::string auxSt (VilOposee(Blocs,villeEnle));
    std::vector < std::string >::iterator aux,aux2;
    for (std::vector < std::string >::iterator it=Extrem.begin(); it!=Extrem.end(); ++it){
        if(*it == villeEnle){
            aux = it;
            break;
        }
    }
    Extrem.erase(aux);
    for (std::vector < std::string >::iterator it=Extrem.begin(); it!=Extrem.end(); ++it){
        if(*it == auxSt) if(auxSt != villeEnle){
            aux2 = it;
            break;
        }
    }
    if(villeEnle != auxSt){
        Extrem.erase(aux2);
    }
}

//FONCTION VilleChoisie = string VilleProche (Pere 1, Pere 2, string, ExtreBlocs)
//Voir la derniere string(une ville) de Fils et chercher la plus proche ville parmi les ExtreBlocs, cette ville ne peut pas etre la meme qui est
//'a cote de la ville choisie dans les peres. Cette fonction retourne cette ville, mais dans quelques cas elle sera la meme qui
//est 'a cote de la ville choisie dans ses peres parce que il n'y a pas d'autre possibilite de choix parmis les villes.
std::string croDPX::VilleProche (const std::vector < std::string > &Pere, const std::vector < std::string > &Mere, std::string VilleDer, std::vector < std::string > &Extrem, std::vector< std::vector < std::string > > &Blocs){
    unsigned i;
    std::map<float,std::string> Dic;
    std::map<float,std::string>::iterator AuxDic;

    //Calculer les distances entre la VilleDer et les villesDer et les mettre dans un Dic
    for (i=0; i<Extrem.size(); i++){
        Dic[mat[contientElem(vectcor, Extrem[i])][contientElem(vectcor, VilleDer)]] = Extrem[i];
    }

    //Il returne la plus proche ville trouvee et que n'est pas normalment 'a cote de la VilleDer dans le Pere ou Mere
    for (std::map<float,std::string>::iterator it=Dic.begin(); it!=Dic.end(); ++it){
        if (VilleACote(Pere, VilleDer, (it)->second) == 0 && VilleACote(Mere, VilleDer, (it)->second) == 0){
            EnleveDeExtr(Extrem,it->second,Blocs);
            return it->second;
        }

    }
    AuxDic=Dic.begin();
    EnleveDeExtr(Extrem,AuxDic->second,Blocs);
    return AuxDic->second;
}



//Croisement DPX Crossover
//C'est la fonction principale pour ce croisement. C'est ici ou' on appelle les sous fonctions de ce croisement et on decide
//combien de fois il aura et les insertions de nouveaux fils et enlevement des pires.
void croDPX::CroisementDPX(std::vector<Chemin*> &che, float p, const char *mut){
    //Le nouveau fils
    std::vector < std::string > fils;
    //Les blocs en comum entre le Pere e la Mere pour chaque croisement
    std::vector< std::vector < std::string > > Blocs;
    //La "liste" de extremitees de chaque bloc
    std::vector < std::string > Extrem;
    //Cette une variable qui controle la quantite de fois qu'on fait le croisement
    int auxCheSize;
    //Variable pour les boucles
    int i;
    //C'est la Ville choisie pour commencer le nouveau Fils, choisie de maniere aleatoire
    std::string VilleChoisie;
    //Les positions aleatoires du Pere et de la Mere
    int PereAleat, MereAleat;


    //Nombre de fois qu'on fait le croisement
    auxCheSize = 0.3 * (che.size());


    //FOR - Executer pour le nombre de fois qu'on veut faire le croisement
    for (i=0 ; i < (auxCheSize - 1); i++)
    {
        //Les positions aleatoires du Pere et de la Mere
        PereAleat = rand()%auxCheSize;
        MereAleat = rand()%auxCheSize;


        //FONCION vector<vector<string>> BlocsChe (Pere 1, Pere 2)
        //Identification des morceaux en commun entre les peres et les mettre dans un vector<vector<string>>
        //Example: [[A,B,C],[R,F],[W,V],[T,J,L,H]]
        Blocs = BlocsChe (che[PereAleat]->getStr(),che[MereAleat]->getStr());

        //FONCION vector<string> ExtreBlocs (BlocsChe)
        //Creer un vecteur de strings avec les extremitees de chaque bloc pour choisir le debut de la solution et aussi mesurer las
        //distances entre la extremitee d'un bloc 'a l'autre
        //Example: [A,C,R,F,W,V,T,H]
        Extrem = ExtremBlocs(Blocs);

        //Choisir une ville (string VilleChoisie) aleatoire pour commencer la nouvelle solution (vector<string> Fils (taille: ch[0]->getStr.size()) )
        VilleChoisie = Extrem[rand()%Extrem.size()];

        //On enleve la premier ville de fils, la "VilleChoisie"
        EnleveDeExtr(Extrem,VilleChoisie, Blocs);


        //FONCION CompleterChe (Fils, VilleChoisie, BlocsChe)
        //Continuer cette nouvelle solution avec la continuation du bloc de la ville choisi, si elle est 'dans le millieu'a la fin
        //on prendre la direction inverse
        CompleterChe (fils, VilleChoisie, Blocs);
        //std::cout << "Depois de CompleterChe, fils size: "<< fils.size()<< endl;

        //On complete le Fils avec la fonctio complete Chemin et on choisit la prochaine ville a cote de la derniere dans le fils
        //avec la fonction "VilleProche". Cette boucle continue jusqu'au moment ou' il existe un bloc dedans le vector de Blocs
        //comuns entre les peres
        while(Blocs.size() != 0){
              CompleterChe (fils, VilleProche (che[PereAleat]->getStr(), che[MereAleat]->getStr(), fils[fils.size() -1], Extrem, Blocs) , Blocs);
        }

        //On appelle la Mutation
        switch (atoi(mut))
        {
            case 1:
                Mutation(fils, p);
                break;
            case 2:
                Mutation2(fils);
                break;
            case 3:
                Mutation3(fils);
                break;
            case 4:
                Mutation4(fils, p);
                break;
            default:
                std::cout << "Erreur: Choisir la mutation entre 1 et 4" << std::endl;
                exit (EXIT_FAILURE);
        }
        //On ajoute le nouveau fils au enssemble de chemins
        che.push_back(new Chemin( fils, coutChemin(fils), 0) );

        //On efface les contenus de fils
        fils.clear();
    }

    //On fait la triage de l'ensemble de solutions de notre algorithme
    OrdVecteur(che);

    //On supprime les solutions mauvaises pour mantenir la quantite de solutions constante
    for(i=0 ; i < (auxCheSize - 1); i++)        //(0,1) (2,3) (4,5) (6,7)...
    {
        che.pop_back();
    }

    return;
}
