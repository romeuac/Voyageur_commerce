#include "algGen.h"
#include <time.h>
#include "omp.h"

using namespace std;

algGen::algGen ():comptIter(0), comptTemps(0) {}

float ** algGen::getMat(){
    return mat;
}

void algGen::setMat(float **m){
    mat = m;
}

float algGen::getPosMat(int a, int b) const {
    return mat[a][b];
}

//Il augment le compteur d'iterations
void algGen::AugCompIte (){
    comptIter++;
}

int algGen::getComptIter (){
    return comptIter;
}

std::vector<std::string> algGen::getVectcor(){
    return vectcor;
}

void algGen::setVectcor(std::vector<std::string> vec){
    vectcor = vec;
}

//Methodes generales

//Création de la grand matrice et Création de vecteur de correspondence
void algGen::creerMat (const vector<Ville*> & vil){
    //Prémier allocation dinamic de la matrice de distances
    mat = new float *[vil.size()];
//    vectcor = new std::vector<std::string>;

    //Deuxiéme allocation dinamique de la matrice de distances
    for (unsigned i=0; i<vil.size(); i++){
        //On crée les donnés internes de la matrice de façon dynamique, la dernière partie
        mat[i] = new float [vil.size()];

        //Il met le nom �  la fin du vecteur de correspondence
        vectcor.push_back ( (*vil[i]).getID());

        //Modification de la matrice de distances
        for (unsigned j = 0; j<vil.size(); j++){
            //Je prend la distance entre les deux villes par un méthode de la classe ville
            mat[i][j] = (*vil[i]).prendreDistVoisin((*vil[j]));
        }
    }
}

void algGen::desaloca (){
    int aux = vectcor.size();

    for (int i=0 ; i < aux ; i++) delete mat[i];

    vectcor.clear();
}

//Le coût de chaque chemin (solution) / Il accède un vecteur de string et retourne le valeur du chemin
float algGen::coutChemin (const vector<string> &str)
{
    float somme;
    somme = 0;
    unsigned i;

    //Il fait la somme des chemins
    for (i=0; i < (str.size()-1); i++){
        somme += mat[contientElem(vectcor,str[i])][contientElem(vectcor,str[i+1])];
    }

    //Il prendre le dernièr calcule
    somme += mat[contientElem(vectcor,str[i])][contientElem(vectcor,str[0])];

    return somme;
}

//Methodes genetiques

//Initialisation du vecteur de chemins qui vient déj�  du main par reference
void algGen::IniVecChemin(vector<Chemin*> &vche, int n)
{
    //On a une poupulation de n chemins, on a commencé avec l'idée de n=10
    vector<string> aux;
    //Ce partie change la variable initiale pour choisir les chiffres aleatoires
    srand((unsigned)time(0));

    //Il crée "n" chemins et calcule leur coût
    for (int i=0; i<n ; i++){
        //Il reçoit un vecteur de string (chemin) aleatoire de ce méthode, cheminrandom
        aux = cheminRandom(vectcor);

        vche.push_back(new Chemin(aux,coutChemin(aux), 0));
    }

    OrdVecteur(vche);

    for (int i=0;i<(n*2/3);i++)
        vche.pop_back();    //dá o pop_back de 800 piores elementos e sobram 400 no vetor
}

