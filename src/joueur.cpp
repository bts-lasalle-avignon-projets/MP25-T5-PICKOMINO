#include "joueur.h"

struct joueur
{
    char pseudo[NB_CARACTERE_PSEUDO];
    int pilePickomino[NB_PICKOMINO];
    int nbVers;
};