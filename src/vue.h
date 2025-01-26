#ifndef VUE_H
#define VUE_H

#include "jeu.h"

const std::string RESET_COLOR          = "\x1b[0m";  // Réinitialiser la couleur
const std::string ROUGE                = "\x1b[31m"; // Rouge
const std::string VERT                 = "\x1b[32m"; // Vert
const std::string JAUNE                = "\x1b[33m"; // Jaune
const std::string MAGENTA              = "\x1b[35m"; // Magenta
const int         NB_LIGNE_PICKOMINO   = 5;
const int         NB_PICKOMINO_EXEMPLE = 4;

int  definirNombreJoueurs();
int  demanderDesARetenir();
bool demanderRelancerDes();

void        afficherVersion();
void        afficherRegles();
std::string afficherPickominoExemple(const int& numeroExemple);
void        afficherDes(const Plateau& plateau);
void        afficherDesRetenus(const Plateau& plateau);
void        afficherTotalDesRetenus(const Plateau& plateau);
void        afficherQuelJoueurTour(const int& joueurQuiJoue, const Jeu& jeu);
void        afficherPileJoueur(const int& joueurQuiJoue, const Jeu& jeu);
void        afficherBrochette(const int& joueurQuiJoue, const Jeu& jeu);
std::string afficherPickomino(const int& numero,
                              const int& JoueurQuiJoue,
                              const int& numeroLigne,
                              const Jeu& jeu);

#endif