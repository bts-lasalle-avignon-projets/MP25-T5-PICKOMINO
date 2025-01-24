#ifndef VUE_H
#define VUE_H

#include "pickomino.h"
#include "plateau.h"
#include "joueur.h"

int  definirNombreJoueurs();
int  demanderDesARetenir();
bool demanderRelancerDes();

void afficherVersion();
void afficherDes(const Plateau& plateau);
void afficherDesRetenus(const Plateau& plateau);
void afficherTotalDesRetenus(const Plateau& plateau);
void afficherQuelJoueurTour(const Joueur& joueur);
void afficherPileJoueur(const Joueur& joueur);
void afficherBrochette(const Plateau& plateau);
std::string afficherPickomino(const int& numero, const Plateau& plateau);

#endif