#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>

#include "plateau.h"

#define NB_JOUEURS_MIN 2
#define NB_JOUEURS_MAX 7

struct Joueur
{
    std::string nom;
    int         pilePickominos[NB_PICKOMINOS];
    int         sommetPile;
};

void initialiserJoueur(const std::string nomJoueur, Joueur& joueur);

#endif