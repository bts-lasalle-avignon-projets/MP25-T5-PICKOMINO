#ifndef JEU_H
#define JEU_H

//#define DEBUG_JEU

#include "joueur.h"

struct Jeu
{
    int     nbJoueurs;
    Joueur  joueurs[NB_JOUEURS_MAX];
    Plateau plateau;
};

void jouerPickomino();
void jouerTour(const int& joueurQuiJoue, Jeu& jeu);
bool estLancerNul(const int& score, const int& numero, const Jeu& jeu);
void initialiserTour(Jeu& jeu);

#endif