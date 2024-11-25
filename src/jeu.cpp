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

bool estLancerNul()
{
    // soit parce que la valeur des dés mis de côté ne suffit pas,
    bool estScoreValide(const int& score);

    // soit parce qu’il n’a mis aucune face « ver » de côté.
    bool verifierSiVersRetenu();

    // @todo n’obtienne sur un nouveau tirage que des valeurs ou des vers qu’il a déjà mis de côté.
    // bool estDesInvalide();
    return false;
}