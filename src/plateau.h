#ifndef PLATEAU_H
#define PLATEAU_H

#include "pickomino.h"

enum Etat
{
    CACHE   = -1,
    VISIBLE = 0
};

struct Pickomino
{
    int  numero;
    int  nbVers;
    Etat etat;
};

struct Plateau
{
    Pickomino pickominos[NB_PICKOMINOS];
    int       nbDes;
    int       des[NB_DES];
    int       desRetenus[NB_DES];
    int       indexDernierDesRetenu;
};

struct Jeu;

void initialiserPlateau(Plateau& plateau);
void initialiserPickominos(Plateau plateau);
void initialiserIndexTableauDes(Plateau plateau);
void lancerDes(int des[NB_DES], int nbDes);

bool estScoreValide(const int& score);
bool verifierSiVersRetenu(const Plateau& plateau);
bool estDesInvalide(const Plateau& plateau);

bool estPickominoVisible(const int& numero, const Jeu& jeu);
bool estPickominoInferieurVisible(const int& numero, const Jeu& jeu);

#endif