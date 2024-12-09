#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include "plateau.h"

struct Joueur
{
    std::string nom;
    Pickomino   pilePickominos[NB_PICKOMINOS];
    int         sommetPile;
};

void initialiserJoueur(const std::string nomJoueur, Joueur& joueur);

#endif