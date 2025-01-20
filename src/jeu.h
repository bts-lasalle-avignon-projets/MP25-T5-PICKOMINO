#ifndef JEU_H
#define JEU_H

#include "joueur.h"

// #define SIMULATION

struct Jeu
{
    int     nbJoueurs;
    Joueur  joueurs[NB_JOUEURS_MAX];
    Plateau plateau;
};

void jouerPickomino();
void jouerTour(Jeu& jeu, Plateau& plateau);
bool estLancerNul(const int& score, const Plateau& plateau);

#endif