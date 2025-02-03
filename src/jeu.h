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
bool estLancerNul(const int& score, const int& numero, const Jeu& jeu, bool lancerNul);
void initialiserTour(Jeu& jeu);
void finDuJeu(Jeu& jeu);

#endif