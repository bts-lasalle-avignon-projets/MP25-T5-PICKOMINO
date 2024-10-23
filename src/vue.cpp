#include "vue.h"
#include "plateau.h"
#include "joueur.h"
#include <iostream>
#include <limits>

using namespace std;

void afficherDes(int des[NB_DES], int nbDes)
{
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