#include "plateau.h"

#define NB_PICKOMINO         16
#define VALEUR_PICKOMINO_MIN 21
#define VALEUR_PICKOMINO_MAX NB_PICKOMINO + VALEUR_PICKOMINO_MIN - 1
#define NB_JOUEUR_MIN        2
#define NB_JOUEUR_MAX        7
#define PALIER_VER_PICKOMINO 4

using namespace std;

int faceDes[NB_FACE_DES]{ 1, 2, 3, 4, 5, 6 };
int desRetenu[NB_DES];

void initialisationPickomino()
{
    for(int i = 0; i < NB_PICKOMINO; i++)
    {
        pickomino[i].numero = VALEUR_PICKOMINO_MIN + i;
        if(pickomino[i].numero >= VALEUR_PICKOMINO_MAX - PALIER_VER_PICKOMINO)
            pickomino[i].nbVer = 4;
        else if(pickomino[i].numero >= VALEUR_PICKOMINO_MAX - PALIER_VER_PICKOMINO * 2)
            pickomino[i].nbVer = 3;
        else if(pickomino[i].numero >= VALEUR_PICKOMINO_MAX - PALIER_VER_PICKOMINO * 3)
            pickomino[i].nbVer = 2;
        else
            pickomino[i].nbVer = 1;
        pickomino[i].etat = true;
    }
}

void initialisationDes()
{
    for(int i = 0; i < NB_DES; i++)
    {
        des[i].valeurFace[i] = i + 1;
        des[i].retenu        = false;
    }
}

int auTourJoueur = 0;

int definirNombreJoueur()
{
    int nombreJoueur;
    while(true) // boucle infinie
    {
        cin >> nombreJoueur;
        if(cin.fail())
        {
            cin.clear();                                         // Réinitialise l'état d'erreur
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore l'entrée
            continue;
        }
        if(verifierConditionJoueurMin(nombreJoueur) && verifierConditionJoueurMax(nombreJoueur))
            break;
    }
    return nombreJoueur;
}

bool verifierConditionJoueurMin(const int& nombreJoueur)
{
    if(nombreJoueur < NB_JOUEUR_MIN)
        return false;
    return true;
}

bool verifierConditionJoueurMax(const int& nombreJoueur)
{
    if(nombreJoueur > NB_JOUEUR_MAX)
        return false;
    return true;
}
