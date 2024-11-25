#include "joueur.h"

void initialiserJoueur(const std::string nomJoueur, Joueur& joueur)
{
    joueur.nom        = nomJoueur;
    joueur.sommetPile = 0;
}

int desRetenueJoueur(int des[NB_DES], Plateau plateau){
    int nombreDesMeme = estDesDoublon(des);
        for(int i = 0; i < nombreDesMeme; i++){    
            plateau.desRetenus[i] = demandeDesARetenir();
        }
    return plateau.desRetenus[NB_DES];
}

bool BloquerDesRetenue(Plateau plateau){
    for(int i = 0; i < NB_DES; i++){
        if(plateau.desRetenus[i] == demandeDesARetenir()){
            return true;
        }
    }
    return false;
}

int calulerValeurTotalDesObtenue(){
    //int valeurDes = choisirDesARetenir();
}