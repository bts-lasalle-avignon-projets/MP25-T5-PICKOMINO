#include "joueur.h"

char definitionNomJoueur(const int& nombreJoueur)
{
    for(int i = 0; i < nombreJoueur; i++)
    {
        joueur[i].nom = "Joueur " + std::to_string(i + 1);
    }
    return joueur.nom;
}

void initialisationPilePickominoJoueur(const int& nombreJoueur)
{
    for(int i = 0; i < nombreJoueur; i++)
    {
        for(int j = 0; j < NB_PICKOMINO; j++)
        {
            joueur[i].pilePickomino[j] = 0;
        }
    }
}