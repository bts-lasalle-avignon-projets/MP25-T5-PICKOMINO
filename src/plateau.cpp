#include "plateau.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void initialiserPlateau(Plateau& plateau)
{
    srand(time(NULL));
    initialiserPickominos(plateau.pickominos);
    plateau.nbDes = NB_DES;
    for(int i = 0; i < NB_DES; i++)
    {
        plateau.desRetenus[i] = 0;
    }
}

void initialiserPickominos(Pickomino pickominos[NB_PICKOMINOS])
{
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        pickominos[i].numero = VALEUR_PICKOMINO_MIN + i;
        pickominos[i].nbVers = (i / PALIER_VER_PICKOMINO) + 1;
        pickominos[i].etat   = Etat::VISIBLE;
    }
}

void lancerDes(int des[NB_DES], int nbDes)
{
    for(int i = 0; i < nbDes; i++)
    {
        des[i] = (rand() % NB_FACE_DES) + 1;
    }
}
