#include "plateau.h"
#include "jeu.h"
#include <cstdlib>
#include <ctime>

#ifdef DEBUG_PLATEAU
#include <iostream>
#endif

void initialiserPlateau(Plateau& plateau)
{
    srand(time(NULL));
    initialiserPickominos(plateau);
    plateau.nbDes = NB_DES;
    for(int i = 0; i < NB_DES; i++)
    {
        plateau.desRetenus[i] = 0;
    }
}

void initialiserPickominos(Plateau& plateau)
{
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        plateau.pickominos[i].numero       = VALEUR_PICKOMINO_MIN + i;
        plateau.pickominos[i].nbVers       = (i / PALIER_VER_PICKOMINO) + 1;
        plateau.pickominos[i].etat         = Etat::VISIBLE;
        plateau.pickominos[i].appartenance = Appartenance::BROCHETTE;
    }
}

void lancerDes(Plateau& plateau)
{
    for(int i = 0; i < plateau.nbDes; i++)
    {
        plateau.des[i] = (rand() % NB_FACE_DES) + 1;
    }
}

bool estDejaRetenu(const Plateau& plateau, int faceDe)
{
    for(int i = 0; i < NB_DES - plateau.nbDes; i++)
    {
        if(plateau.desRetenus[i] == faceDe)
        {
            return true;
        }
    }
    return false;
}

bool retenirDes(Plateau& plateau, int faceDe)
{
    if(estDejaRetenu(plateau, faceDe) || plateau.nbDes == 0)
    {
        return false;
    }

    int  nbDesRetenus = NB_DES - plateau.nbDes;
    bool retenue      = false;

    for(int i = 0; i < plateau.nbDes; i++)
    {
        if(plateau.des[i] == faceDe)
        {
            plateau.desRetenus[nbDesRetenus++] = plateau.des[i];
            retenue                            = true;
        }
    }

    plateau.nbDes = NB_DES - nbDesRetenus;

    return retenue;
}

bool estScoreValide(const int& scoreDes)
{
    if(scoreDes >= VALEUR_PICKOMINO_MIN && scoreDes <= VALEUR_PICKOMINO_MAX)
        return true;
    return false;
}

bool verifierSiVersRetenu(const Plateau& plateau)
{
    for(int i = 0; i < (NB_DES - plateau.nbDes); i++)
    {
        if(plateau.desRetenus[i] == FACE_VER)
        {
            return true;
        }
    }
    return false;
}

int calculerTotalDesRetenus(Plateau& plateau)
{
    plateau.totalDes = 0;

    for(int i = 0; i < NB_DES - plateau.nbDes; i++)
    {
        if(plateau.desRetenus[i] == FACE_VER)
        {
            plateau.totalDes += VALEUR_FACE_VER;
            continue;
        }
        else
        {
            plateau.totalDes += plateau.desRetenus[i];
        }
    }

    return plateau.totalDes;
}

int convertirNumeroPickomino(const int& scoreDes)
{
    return (scoreDes - VALEUR_PICKOMINO_MIN);
}

bool estPickominoVisible(const int& numero, const Jeu& jeu)
{
    return (jeu.plateau.pickominos[numero].etat == Etat::VISIBLE);
}

bool estPickominoInferieurVisible(const int& numero, const Jeu& jeu)
{
    for(int i = numero; i >= 0; --i)
    {
        if(jeu.plateau.pickominos[i].etat == Etat::VISIBLE &&
           jeu.plateau.pickominos[i].appartenance == Appartenance::BROCHETTE)
        {
            return true;
        }
    }
    return false;
}

int lirePickominoMaxBrochette(const Jeu& jeu)
{
    int pickomino = NB_PICKOMINOS;
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        if(estPickominoVisible(pickomino, jeu) &&
           jeu.plateau.pickominos[pickomino].appartenance == Appartenance::BROCHETTE)
        {
            return (jeu.plateau.pickominos[pickomino].numero);
        }
        pickomino -= 1;
    }
    return 36;
}

bool estSommetPileJoueur(const int& numero, const int& joueurQuiJoue, const Jeu& jeu)
{
    if(jeu.plateau.pickominos[numero].numero ==
       jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero)
    {
        return true;
    }
    return false;
}

bool estBrochetteVide(const Jeu& jeu)
{
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        if(jeu.plateau.pickominos[i].etat == Etat::VISIBLE &&
           jeu.plateau.pickominos[i].appartenance == Appartenance::BROCHETTE)
        {
            return false;
        }
    }

    return true;
}

