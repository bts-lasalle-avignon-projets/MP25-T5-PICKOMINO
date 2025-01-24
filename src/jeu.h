#ifndef JEU_H
#define JEU_H

#include "joueur.h"

#define DEBUG_JEU

struct Jeu
{
    int     nbJoueurs;
    Joueur  joueurs[NB_JOUEURS_MAX];
    Plateau plateau;
};

void jouerPickomino();
void jouerTour(Jeu& jeu);
bool estLancerNul(const int& score, const Jeu& jeu);
void initialiserTour(Jeu& jeu);

#endif