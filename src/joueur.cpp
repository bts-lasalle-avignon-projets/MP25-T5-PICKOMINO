#include "joueur.h"

void initialiserJoueur(const std::string nomJoueur, Joueur& joueur)
{
    joueur.nom        = nomJoueur;
    joueur.sommetPile = 0;
}

bool verificationScoreDesTotal(const int& score){
    if(score >= 21 && score <= 36)
        return 0;
    return 1;
}

bool verificationPickominoInferieurVisible(const int& score, Pickomino pickominos[NB_PICKOMINOS]){
    for(int i = 0; i < NB_PICKOMINOS; i++){
        if(score-1 == pickominos[i].numero && pickominos[i].etat == VISIBLE)
            return 0;
    }
    return 1;
}