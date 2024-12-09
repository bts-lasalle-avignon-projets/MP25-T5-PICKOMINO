#include "plateau.h"
#include "jeu.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

void initialiserPlateau(Plateau& plateau)
{
    srand(time(NULL));
    initialiserPickominos(plateau);
    initialiserIndexTableauDes(plateau);
}

void initialiserPickominos(Plateau plateau)
{
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        plateau.pickominos[i].numero = VALEUR_PICKOMINO_MIN + i;
        plateau.pickominos[i].nbVers = (i / PALIER_VER_PICKOMINO) + 1;
        plateau.pickominos[i].etat   = Etat::VISIBLE;
    }
}

void initialiserIndexTableauDes(Plateau plateau)
{
    plateau.indexDernierDesRetenu = 0;
}

void lancerDes(int des[NB_DES], int nbDes)
{
    for(int i = 0; i < nbDes; i++)
    {
        des[i] = (rand() % NB_FACE_DES) + 1;
    }
}

bool estScoreValide(const int& score)
{
    if(score >= VALEUR_PICKOMINO_MIN && score <= VALEUR_PICKOMINO_MAX)
        return false;
    return true;
}

bool verifierSiVersRetenu(const Plateau& plateau)
{
    for(int i = 0; i < NB_DES; i++)
    {
        if(plateau.desRetenus[i] == FACE_VER)
        {
            return true;
        }
    }
    return false;
}

bool estPickominoVisible(const int& numero, const Jeu& jeu)
{
    return (jeu.plateau.pickominos[numero - VALEUR_PICKOMINO_MIN].etat == VISIBLE);
}

bool estPickominoInferieurVisible(const int& numero, const Jeu& jeu)
{
    for(int i = 0; i < numero - VALEUR_PICKOMINO_MIN; i++)
    {
        for(int j = 0; j < jeu.nbJoueurs; j++)
            if(numero - i != jeu.joueurs[j].pilePickominos[jeu.joueurs[j].sommetPile].numero)
            {
                return (jeu.plateau.pickominos[numero - VALEUR_PICKOMINO_MIN].etat - i == VISIBLE);
            }
    }
    return false;
}