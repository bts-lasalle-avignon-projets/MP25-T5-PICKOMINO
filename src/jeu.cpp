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
    afficherRegles();
    for(int i = 0; i < jeu.nbJoueurs; i++)
    {
        initialiserJoueur("Joueur" + std::to_string(i + 1), jeu.joueurs[i]);
    }

    initialiserPlateau(jeu.plateau);
    do
    {
        for(int i = 0; i < jeu.nbJoueurs; i++)
        {
            afficherQuelJoueurTour(i, jeu);
            afficherBrochette(i, jeu);
            jouerTour(i, jeu);
        }
    } while(!estBrochetteVide(jeu));
}

void jouerTour(const int& joueurQuiJoue, Jeu& jeu)
{
    bool tourFini  = false;
    bool lancerNul = false;

    initialiserTour(jeu);
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
                tourFini = true;
            else
                tourFini = !demanderRelancerDes();
        }
        else
        {
            tourFini = true;
        }

    } while(!tourFini);

    int score  = calculerTotalDesRetenus(jeu.plateau);
    int numero = convertirNumeroPickomino(score);
    std::cout << "score = " << score << std::endl;

    if(!estLancerNul(score, jeu))
    {
        if(estPickominoVisible(numero, jeu) &&
           jeu.plateau.pickominos[numero].appartenance == Appartenance::BROCHETTE)
        {
            prendrePickomino(numero, joueurQuiJoue, jeu);
            std::cout << "Pris" << std::endl;
        }
        else if(estPickominoVisible(numero, jeu) &&
                !estSommetPileJoueur(numero, joueurQuiJoue, jeu))
        {
            std::cout << "BECQUETE" << std::endl;
            becqueter(numero, joueurQuiJoue, jeu);
            prendrePickomino(numero, joueurQuiJoue, jeu);
        }
        else
        {
            prendrePickominoInferieur(numero, joueurQuiJoue, jeu);
            std::cout << "INFERIEUR" << std::endl;
        }
    }
    else
    {
        remisePickomino(joueurQuiJoue, jeu);
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