#include "jeu.h"
#include "vue.h"

void jouerPickomino()
{
    afficherVersion();

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

    jouerTour(jeu, jeu.plateau);
}

void jouerTour(Jeu& jeu, Plateau& plateau)
{
    for(int i = 0; i < jeu.nbJoueurs; i++)
    {
        bool tourFini  = false;
        bool lancerNul = false;
        plateau.nbDes  = NB_DES;

        afficherQuelJoueurTour(jeu.joueurs[i]);
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

                if(plateau.nbDes == 0)
                {
                    tourFini = true;
                }
                else
                {
                    tourFini = !demanderRelancerDes();
                }
            }
            else
            {
                tourFini = true;
            }
        } while(!tourFini);
    }
}

bool estLancerNul(const int& score, const Plateau& plateau)
{
    return false;
}