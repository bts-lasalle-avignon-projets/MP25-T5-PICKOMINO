#include "plateau.h"
#include "jeu.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

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

void initialiserPickominos(Plateau plateau)
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

bool estScoreValide(const int& score)
{
    if(score >= VALEUR_PICKOMINO_MIN && score <= VALEUR_PICKOMINO_MAX)
        return true;
    return false;
}

bool verifierSiVersRetenu(const Plateau& plateau)
{
    for(int i = 0; i < NB_DES; i++)
    {
        if(plateau.desRetenus[i] == FACE_VER)
        {
            return true;
        }
    }
    return false;
}

bool estPickominoVisible(const int& numero, const Jeu& jeu)
{
    return (jeu.plateau.pickominos[numero - VALEUR_PICKOMINO_MIN].etat == VISIBLE);
}

bool estPickominoInferieurVisible(const int& numero, const Jeu& jeu)
{
    for(int i = 0; i < numero - VALEUR_PICKOMINO_MIN; i++)
    {
        if(jeu.plateau.pickominos[numero - i].etat == VISIBLE &&
           jeu.plateau.pickominos[numero - i].appartenance == BROCHETTE)
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

void remisePickomino(const int joueurQuiJoue, Jeu& jeu)
{
    if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
    {
        jeu.joueurs[joueurQuiJoue].sommetPile -= 1;
        if(jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero <
           estPickominoMaxBrochette(jeu))
        {
            jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].etat =
              CACHE;
            jeu.joueurs[joueurQuiJoue]
              .pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile]
              .appartenance = BROCHETTE;
        }
        if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
            jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].etat =
              VISIBLE;
    }
}

int estPickominoMaxBrochette(Jeu& jeu)
{
    for(int i = VALEUR_PICKOMINO_MAX; i < VALEUR_PICKOMINO_MIN; i--)
    {
        if(jeu.plateau.pickominos[i].etat == VISIBLE &&
           jeu.plateau.pickominos[i].appartenance == BROCHETTE)
        {
            return (jeu.plateau.pickominos[i].numero);
        }
    }
    return 0;
}

bool estBrochetteVide(Jeu& jeu)
{
    for(int i = VALEUR_PICKOMINO_MIN; i < VALEUR_PICKOMINO_MAX; i++)
    {
        if(jeu.plateau.pickominos[i].etat == VISIBLE &&
           jeu.plateau.pickominos[i].appartenance == BROCHETTE)
        {
            return false;
        }
    }
    return true;
}