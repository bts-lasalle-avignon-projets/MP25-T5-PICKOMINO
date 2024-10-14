#ifndef JOUEUR_H
#define JOUEUR_H

#define NB_CARACTERE_PSEUDO 7
#define NB_PICKOMINO 16

struct joueur
{
    char pseudo[NB_CARACTERE_PSEUDO];
    int pilePickomino[NB_PICKOMINO];
    int nbVers;
};



#endif