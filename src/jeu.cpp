#include "jeu.h"
#include "vue.h"

#ifdef DEBUG_JEU
#include <iostream>
#endif

void jouerPickomino()
{
    afficherVersion();

    Jeu jeu;

    jeu.nbJoueurs = definirNombreJoueurs();

    for(int i = 0; i < jeu.nbJoueurs; i++)
    {
        initialiserJoueur("Joueur" + std::to_string(i + 1), jeu.joueurs[i]);
    }

    initialiserPlateau(jeu.plateau);

    jouerTour(jeu);
}

void jouerTour(Jeu& jeu)
{
    for(int i = 0; i < jeu.nbJoueurs; i++)
    {
        bool tourFini  = false;
        bool lancerNul = false;

        initialiserTour(jeu);
        afficherBrochette(jeu.plateau);
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

                if(jeu.plateau.nbDes == 0)
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

        int score = calculerTotalDesRetenus(jeu.plateau);
#ifdef DEBUG_JEU
        std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
        std::cout << "score = " << score << std::endl;
#endif
        if(!estLancerNul(score, jeu))
        {
            // @todo récupérer le pickomino
#ifdef DEBUG_JEU
            std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
            std::cout << "récupérer le pickomino" << std::endl;
#endif
        }
        else
        {
            // @todo remettre un pickomino et éventuellement retourner un pickomino
#ifdef DEBUG_JEU
            std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
            std::cout << "remettre un pickomino et éventuellement retourner un pickomino"
                      << std::endl;
#endif
        }
    }
}

bool estLancerNul(const int& score, const Jeu& jeu)
{
    if(estScoreValide(score) && verifierSiVersRetenu(jeu.plateau))
    {
        if(estPickominoVisible(score - VALEUR_PICKOMINO_MIN, jeu) ||
           estPickominoInferieurVisible(score - VALEUR_PICKOMINO_MIN, jeu))
            return false;
    }
    return true;
}

void initialiserTour(Jeu& jeu)
{
    jeu.plateau.nbDes = NB_DES;
    for(int i = 0; i < NB_DES; i++)
    {
        jeu.plateau.desRetenus[i] = 0;
    }
}