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

void lancerDes(Plateau& plateau)
{
    for(int i = 0; i < plateau.nbDes; i++)
    {
        plateau.des[i] = (rand() % NB_FACE_DES) + 1;
    }
}

bool estDejaRetenue(const Plateau& plateau, int faceDe)
{
    for(int i = 0; i < NB_DES - plateau.nbDes; i++)
    {
        if(plateau.desRetenus[i] == faceDe)
        {
            return true;
        }
    }
    return false;
}

bool retenirDes(Plateau& plateau, int faceDe)
{
    if(estDejaRetenue(plateau, faceDe) || plateau.nbDes == 0)
    {
        return false;
    }

    int  nbDesRetenus = NB_DES - plateau.nbDes;
    bool retenue      = false;

    for(int i = 0; i < plateau.nbDes; i++)
    {
        if(plateau.des[i] == faceDe)
        {
            plateau.desRetenus[nbDesRetenus++] = plateau.des[i];
            retenue                            = true;
        }
    }

    plateau.nbDes = NB_DES - nbDesRetenus;

    return retenue;
}

int calculerTotalDesRetenus(Plateau& plateau)
{
    for(int i = 0; i < plateau.desRetenus[i]; i++)
    {
        plateau.totalRetenue = plateau.desRetenus[i] + plateau.desRetenus[i++];
    }
    return plateau.totalRetenue;
}