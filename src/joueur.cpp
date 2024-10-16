#include "joueur.h"

char definitionNomJoueur(){
    for (int i = 0; i < NB_JOUEUR; i++){
        joueur[i].nom[i] = "Joueur " + std::to_string(i + 1);
    }
}

void initialisationPilePickominoJoueur(){
    for (int i = 0; i < NB_JOUEUR; i++){
        for (int j = 0; j < NB_PICKOMINO; j++){
            joueur[i].pilePickomino[i][j] = 0;
        }
    } 
}