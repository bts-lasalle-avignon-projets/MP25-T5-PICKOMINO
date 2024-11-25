#include "joueur.h"
#include "jeu.h"

void initialiserJoueur(const std::string nomJoueur, Joueur& joueur)
{
    joueur.nom        = nomJoueur;
    joueur.sommetPile = 0;
}
