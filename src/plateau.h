#ifndef PLATEAU_H
#define PLATEAU_H

// #define DEBUG_PLATEAU

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

// Initialisation du jeu
void initialiserPlateau(Plateau& plateau);
void initialiserPickominos(Plateau& plateau);

// Dès
void lancerDes(Plateau& plateau);
bool estDejaRetenu(const Plateau& plateau, int faceDe);
bool retenirDes(Plateau& plateau, int faceDe);
bool estScoreValide(const int& scoreDes);
bool verifierSiVersRetenu(const Plateau& plateau);
int  calculerTotalDesRetenus(Plateau& plateau);

// Vérification/Lecture des pickominos
int  convertirNumeroPickomino(const int& scoreDes);
bool estPickominoVisible(const int& numero, const Jeu& jeu);
bool estPickominoInferieurVisible(const int& numero, const Jeu& jeu);
int  lirePickominoMaxBrochette(const Jeu& jeu);
bool estSommetPileJoueur(const int& numero, const int& joueurQuiJoue, const Jeu& jeu);
bool estBrochetteVide(const Jeu& jeu);

// Actions
void remettrePickomino(const int& joueurQuiJoue, Jeu& jeu);
void remettrePickominoMaxDansLaBrochette(const int& joueurQuiJoue, Jeu& jeu);
void remettrePickominoMaxChezLeJoueur(const int& joueurQuiJoue, Jeu& jeu);

void prendrePickomino(const int& numero, const int& joueurQuiJoue, Jeu& jeu);
void prendrePickominoInferieur(const int& numero, const int& joueurQuiJoue, Jeu& jeu);
void becqueter(const int& numero, const int& joueurQuiJoue, Jeu& jeu);

void changerAppartenancePickomino(const int& numero, Plateau& plateau, Appartenance appartenance);
void changerEtatPickominoBrochette(const int& numero, Plateau& plateau, Etat etat);

void incrementerSommetPileJoueur(const int& joueurConcerne, Jeu& jeu);
void decrementerSommetPileJoueur(const int& joueurConcerne, Jeu& jeu);

int comptageVers(const int& joueur, const Jeu& jeu);
int trouverScoreMaxPickominoJoueur(const int& joueur, const Jeu& jeu);

#endif