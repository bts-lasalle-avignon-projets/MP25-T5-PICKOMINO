#ifndef VUE_H
#define VUE_H

#include "jeu.h"

const std::string RESET_COLOR          = "\x1b[37m"; // Réinitialiser la couleur
const std::string BLANC                = "\x1b[97m"; // Rouge
const std::string ROUGE                = "\x1b[31m"; // Rouge
const std::string VERT                 = "\x1b[32m"; // Vert
const std::string JAUNE                = "\x1b[33m"; // Jaune
const std::string MAGENTA              = "\x1b[35m"; // Magenta
const int         NB_LIGNE_PICKOMINO   = 5;
const int         NB_PICKOMINO_EXEMPLE = 4;

void changerCouleurParDefaut(const int& numero);
int  definirNombreJoueurs();
int  demanderDesARetenir();
bool demanderRelancerDes();
void viderTampon();

void        afficherVersion();
void        afficherRegles();
std::string afficherPickominoExemple(const int& numeroExemple);
void        afficherDes(const Plateau& plateau);
void        afficherDesRetenus(const Plateau& plateau);
void        afficherTotalDesRetenus(const Plateau& plateau);
void        afficherQuelJoueurTour(const int& joueurQuiJoue, const Jeu& jeu);
void        afficherPileJoueur(const int& joueurQuiJoue, const Jeu& jeu);
void        afficherBrochette(const int& joueurQuiJoue, const Jeu& jeu);
std::string afficherPickominoBrochette(const int& numero,
                                       const int& JoueurQuiJoue,
                                       const int& numeroLigne,
                                       const Jeu& jeu);
std::string afficherPickominoPileJoueur(const int& numero,
                                        const int& joueurQuiJoue,
                                        const Jeu& jeu);
std::string afficherPickominoVide();

#endif