#include "jeu.h"
#include "joueur.h"
#include "plateau.h"
#include "vue.h"

void jouerPickomino()
{
    Jeu jeu;

#ifdef SIMULATION
    int nbJoueurs = NB_JOUEURS_MIN;
#else
    int nbJoueurs = definirNombreJoueurs();
#endif

    jeu.nbJoueurs = nbJoueurs;
    for(int i = 0; i < nbJoueurs; i++)
    {
        initialiserJoueur("Joueur" + std::to_string(i + 1), jeu.joueurs[i]);
    }

    initialiserPlateau(jeu.plateau);

    lancerDes(jeu.plateau.des, jeu.plateau.nbDes);

    afficherDes(jeu.plateau.des, jeu.plateau.nbDes);
    afficherDes(jeu.plateau.desRetenus, (NB_DES - jeu.plateau.nbDes));
}
