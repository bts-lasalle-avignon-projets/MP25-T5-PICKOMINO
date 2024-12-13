#include "jeu.h"
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

    jouerTour(jeu);
}

void jouerTour(Jeu& jeu)
{
    bool tourFini  = false;
    bool lancerNul = false;

    do
    {
        lancerDes(jeu.plateau);
        afficherDes(jeu.plateau);

        int faceDe = demanderDesARetenir();
        lancerNul  = !retenirDes(jeu.plateau, faceDe);

        if(!lancerNul)
        {
            afficherDesRetenus(jeu.plateau);
            calculerTotalDesRetenus(jeu.plateau);
            afficherTotalDesRetenus(jeu.plateau);

            tourFini = !demanderRelancerDes();
        }
        else
        {
            tourFini = true;
        }
    } while(!tourFini);
}

bool estLancerNul(const int& score, const Plateau& plateau)
{
    // soit parce que la valeur des dés mis de côté ne suffit pas,
    bool estScoreValide(const int& score);

    // soit parce qu’il n’a mis aucune face « ver » de côté.
    bool verifierSiVersRetenu(const Plateau& plateau);

    return false;
}