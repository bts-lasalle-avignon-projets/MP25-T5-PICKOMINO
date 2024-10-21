#include "jeu.h"
#include "joueur.h"
#include "plateau.h"
#include "vue.h"

void jouerPickomino()
{
    int aleatoireDes[NB_DES];
    lanceeDes(aleatoireDes);
    affichageDesAleatoires(aleatoireDes); 
}