void remettrePickomino(const int& joueurQuiJoue, Jeu& jeu)
{
    if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
    {
        int pickominoSommetPilePerdu = convertirNumeroPickomino(
          jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero);

        int valeurPickominoSommetPilePerdu =
          jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero;

        if(valeurPickominoSommetPilePerdu < lirePickominoMaxBrochette(jeu))
        {
            remettrePickominoMaxDansLaBrochette(pickominoSommetPilePerdu, jeu);
        }
        else
        {
            remettrePickominoMaxChezLeJoueur(pickominoSommetPilePerdu, jeu);
        }

        decrementerSommetPileJoueur(joueurQuiJoue, jeu);

        if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
        {
            int nouveauPickominoSommet =
              convertirNumeroPickomino(jeu.joueurs[joueurQuiJoue]
                                         .pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile]
                                         .numero);
            changerEtatPickominoBrochette(nouveauPickominoSommet, jeu.plateau, Etat::VISIBLE);
        }
    }
}

void remettrePickominoMaxDansLaBrochette(const int& pickominoSommetPilePerdu, Jeu& jeu)
{
    int pickominoMaxBrochette = convertirNumeroPickomino(lirePickominoMaxBrochette(jeu));
    changerEtatPickominoBrochette(pickominoMaxBrochette, jeu.plateau, Etat::CACHE);
    remettrePickominoMaxChezLeJoueur(pickominoSommetPilePerdu, jeu);
}

void remettrePickominoMaxChezLeJoueur(const int& pickominoSommetPilePerdu, Jeu& jeu)
{
    changerAppartenancePickomino(pickominoSommetPilePerdu, jeu.plateau, Appartenance::BROCHETTE);
}

void prendrePickomino(const int& numero, const int& joueurQuiJoue, Jeu& jeu)
{
    int pickominoSommetPile = convertirNumeroPickomino(
      jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero);

    if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
    {
        changerEtatPickominoBrochette(pickominoSommetPile, jeu.plateau, Etat::CACHE);
    }

    incrementerSommetPileJoueur(joueurQuiJoue, jeu);
    jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile] =
      jeu.plateau.pickominos[numero];
    changerAppartenancePickomino(numero, jeu.plateau, Appartenance::JOUEUR);
}

void prendrePickominoInferieur(const int& numero, const int& joueurQuiJoue, Jeu& jeu)
{
    for(int i = numero; i >= 0; --i)
    {
        if(estPickominoVisible(i, jeu) &&
           jeu.plateau.pickominos[i].appartenance == Appartenance::BROCHETTE)
        {
#ifdef DEBUG_PLATEAU
            std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
            std::cout << "numero = " << jeu.plateau.pickominos[i].numero << std::endl;
#endif
            prendrePickomino(i, joueurQuiJoue, jeu);
            break;
        }
    }
}

void becqueter(const int& numero, const int& joueurQuiJoue, Jeu& jeu)
{
    for(int i = 0; i < jeu.nbJoueurs; i++)
    {
        if(jeu.joueurs[i].nom != jeu.joueurs[joueurQuiJoue].nom &&
           jeu.joueurs[i].pilePickominos[jeu.joueurs[i].sommetPile].numero ==
             jeu.plateau.pickominos[numero].numero)
        {
            decrementerSommetPileJoueur(i, jeu);
            if(jeu.joueurs[i].sommetPile > 0)
            {
                int pickominoSommetPile = convertirNumeroPickomino(
                  jeu.joueurs[i].pilePickominos[jeu.joueurs[i].sommetPile].numero);

                changerEtatPickominoBrochette(pickominoSommetPile, jeu.plateau, Etat::VISIBLE);
            }
            break;
        }
    }
}

void changerAppartenancePickomino(const int& numero, Plateau& plateau, Appartenance appartenance)
{
    plateau.pickominos[numero].appartenance = appartenance;
}

void changerEtatPickominoBrochette(const int& numero, Plateau& plateau, Etat etat)
{
    plateau.pickominos[numero].etat = etat;
}

void incrementerSommetPileJoueur(const int& joueurConcerne, Jeu& jeu)
{
    jeu.joueurs[joueurConcerne].sommetPile += 1;
}

void decrementerSommetPileJoueur(const int& joueurConcerne, Jeu& jeu)
{
    jeu.joueurs[joueurConcerne].sommetPile -= 1;
}

int comptageVers(const int& joueur, const Jeu& jeu) //, const Jeu& jeu
{
    int totalVers = 0;

    for(int i = 0; i < jeu.joueurs[joueur].sommetPile; i++)
    {
        totalVers += jeu.joueurs[joueur].pilePickominos[i].nbVers;
    }

    return totalVers;
}