#include "jeu.h"
#include "vue.h"

#ifdef DEBUG_JEU
#include <iostream>
#endif

#include <iostream>
#include <limits>

void jouerPickomino()
{
    changerCouleurParDefaut(0);
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
            if(estBrochetteVide(jeu))
                break;
        }
    } while(!estBrochetteVide(jeu));
    gererFinDuJeu(jeu);
#ifdef DEBUG_JEU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "fin du jeu" << std::endl;
#endif
    changerCouleurParDefaut(1);
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
    int numero = convertirNumeroPickomino(score);

    if(!estLancerNul(score, numero, jeu, lancerNul))
    {
        if(estPickominoVisible(numero, jeu) &&
           jeu.plateau.pickominos[numero].appartenance == Appartenance::BROCHETTE)
        {
            prendrePickomino(numero, joueurQuiJoue, jeu);
        }
        else if(estPickominoVisible(numero, jeu) &&
                !estSommetPileJoueur(numero, joueurQuiJoue, jeu) &&
                jeu.plateau.pickominos[numero].appartenance == Appartenance::JOUEUR)
        {
            becqueter(numero, joueurQuiJoue, jeu);
            prendrePickomino(numero, joueurQuiJoue, jeu);
        }
        else if(estPickominoInferieurVisible(numero, jeu))
        {
            prendrePickominoInferieur(numero, joueurQuiJoue, jeu);
        }
        else
            remettrePickomino(joueurQuiJoue, jeu);
    }
    else
    {
        remettrePickomino(joueurQuiJoue, jeu);
    }
    afficherPileJoueur(joueurQuiJoue, jeu);
}

bool estLancerNul(const int& score, const int& numero, const Jeu& jeu, bool lancerNul)
{
    if(estScoreValide(score) && verifierSiVersRetenu(jeu.plateau) && lancerNul == false)
    {
        if(estPickominoVisible(numero, jeu) || estPickominoInferieurVisible(numero, jeu))
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

void gererFinDuJeu(const Jeu& jeu)
{
    int tableauDesScoresVers[jeu.nbJoueurs];
    int tableauDesvainqueur[jeu.nbJoueurs];
    int meilleurTotalVers      = 0;
    int occurence              = 1;
    int indiceTableauVainqueur = 0;
    int joueurParDefaut        = 0;
    int gagnant                = joueurParDefaut;

    for(int i = 0; i < jeu.nbJoueurs; i++) // Rempli le tableau de comparaison
    {
        int totalVers           = compterNbVers(i, jeu);
        tableauDesScoresVers[i] = totalVers;
    }

    for(int i = 0; i < jeu.nbJoueurs; i++)
    {
        if(meilleurTotalVers < tableauDesScoresVers[i] && tableauDesScoresVers[i] != 0)
        {
            meilleurTotalVers = tableauDesScoresVers[i];
            gagnant           = i;

            occurence              = 1;
            indiceTableauVainqueur = joueurParDefaut;
        }
        else if(meilleurTotalVers == tableauDesScoresVers[i] && tableauDesScoresVers[i] != 0)
        {
            occurence += 1;
            tableauDesvainqueur[indiceTableauVainqueur] = i;
            indiceTableauVainqueur++;
        }
    }
    if(occurence != 1) // Si égalité
    {
        int tableauDesScores[indiceTableauVainqueur];
        int gagnant         = tableauDesvainqueur[0];
        int meilleurScore   = 0;
        tableauDesScores[0] = trouverScoreMaxPickominoJoueur(gagnant, jeu);

        for(int i = 0; i < indiceTableauVainqueur; i++) // Rempli le tableau de comparaison
        {
            tableauDesScores[i] = trouverScoreMaxPickominoJoueur(i, jeu);
        }
        for(int i = 0; i < indiceTableauVainqueur; i++)
        {
            if(meilleurScore < tableauDesScores[i])
            {
                gagnant = tableauDesvainqueur[i];
            }
        }
    }

    afficherGagnant(jeu.joueurs[gagnant].nom, meilleurTotalVers);
}