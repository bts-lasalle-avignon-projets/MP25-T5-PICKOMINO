#ifndef VUE_H
#define VUE_H

#include "pickomino.h"
#include "plateau.h"
#include "joueur.h"

const std::string RESET = "\033[0m"; // Réinitialiser la couleur
const std::string YELLOW = "\033[33m"; // Jaune

int  definirNombreJoueurs();
int  demanderDesARetenir();
bool demanderRelancerDes();

void afficherVersion();
void afficherDes(const Plateau& plateau);
void afficherDesRetenus(const Plateau& plateau);
void afficherTotalDesRetenus(const Plateau& plateau);
void afficherQuelJoueurTour(const Joueur& joueur);
void affichageGagnant();

#endif