//Pour modifier l'ensemble de Chemins initiales
void algGen::IniModifChemin(vector<Chemin*> &vche, int n){
    //Creation de un nouveau vecteur de string égale au vectcor pour etre mixe
    vector<string> nouveauChe;
    std::map<std::string, std::map<float,string> > DistDeChaq;
    std::map<float,std::string> mapAux;
    int posAux, indAux, x;
    float quantiteNouvChe;

    //On analise la matrice et on met dedans un Map les couts et ses reespectifs strings
    for (std::vector<std::string>::iterator Vet = vectcor.begin() ; Vet != vectcor.end(); ++Vet){
        posAux = contientElem(vectcor,*Vet);

        //On met les distances relatives a ville *Vet dans la structure MAP "mapAux"
        for (unsigned i=0; i<vectcor.size(); i++) mapAux[mat[posAux][i]] = vectcor[i];

        //On ajoute les distances relatifs a la ville *Vet et on supprime tout le contenu de notre Map auxiliare pour l'autre usage
        DistDeChaq[*Vet] = mapAux;
        mapAux.clear();
    }

    //La quantite de villes qu'on va ajouter 'a nos solutions initiales
    quantiteNouvChe = 0.2*n;
    for (int t=0; t<quantiteNouvChe; t++){

        //On vide la prochaine nouvelle solution
        nouveauChe.clear();
        //La premiere ville, choisie de maniere aleatoire
        indAux = rand()%vectcor.size();
        nouveauChe.push_back(vectcor[indAux]);

        //Pour mettre le nombre precis de villes dedans la nouvelle solution
        for (unsigned a=0; a<vectcor.size(); a++){
            //On choisit l'indice d'une ville qui est relativement proche de cela qu'on voit maintenant
            indAux = rand()%((int)(0.2*vectcor.size()));
            //On parcourt le sous MAP relatif a la derniere ville du nouveau fils
            x=0;
            for (std::map<float,std::string>::iterator Vet = DistDeChaq[nouveauChe[nouveauChe.size()-1]].begin(); Vet != DistDeChaq[nouveauChe[nouveauChe.size()-1]].end(); ++Vet,x++){
                //On prend la ville qu'on veut et on finit le boucle
                if (x==indAux){
                    //Il faut voir si cette ville choisie fait deja partie de la nouvelle solution
                    if(contientElem(nouveauChe,Vet->second) == -1)nouveauChe.push_back(Vet->second);
                    //Si elle fait partie de a nouvelle solution on parcourt le MAP 'a nouveau pour trouver en partant dela
                    //la ville la plus proche de celle la' qui n'est pas deja dans la nouvelle solution
                    else{
                        for (std::map<float,std::string>::iterator it = DistDeChaq[nouveauChe[nouveauChe.size()-1]].begin(); it != DistDeChaq[nouveauChe[nouveauChe.size()-1]].end(); ++it){
                            if(contientElem(nouveauChe,it->second) == -1){
                                nouveauChe.push_back(it->second);
                                break;
                            }
                        }

                    }
                    break;
                }
            }
        }
        //On ajoute le nouveauChe 'a l'ensemble de chemins
        vche.push_back(new Chemin(nouveauChe,coutChemin(nouveauChe), 0));
    }
    //On fait la triage du vector de solutions "vche" et ensuite on supprime les dernieres positions
    OrdVecteur(vche);
    for (int t=0; t<quantiteNouvChe; t++) vche.pop_back();
}


//NOVO CRUZAMENTO ------------------DPX----------------------


//Mutation des 2 meilleurs chemins et substitution des pires (apres avoir fait une nouvelle selection)
void algGen::Mutation(std::vector<std::string> &fils, float p){
    //Si le programe n'est pas encore � la fin il fera les mutations avec une pourcentage pr�cis�...
    if (p > 0.1) p = ((rand())%100)/100.0;

    if (p < 0.1)           //20% de realizar a muta��o
    {
        //2% d'arriver sur le fils
        int taille = fils.size();
        int pos = rand()%taille;
        std::string stAux;
        int npos=rand()%taille;

        //Pour savoir si il a choisi le dernier element
        if (pos == taille)  npos = pos-1;

        //Il recoit un chemin � changer
        stAux = fils[npos];
        fils[npos] = fils[pos];
        fils[pos] = stAux;
    }
}


void algGen::Mutation2(std::vector<std::string> &fils){
    float p;
    int pos;
    std::string aux;

    p = (rand())%100/100.00;

    if (p < 0.1){

        pos = (rand())%fils.size();

        aux = fils[pos];
        fils[pos] = fils[(pos+1)%fils.size()];
        fils[(pos+1)%fils.size()] = aux;
    }

}

