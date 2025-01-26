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
    cout << "-----------------Version " << VERSION << "-----------------" << endl;
    cout << "-----------------------------------------------" << endl;
}

void afficherDes(const Plateau& plateau)
{
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
    cout << "Dés retenus :    ";
    for(int i = 0; i < (NB_DES - plateau.nbDes); i++)
    {
        if(plateau.desRetenus[i] == FACE_VER)
            cout << "V    ";
        else
            cout << plateau.desRetenus[i] << "    ";
    }
    cout << endl;
}

void afficherTotalDesRetenus(const Plateau& plateau)
{
    cout << "Total dés : " << plateau.totalDes << endl;
}

void afficherQuelJoueurTour(const int& joueurQuiJoue, const Jeu& jeu)
{
    cout << "C'est le tour de " << JAUNE << jeu.joueurs[joueurQuiJoue].nom << RESET_COLOR << " !"
         << endl;
    afficherPileJoueur(joueurQuiJoue, jeu);
}

void afficherPileJoueur(const int& joueurQuiJoue, const Jeu& jeu)
{
    if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
    {
        cout << "Vos pickominos : ";
        for(int i = 1; i <= jeu.joueurs[joueurQuiJoue].sommetPile; i++)
        {
            cout << jeu.joueurs[joueurQuiJoue].pilePickominos[i].numero << " ";
        }
        cout << endl;
    }
}

void afficherBrochette(const int& joueurQuiJoue, const Jeu& jeu)
{
    string brochetteAffichage[16];
    string pickominoDisponible = "";
    cout << "Brochette : " << endl;

    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        brochetteAffichage[i] = afficherPickomino(i, joueurQuiJoue, jeu);
        pickominoDisponible += brochetteAffichage[i];
    }
    cout << pickominoDisponible << endl;
}

string afficherPickomino(const int& numero, const int& joueurQuiJoue, const Jeu& jeu)
{
    int nombreVerPickomino = jeu.plateau.pickominos[numero].nbVers;

    /*string pickomino = " ____\n";
    pickomino += "| " + to_string(numero+VALEUR_PICKOMINO_MIN) + " |\n";
    pickomino += "|----|\n";
    pickomino += "| " + to_string(nombreVerPickomino) + "🪱 |\n";
    pickomino += " ‾‾‾‾";  *///Pour tout sur la même ligne c'est complex donc on le fera plus tard

    string pickomino = "___________\n";
    pickomino += "| " + to_string(numero + VALEUR_PICKOMINO_MIN) + " | " +
                 to_string(nombreVerPickomino) + "🪱 |\n";
    pickomino += "‾‾‾‾‾‾‾‾‾‾‾\n";

    if(jeu.plateau.pickominos[numero].etat == Etat::CACHE)
    {
        return (afficherPickominoCache(numero, nombreVerPickomino));
    }
    else if(jeu.plateau.pickominos[numero].appartenance == Appartenance::JOUEUR &&
            jeu.plateau.pickominos[numero].numero ==
              jeu.joueurs[joueurQuiJoue]
                .pilePickominos[jeu.joueurs[joueurQuiJoue].sommetPile]
                .numero)
    {
        return (MAGENTA + pickomino + RESET_COLOR);
    }
    else if(jeu.plateau.pickominos[numero].appartenance == Appartenance::JOUEUR)
    {
        return (ROUGE + pickomino + RESET_COLOR);
    }
    else
    {
        return (VERT + pickomino + RESET_COLOR);
    }
}

string afficherPickominoCache(const int& numero, const int& nombreVerPickomino)
{
    string resultat = "___________\n";
    resultat += "| XX | XX |\n";
    resultat += "‾‾‾‾‾‾‾‾‾‾‾\n";
    return resultat;
}