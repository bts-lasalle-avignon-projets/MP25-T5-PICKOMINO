#ifndef JEU_H
#define JEU_H

#include "joueur.h"

struct Jeu
{
    int     nbJoueurs;
    Joueur  joueurs[NB_JOUEURS_MAX];
    Plateau plateau;
};

void jouerPickomino();
void jouerTour(Jeu& jeu);
bool estLancerNul(const int& score, const Plateau& plateau);
void determinerGagnant(const Jeu& jeu);
void siEgaliteVersGagnant(const Jeu& jeu);

#endif