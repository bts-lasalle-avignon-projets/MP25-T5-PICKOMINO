#include "jeu.h"
#include "vue.h"

#include <iostream> //test
#include <limits>   //test

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

    jouerTour(jeu);

    determinerGagnant(jeu);
}

void jouerTour(Jeu& jeu)
{
    for(int i = 0; i < jeu.nbJoueurs; i++)
    {
        bool tourFini     = false;
        bool lancerNul    = false;
        jeu.plateau.nbDes = NB_DES;

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
    }
}

bool estLancerNul(const int& score, const Plateau& plateau)
{
    return false;
}

void determinerGagnant(const Jeu& jeu)
{
    int meilleurScore = -1;
    int indexGagnant  = -1;

    for(int i = 0; i < jeu.nbJoueurs; i++)
    {
        int scoreVers = 0;
        for(int j = 0; j < NB_PICKOMINOS; j++)
        {
            scoreVers += jeu.joueurs[i].pilePickominos[j].nbVers;
        }

        std::cout << "Score de " << jeu.joueurs[i].nom << ": " << scoreVers << " vers"
                  << std::endl; // test

        if(scoreVers > meilleurScore)
        {
            meilleurScore = scoreVers;
            indexGagnant  = i;
        }
        else if(scoreVers == meilleurScore)
        {
            siEgaliteVersGagnant;
        }
    }

    if(indexGagnant != -1) // test
    {
        std::cout << "Le gagnant est " << jeu.joueurs[indexGagnant].nom << " avec " << meilleurScore
                  << " vers!" << std::endl;
    }
    else
    {
        std::cout << "Aucun gagnant." << std::endl;
    }
}

void siEgaliteVersGagnant(const Jeu& jeu)
{
    for(int i = 0; i < jeu.nbJoueurs; i++)
    {
        int scorePickomino = 0;
        for(int j = 0; j < NB_PICKOMINOS; j++)
        {
            scorePickomino += jeu.joueurs[i].pilePickominos[j].numero;
        }
    }
}