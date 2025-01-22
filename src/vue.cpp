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
        cout << "Nombre de joueurs (entre " << NB_JOUEURS_MIN << " et " << NB_JOUEURS_MAX << ") ? ";
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

int demanderDesARetenir()
{
    // Saisie valide : 1, 2, 3, 4, 5 ou V, v

    char faceARetenir       = '\0';
    int  valeurFaceARetenir = 0;
    bool saisieInvalide     = true;

    do
    {
        cout << "Face dé à retenir (1, 2, 3, 4, 5 ou V, v) : ";
        cin >> faceARetenir;
        cout << endl;
        if((faceARetenir >= '1' && faceARetenir <= '5') ||
           (faceARetenir == 'V' || faceARetenir == 'v'))
        {
            saisieInvalide = false;
        }
        else
        {
            cout << "Saisie invalide !" << std::endl;
            saisieInvalide = true;
        }
    } while(saisieInvalide);

    if(faceARetenir >= '1' && faceARetenir <= '5')
    {
        valeurFaceARetenir = atoi(&faceARetenir);
    }
    else /* V pou v */
    {
        valeurFaceARetenir = FACE_VER;
    }

    return valeurFaceARetenir;
}

bool demanderRelancerDes()
{
    // Saisie valide : O, o, N, n

    char choixRelance   = '\0';
    bool saisieInvalide = true;

    do
    {
        cout << "Relancer les dés (Oo ou Nn) ? ";
        cin >> choixRelance;
        if((choixRelance == 'O' || choixRelance == 'o') ||
           (choixRelance == 'N' || choixRelance == 'n'))
        {
            saisieInvalide = false;
        }
        else
        {
            cout << "Saisie invalide !" << std::endl;
            saisieInvalide = true;
        }
    } while(saisieInvalide);

    if(choixRelance == 'O' || choixRelance == 'o')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void afficherVersion()
{
    cout << "-----------------------------------------------" << endl;
    cout << "-------------------Pickomino-------------------" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "-----------------Version " << VERSION << "------------------" << endl;
    cout << "-----------------------------------------------" << endl;
}

void afficherDes(const Plateau& plateau)
{
    positionnerCurseur(100, 100);
    cout << "Dés :    ";
    for(int i = 0; i < plateau.nbDes; i++)
    {
        if(plateau.des[i] == FACE_VER)
            cout << "V    ";
        else
            cout << plateau.des[i] << "    ";
    }
    cout << endl;
}

void afficherDesRetenus(const Plateau& plateau)
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "| Dés retenus :    ";
    for(int i = 0; i < (NB_DES - plateau.nbDes); i++)
    {
        if(plateau.desRetenus[i] == FACE_VER)
            cout << "V     ";
        else
            cout << plateau.desRetenus[i] << "     ";
    }
    cout << "\n------------------------------------------------------------------";
    cout << endl;
}

void afficherTotalDesRetenus(const Plateau& plateau)
{
    cout << "Total dés : " << plateau.totalDes << endl;
}

void afficherQuelJoueurTour(const Joueur& joueur)
{
    cout << "\nC'est le tour de " << YELLOW << joueur.nom << RESET << " !" << endl;
}

void positionnerCurseur(int x, int y)
{
    // Déplace le curseur à la position (x, y)

    std::cout << "\033[" << y << ";" << x << "H";
}