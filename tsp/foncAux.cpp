#include "foncAux.h"
#include <time.h>

using namespace std;

//Groupe de fonctions auxiliaires qu'on utilise dans les autres fichier, mais on les separe dans ce espace pour
//avoir une meilleure organization de nos travail.

//Affiche la grande matrice
void afficheMat(float **mat){
    unsigned  i,j;

    for (i=0; i<21 ; i++){
        for (j=0; j<21; j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void afficheStr(vector<string> &str){
    for (unsigned  j = 0; j < str.size() ; j++) cout << str[j];
    cout << endl;
}


//Affiche tous les chemins
void afficheChe(vector<Chemin*> &che){

    //cout << che[0]->getStr()[0] << endl<< endl<<endl;

    for (unsigned  i = 0; i<che.size() ; i++){
        for (unsigned  j = 0; j < che[i]->getStr().size() ; j++) cout << che[i]->getStr()[j] << " ";
        cout << endl;
    }


}

//Auxiliaire pour cheminRandom() random generator function:
ptrdiff_t myrandom (ptrdiff_t i) { return rand()%i;}

//Ce méthode retourne une vecteur de string aleatoire, cet une possibilité de solution initiale
vector<string> cheminRandom(vector<string> &vectcor){
    //Création de un nouveau vecteur de string égale au vectcor pour être mixé
    vector<string> valet(vectcor);

    //Pour savoir la taille du vecteur de sting
    //int nombre = vectcor.size();
    //cout << valet[0] <<" valet nao mixado\n";
    random_shuffle ( valet.begin(), valet.end() , myrandom);
    //cout << valet[0] <<" valet mixado\n";
    return valet;
}

//Fonction auxiliaire
int compare (const void * a, const void * b)
{
    Chemin* pa = *(Chemin**) a;
    Chemin* pb = *(Chemin**) b;

    if ((*pb).getCout() < (*pa).getCout() ){
        return 1;
        }
    else if ((*pa).getCout() < (*pb).getCout()){
        return -1;
        }
    return 0;

}


//Il calcule le temps - Il reçoit le variable qu'on prends au début du code, dans le main.
int Temps (time_t tstart){
    time_t tend;
    tend = time(0);
    return difftime(tend, tstart);
}

std::vector < Ville * >lireFichier (char *fichier)
{
    std::vector < Ville * >villes;
    std::string ville;
    float a, b;                     //coordenadas vilas
    int tam, i;
    char v[10];

    std::cout << fichier << std::endl;

    if ((tam = atoi(fichier)) != 0){           // villes aleatoires
        for (i=0 ; i < tam ; i++){
            sprintf(v,"%d",i);
            villes.push_back(new Ville (v, rand()%400 , rand()%400));
        }

        return villes;
    }
    else{

        std::ifstream monFichier;
        monFichier.open (fichier);

        if (monFichier.is_open ())
        {
            while (monFichier >> ville >> a >> b){
                villes.push_back (new Ville (ville, a, b));
            }
        }
        else{
            std::cout << "Unable to open file\n";
            exit(1);
        }

        monFichier.close();

        return villes;
        //retorna o VETOR DE VILAS ;
    }
}

//Il verifie s'il y a l'element dedans vet et retourne sa position, s'il y a pas il retourne -1
int contientElem(vector<string> vet, string a)
{
    unsigned int i;

    for (i=0 ; i < vet.size() ; i++)
    {
        if (vet[i] == a) return i;
    }
    return -1;
}

//Selection des meilleures solutions (chemin), ordonnant le tableau de chemeins par ses coÃ»t avec les meilleures au dÃ©but
void OrdVecteur (vector<Chemin*> &che)
{
    qsort (&che[0], che.size(), sizeof(Chemin *), compare);
//          On sait que le meilleur chemin est le premier chemin et le temps qu'il est le premier est sur son competeur une fois qui depuis son
//          naissance il est dÃ©jÃ  le meilleur
}

void normaliza(QPointF *points, int size)
{
    float max;
    float aux;
    int i;

    max = points[0].rx();

    for (i=0 ; i < size ; i++)          //trouver le valeur maximum d'entre les coordinates de points
    {
        if (max < points[i].rx()) max = points[i].rx();
        if (max < points[i].ry()) max = points[i].ry();
    }

    for (i=0 ; i < size ; i++)
    {
        aux = 600*(points[i].rx())/max;
        points[i].setX(aux);

        aux = 600*(points[i].ry())/max;
        points[i].setY(aux);
    }
}
