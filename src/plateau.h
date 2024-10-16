#ifndef PLATEAU_H
#define PLATEAU_H

#define NB_DES      8
#define NB_FACE_DES 6

struct Pickomino
{
    int  numero;
    int  nbVer;
    bool etat;
};
extern Pickomino pickomino[16];

struct Des
{
    int  valeurFace[NB_FACE_DES];
    bool retenu;
};
extern Des des[NB_DES];

void initialisationPickomino();

void initialisationDes();

int  definirNombreJoueur();
bool verifierConditionJoueurMin(const int& nombreJoueur);
bool verifierConditionJoueurMin(const int& nombreJoueur);

int changerJoueur(const int& nombreJoueur, int auTourJoueur);

#endif