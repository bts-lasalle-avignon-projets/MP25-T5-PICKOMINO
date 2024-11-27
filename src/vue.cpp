#include "vue.h"
#include "joueur.h"
#include <iostream>
#include <limits>

using namespace std;

int definirNombreJoueurs()
{
    int nombreJoueurs;

    do
    {
        std::cout << "Nombre de joueurs (entre " << NB_JOUEURS_MIN << " et " << NB_JOUEURS_MAX
                  << ") ? ";
        cin >> nombreJoueurs;
        if(cin.fail())
        {
            cin.clear();                                         // Réinitialise l'état d'erreur
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore l'entrée
            continue;
        }
    } while(nombreJoueurs < NB_JOUEURS_MIN || nombreJoueurs > NB_JOUEURS_MAX);

    return nombreJoueurs;
}

void afficherDes(int des[NB_DES], int nbDes){
    cout << "Dés :    ";
    for(int i = 0; i < nbDes; i++)
    {
        if(des[i] == FACE_VER)
            cout << "V    ";
        else
            cout << des[i] << "    ";
    }
    cout << endl;
}

int demandeDesARetenir(){
    int chiffreARetenir;

    cin >> chiffreARetenir;
    int vers = atoi("V");
    if(vers){
        chiffreARetenir = FACE_VER;
        return chiffreARetenir;
    }
    else return chiffreARetenir;
}

void affichageDesRetenue(Plateau plateau){
    cout << "Dés retenue :    ";
    for(int i = 0; i < plateau.desRetenus[NB_DES]; i++)
    {
        if(plateau.desRetenus[i] == FACE_VER)
            cout << "V    ";
        else
            cout << plateau.desRetenus[i] << "    ";
    }
    cout << endl;
}
