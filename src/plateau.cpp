#include "plateau.h"
#include <cstdlib>
#include <ctime>

void intialiserPlateau(Plateau& plateau)
{
    srand(time(NULL));
    plateau.nbDes = NB_DES;
    for(int i = 0; i < NB_DES; i++)
    {
        plateau.desRetenus[i] = 0;
    }
}

void lancerDes(int des[NB_DES], int nbDes)
{
    for(int i = 0; i < nbDes; i++)
    {
        des[i] = (rand() % NB_FACE_DES) + 1;
    }
}