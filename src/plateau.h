#ifndef PLATEAU_H
#define PLATEAU_H

#include "pickomino.h"

struct Jeu;

enum Etat
{
    CACHE   = -1,
    VISIBLE = 0
};

enum Appartenance
{
    BROCHETTE = -1,
    JOUEUR    = 0
};

struct Pickomino
{
    int          numero;
    int          nbVers;
    Etat         etat;
    Appartenance appartenance;
};

struct Plateau
{
    Pickomino pickominos[NB_PICKOMINOS];
    int       nbDes;
    int       des[NB_DES];
    int       desRetenus[NB_DES];
    int       totalDes;
};

void initialiserPlateau(Plateau& plateau);
void initialiserPickominos(Plateau& plateau);
void lancerDes(Plateau& plateau);
bool estDejaRetenu(const Plateau& plateau, int faceDe);
bool retenirDes(Plateau& plateau, int faceDe);
bool estScoreValide(const int& score);
bool verifierSiVersRetenu(const Plateau& plateau);
int  estNumeroPickomino(const int& scoreDes);
bool estPickominoVisible(const int& numero, const Jeu& jeu);
bool estPickominoInferieurVisible(const int& numero, const Jeu& jeu);
int  calculerTotalDesRetenus(Plateau& plateau);
bool remettrePickomino(const int& joueurQuiJoue, Jeu& jeu);
int  lirePickominoMaxBrochette(Jeu& jeu);
bool estBrochetteVide(Jeu& jeu);

#endif