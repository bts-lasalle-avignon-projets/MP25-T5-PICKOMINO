#ifndef VUE_H
#define VUE_H

#include "jeu.h"

int  definirNombreJoueurs();
int  demanderDesARetenir();
bool demanderRelancerDes();

void afficherVersion();
void afficherDes(const Plateau& plateau);
void afficherDesRetenus(const Plateau& plateau);
void afficherTotalDesRetenus(const Plateau& plateau);
void afficherQuelJoueurTour(const int& joueurQuiJoue, const Jeu& jeu);
void afficherPileJoueur(const int& joueurQuiJoue, const Jeu& jeu);
void afficherBrochette(const int& joueurQuiJoue, const Jeu& jeu);
std::string afficherPickomino(const int& numero, const int& JoueurQuiJoue, const Jeu& jeu);
std::string afficherPickominoJoueurActif(const int& numero, const int& nombreVerPickomino);
std::string afficherPickominoJoueur(const int& numero, const int& nombreVerPickomino);
std::string afficherPickominoNormal(const int& numero, const int& nombreVerPickomino);
std::string afficherPickominoCache(const int& numero, const int& nombreVerPickomino);

#endif