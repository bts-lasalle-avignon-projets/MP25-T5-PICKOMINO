#include "plateau.h"
#include "jeu.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

/*************************Initialisation du jeu*************************/
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

/**********************************Dès**********************************/
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

/******************Vérification/Lecture des pickominos******************/
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
    for(int i = 1; i < numero; i++)
    {
        if(jeu.plateau.pickominos[numero - i].etat == Etat::VISIBLE &&
           jeu.plateau.pickominos[numero - i].appartenance == Appartenance::BROCHETTE)
        {
            return true;
        }
    }
    return false;
}

int lirePickominoMaxBrochette(const Jeu& jeu)
{
    for(int i = NB_PICKOMINOS - 1; i <= 0; i--)
    {
        if(jeu.plateau.pickominos[i].etat == Etat::VISIBLE &&
           jeu.plateau.pickominos[i].appartenance == Appartenance::BROCHETTE)
        {
            return (jeu.plateau.pickominos[i].numero);
        }
    }
    return 0;
}

bool estSommetPileJoueur(const int& numero, const int& joueurQuiJoue, const Jeu& jeu)
{
    if(jeu.plateau.pickominos[numero].numero ==
       jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero)
    {
        std::cout << "MEME PICKO" << std::endl;
        return true;
    }
    std::cout << "PAS LE MEME PICKO" << std::endl;
    return false;
}

/******************************Dèclencheur******************************/
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
    std::cout << "BROCHETTE VIDE !!" << std::endl;
    return true;
}

/********************************Actions********************************/
void remisePickomino(const int& joueurQuiJoue, Jeu& jeu)
{
    if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
    {
        int numero = convertirNumeroPickomino(
          jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero);
        if(numero < lirePickominoMaxBrochette(jeu))
        {
            remisePickominoMaxDansLaBrochette(joueurQuiJoue, jeu);
        }
        else
        {
            remisePickominoMaxChezLeJoueur(joueurQuiJoue, jeu);
        }
        if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
            devientPickominoVisible(numero, jeu.plateau);
        std::cout << "PICKO PERDU" << jeu.plateau.pickominos[numero].numero << std::endl;
    }
}

void remisePickominoMaxDansLaBrochette(const int& joueurQuiJoue, Jeu& jeu)
{
    int pickominoSommetPilePerdu = convertirNumeroPickomino(
      jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero);

    devientPickominoBrochette(pickominoSommetPilePerdu, jeu.plateau);
    devientPickominoCache(pickominoSommetPilePerdu, jeu.plateau);
    decrementerSommetPileJoueur(joueurQuiJoue, jeu);

    if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
    {
        int pickominoSommetPile = convertirNumeroPickomino(
          jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero);
        devientPickominoVisible(pickominoSommetPile, jeu.plateau);
    }
}

void remisePickominoMaxChezLeJoueur(const int& joueurQuiJoue, Jeu& jeu)
{
    int pickominoSommetPilePerdu = convertirNumeroPickomino(
      jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero);

    devientPickominoBrochette(pickominoSommetPilePerdu, jeu.plateau);
    decrementerSommetPileJoueur(joueurQuiJoue, jeu);

    if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
    {
        int pickominoSommetPile = convertirNumeroPickomino(
          jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero);
        devientPickominoVisible(pickominoSommetPile, jeu.plateau);
    }
}

void prendrePickomino(const int& numero, const int& joueurQuiJoue, Jeu& jeu)
{
    int pickominoSommetPile = convertirNumeroPickomino(
      jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero);

    if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
    {
        devientPickominoCache(pickominoSommetPile, jeu.plateau);
    }

    incrementerSommetPileJoueur(joueurQuiJoue, jeu);
    jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile] =
      jeu.plateau.pickominos[numero];
    devientPickominoJoueur(numero, jeu.plateau);
}

void prendrePickominoInferieur(const int& numero, const int& joueurQuiJoue, Jeu& jeu)
{
    int numeroDecremente;
    int pickominoSommetPile = convertirNumeroPickomino(
      jeu.joueurs[joueurQuiJoue].pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile].numero);

    if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
    {
        devientPickominoCache(pickominoSommetPile, jeu.plateau);
    }

    incrementerSommetPileJoueur(joueurQuiJoue, jeu);
    for(int i = 1; i < numero; i++)
    {
        numeroDecremente = numero - i;
        if(estPickominoVisible(numeroDecremente, jeu) &&
           jeu.plateau.pickominos[numeroDecremente].appartenance == Appartenance::BROCHETTE)
        {
            prendrePickomino(numeroDecremente, joueurQuiJoue, jeu);
            std::cout << "PICKO GAGNE : " << jeu.plateau.pickominos[numeroDecremente].numero
                      << std::endl;
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

                devientPickominoVisible(pickominoSommetPile, jeu.plateau);
            }
            break;
        }
    }
}

void devientPickominoBrochette(const int& numero, Plateau& plateau)
{
    plateau.pickominos[numero].appartenance = Appartenance::BROCHETTE;
}

void devientPickominoJoueur(const int& numero, Plateau& plateau)
{
    plateau.pickominos[numero].appartenance = Appartenance::JOUEUR;
}

void devientPickominoCache(const int& numero, Plateau& plateau)
{
    plateau.pickominos[numero].etat = Etat::CACHE;
}

void devientPickominoVisible(const int& numero, Plateau& plateau)
{
    plateau.pickominos[numero].etat = Etat::VISIBLE;
}

void incrementerSommetPileJoueur(const int& joueurConcerne, Jeu& jeu)
{
    jeu.joueurs[joueurConcerne].sommetPile += 1;
}

void decrementerSommetPileJoueur(const int& joueurConcerne, Jeu& jeu)
{
    jeu.joueurs[joueurConcerne].sommetPile -= 1;
}