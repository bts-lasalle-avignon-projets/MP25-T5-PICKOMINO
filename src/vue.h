#ifndef VUE_H
#define VUE_H

#include "pickomino.h"
#include "plateau.h"

int  definirNombreJoueurs();
int  demanderDesARetenir();
bool demanderRelancerDes();
void afficherDes(const Plateau& plateau);
void afficherDesRetenus(const Plateau& plateau);
void afficherTotalDesRetenus(const Plateau& plateau);

#endif