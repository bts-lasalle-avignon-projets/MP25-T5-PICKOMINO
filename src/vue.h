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

#endif