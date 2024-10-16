#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>

#define NB_CARACTERE_PSEUDO 7
#define NB_PICKOMINO 16
#define NB_JOUEUR 3
#define NB_JOUEUR_MAX 7 //test

struct Joueur
{
    std::string nom[NB_JOUEUR_MAX];
    int pilePickomino[NB_JOUEUR][NB_PICKOMINO];
};

extern Joueur joueur[NB_JOUEUR];


#endif