#include "cropmx.h"

croPMX::croPMX(){}

void croPMX::consertaOutraPosicao(vector<string> &fils, const vector<string> &pere, int &divisa)
{
    int taille = ( pere.size() - divisa) % 5;
    if (taille == 0) taille++;

    std::vector <string> pai = pere;
    std::vector <string> filho = fils;

    int p;
    int i;
    unsigned int j;

//primeira parte do filho
    for (i=0; i<divisa; i++)
    {
        p = contientElem(fils, pai[i]);

        if ( p == -1)
        {
            fils[i] = pai[i];
        }
        else{
            fils[i] = element(fils, pai, p);
        }
    }

//segunda parte do filho apÃ³s a divisÃ£o
    for (j=(divisa+taille); j<pai.size(); j++)
    {
        p = contientElem(fils, pai[j]);

        if ( p == -1)
        {
            fils[j] = pai[j];
        }
        else{
            fils[j] = element(fils, pai, p);
        }
    }
}

//Cette fonction retourne la bonne string pour le croisement
string croPMX::element(vector<string> &filho, vector<string> &pai, int pos)
{
    int sai = 0;
    string result;

    while(sai == 0)
    {
        result = pai[pos];
        pos = contientElem(filho,result);
        if ( pos == -1)
        {
            sai = 1;
        }
    }
    return result;
}

//Croisement des meilleurs chemins et substitution des pires ils commencent triÃ© (cruza 10%)
void croPMX::CroisementPMX(vector<Chemin*> &che, float &p, const char *mut)
{
    std::vector < string > filho1 (vectcor.size());
    std::vector < string > filho2 (vectcor.size());

    float auxCheSize;
    int divisa,taille, i, j;
    unsigned int k;
    divisa = rand() % vectcor.size();

    //Pour changer la taille du vecteur quand elle est zero
    taille = ( ( che[0]->getStr().size()) - divisa) % 5;
    if (taille == 0) taille++;

    //Nombre de fois qu'on fait le croisement
    auxCheSize = 0.3 * (che.size());

    for (i=0 ; i< (auxCheSize - 1); i+=2)        //(0,1) (2,3) (4,5) (6,7)...
    {
        for (j=0 ; j < taille; j++)
        {

            filho1[divisa+j] = che[i+1]->getStr()[divisa+j];               //pega o trecho dos dois melhores pai
            filho2[divisa+j] = che[i]->getStr()[divisa+j];
        }

        consertaOutraPosicao( filho1, che[i]->getStr() , divisa);
        //Deuxopt(filho1,p);
        switch (atoi(mut))
        {
            case 1:
                Mutation(filho1, p);
                break;
            case 2:
                Mutation2(filho1);
                break;
            case 3:
                Mutation3(filho1);
                break;
            case 4:
                Mutation4(filho1, p);
                break;
            default:
                std::cout << "Erreur: Choisir la mutation entre 1 et 4" << std::endl;
                exit (EXIT_FAILURE);
        }
        che.push_back(new Chemin( filho1, coutChemin(filho1), 0));

        consertaOutraPosicao(filho2, che[i+1]->getStr(), divisa);
        //Deuxopt(filho2,p);
        switch (atoi(mut))
        {
            case 1:
                Mutation(filho2, p);
                break;
            case 2:
                Mutation2(filho2);
                break;
            case 3:
                Mutation3(filho2);
                break;
            case 4:
                Mutation4(filho2, p);
                break;
            default:
                std::cout << "Erreur: Choisir la mutation entre 1 et 4" << std::endl;
                exit (EXIT_FAILURE);
        }
        che.push_back(new Chemin(filho2,coutChemin(filho2), 0));


        for (k=0; k < vectcor.size() ; k++)     //reinicializa os filhos para serem usados
                                    //na prÃ³xima iteraÃ§Ã£o de cruzamento
        {

            filho1[k] = "";
            filho2[k] = "";
        }
    }

    //Il trie le vecteur aprÃ¨s faire les croisements
    OrdVecteur(che);

    for(i=0 ; i < auxCheSize - 1; i+=2)        //(0,1) (2,3) (4,5) (6,7)...
    {
        che.pop_back();
        che.pop_back();
    }
}

