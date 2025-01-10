#include "joueur.h"

void initialiserJoueur(const std::string& nomJoueur, Joueur& joueur)
{
    joueur.nom        = nomJoueur;
    joueur.sommetPile = 0;
}