void algGen::Mutation3(std::vector<std::string> &fils){
    float p;
    p = (rand())%100/100.00;

    int i,j;

    if (p < 0.1)
    {
        int taille = fils.size();
        int pos = rand()%taille;
        int npos=rand()%taille;
        int aux;

        std::string stAux;

        //Pour savoir si il a choisi le dernier element
        if (pos == taille)  npos = pos-1;

        if(pos >= npos){
            aux = pos;
            pos = npos;
            npos = aux;
        }

        i = pos;
        j = npos;

        //On veut que "i" (pos) soit toujour plus petit que "j"(npos)
        while (i <= j){
            stAux = fils[i];

            fils[i] = fils[j];
            fils[j] = stAux;
            i++;
            j--;
        }
    }
}

//L'autre type de mutation
void algGen::Mutation4(std::vector<std::string> &fils, float p){

    int i,j;

    if (p > 0.1) p = ((rand())%100)/100.0;

    if (p < 0.1)
    {
        //2% d'arriver sur le fils
        int taille = fils.size();
        int pos = rand()%taille;
        int npos=rand()%taille;
        int aux;

        std::string stAux;

        //Pour savoir si il a choisi le dernier element
        if (pos == taille)  npos = pos-1;

        if(pos >= npos){
            aux = pos;
            pos = npos;
            npos = aux;
        }

        i = pos;
        j = npos;

        while (i <= j){
            stAux = fils[i];
            fils[i] = fils[j];
            fils[j] = stAux;
            i++;
            j--;
        }

        pos = rand()%taille;

        npos=rand()%taille;

        //Pour savoir si il a choisi le dernier element
        if (pos == taille)  npos = pos-1;

        //Il recoit un chemin � changer
        stAux = fils[npos];
        fils[npos] = fils[pos];
        fils[pos] = stAux;
    }
}

//2optSwap pour utiliser dedans la fonction de 2opt
std::vector<std::string> algGen::DeuxoptSwap(std::vector<std::string> &fils, int i, int k){
    std::vector<std::string> nouvChe;

    //int aux;

    for (int j=0; j<i; j++){
        nouvChe.push_back(fils[j]);
        //std::cout << j << " \n";
    }
    //aux = i;
    for (int j=k; j>(i-1); j--){
        //Il copie l'inverse de fils vers nouvChe
        nouvChe.push_back(fils[j]);
        //std::cout << j << " \n";
    }
    for (unsigned j=k+1; j<fils.size(); j++){
        nouvChe.push_back(fils[j]);
        //std::cout << j << " \n";
    }

    //std::cout << "\nChemin do 2optSwap\n";
    //for (int j=0; j<fils.size(); j++) std::cout<< nouvChe[j] << " ";
//    30004 01496 00000838833 90

    return nouvChe;
}

//On essaye l'algorutme 2-opt
void algGen::Deuxopt(std::vector<std::string> &fils, float p){
    float meillDisChem, nouvDisChe, nAlea, iAlea, stop, aux;
    std::vector<std::string> nouvChe;

    meillDisChem = 0;
    nouvDisChe = 1;

    stop=0;

    if (p < 0.2){
        while (stop==0){
            meillDisChem = coutChemin(fils);

            nAlea = rand()%(fils.size());

            iAlea = rand()%(fils.size());
            if(iAlea >= nAlea){
                aux = iAlea;
                iAlea = nAlea;
                nAlea = aux;
            }

            //std:cout << "Deuxopt, nAlea "<< nAlea<< " iAlea "<< iAlea<<std::endl;
            stop = 1;
            for (int i = iAlea; i<nAlea; i++){
                for (int k =i+1; k < (nAlea); k++){
                    //cout << "i = "<< i << " k = " << k <<endl;
                    //for ()
                    nouvChe = DeuxoptSwap(fils, i, k);
                    nouvDisChe = coutChemin(nouvChe);

                    if (nouvDisChe > meillDisChem){
                        fils = nouvChe;
                        stop = 1;
                        break;
                        //goto start_again;
                    }
                }
                if (stop == 1) break;
            }
        }
    }
}

//Il verifie si les conditions d'arret sont atteintes
int algGen::Terminaison(vector<Chemin*> &che, int temps,const char *temp , const char *repet){
    if ((che[0]->getComp()) > atoi(repet) || temps > atoi(temp))
   {
       //cout << che[0]->getComp() << " " << temps << endl;
       return 1;
   }
   return 0;
}
