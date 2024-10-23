#include "jeu.h"
#include "joueur.h"
#include "plateau.h"
#include "vue.h"

void jouerPickomino()
{
    Plateau plateau;

    intialiserPlateau(plateau);

    lancerDes(plateau.des, plateau.nbDes);

    afficherDes(plateau.des, plateau.nbDes);
    afficherDes(plateau.desRetenus, NB_DES - plateau.nbDes);
}
