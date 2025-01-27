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
    cout << "_________________________________________________" << endl;
    cout << "|--------------|    Pickomino    |--------------|" << endl;
    cout << "|--------------|                 |--------------|" << endl;
    cout << "|--------------|   Version " << VERSION << "   |--------------|" << endl;
    cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n" << endl;
}

void afficherRegles()
{
    cout << "\n********************REGLES*********************" << endl;
    cout << "Lire le README pour avoir les règles complètes.\n" << endl;
    cout << "Voici 4 couleurs pour différiencier les pickominos : \n" << endl;
    for(int i = 0; i < NB_PICKOMINO_EXEMPLE; i++)
    {
        cout << afficherPickominoExemple(i) << endl;
    }
    cout << "***********************************************\n" << endl;
}

string afficherPickominoExemple(const int& numeroExemple)
{
    string description[NB_LIGNE_PICKOMINO];
    string pickomino[NB_LIGNE_PICKOMINO];
    pickomino[0]                = " ____ ";
    pickomino[1]                = "| 21 |";
    pickomino[2]                = "|————|";
    pickomino[3]                = "| 1v |";
    pickomino[4]                = " ‾‾‾‾ ";
    string pickominoDescription = "";
    if(numeroExemple == 0)
    {
        description[0] = "   Ceci est le pickomino classic appartenant\n";
        description[1] = "   à la brochette. Peut être gagné :\n";
        description[2] = "   Avec le bon score de dè.\n";
        description[3] = "   Score inferieur si indisponible.\n";
        description[4] = "\n";
        for(int i = 0; i < NB_LIGNE_PICKOMINO; i++)
        {
            pickominoDescription += VERT + pickomino[i] + RESET_COLOR + description[i];
        }
        return (pickominoDescription);
    }
    if(numeroExemple == 1)
    {
        description[0] = "   Ceci est le pickomino appartenant\n";
        description[1] = "   à un autre joueur que vous.\n";
        description[2] = "   Peut être gagné :\n";
        description[3] = "   Uniquement avec le bon score de dès.\n";
        description[4] = "\n";
        for(int i = 0; i < NB_LIGNE_PICKOMINO; i++)
        {
            pickominoDescription += ROUGE + pickomino[i] + RESET_COLOR + description[i];
        }
        return (pickominoDescription);
    }
    if(numeroExemple == 2)
    {
        description[0] = "   Ce pickomino est votre dernier pickomino\n";
        description[1] = "   obtenu.\n";
        description[2] = "   Si resélectionné par son propriétaire,\n";
        description[3] = "   le pickomino inférieur appartenant à\n";
        description[4] = "   la brochette sera pris.\n";
        for(int i = 0; i < NB_LIGNE_PICKOMINO; i++)
        {
            pickominoDescription += MAGENTA + pickomino[i] + RESET_COLOR + description[i];
        }
        return (pickominoDescription);
    }
    else
    {
        pickomino[1]   = "| XX |";
        pickomino[3]   = "| XX |";
        description[0] = "   Ce pickomino est indisponible (Caché).\n";
        description[1] = "   Il peut être :\n";
        description[2] = "   Redisponible si est le suivant dans la pile\n";
        description[3] = "   d'un joueur et fait un tour nul.\n";
        description[4] = "   Verrouillé par le jeu indéfiniment.\n";
        for(int i = 0; i < NB_LIGNE_PICKOMINO; i++)
        {
            pickominoDescription += pickomino[i] + description[i];
        }
        return (pickominoDescription);
    }
}

void afficherDes(const Plateau& plateau)
{
    positionnerCurseur(65, 100);
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

void afficherQuelJoueurTour(const int& joueurQuiJoue, const Jeu& jeu)
{
    cout << "\nC'est le tour de " << JAUNE << jeu.joueurs[joueurQuiJoue].nom << RESET_COLOR << " !"
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
    for(int j = 0; j < NB_LIGNE_PICKOMINO; j++)
    {
        for(int i = 0; i < NB_PICKOMINOS; i++)
        {
            brochetteAffichage[i] = afficherPickomino(i, joueurQuiJoue, j, jeu);
            pickominoDisponible += brochetteAffichage[i];
        }
        pickominoDisponible += "\n";
    }
    cout << pickominoDisponible << endl;
}

string afficherPickomino(const int& numero,
                         const int& joueurQuiJoue,
                         const int& numeroLigne,
                         const Jeu& jeu)
{
    int    nombreVerPickomino = jeu.plateau.pickominos[numero].nbVers;
    string pickomino;

    if(numeroLigne == 0)
    {
        pickomino = " ____  ";
    }
    else if(numeroLigne == 1)
    {
        if(jeu.plateau.pickominos[numero].etat == Etat::CACHE)
            pickomino = "| XX | ";
        else
            pickomino = "| " + to_string(numero + VALEUR_PICKOMINO_MIN) + " | ";
    }
    else if(numeroLigne == 2)
    {
        pickomino = "|————| ";
    }
    else if(numeroLigne == 3)
    {
        if(jeu.plateau.pickominos[numero].etat == Etat::CACHE)
            pickomino = "| XX | ";
        else
            pickomino = "| " + to_string(nombreVerPickomino) + "v | ";
    }
    else
    {
        pickomino = " ‾‾‾‾  ";
    }
    /*
        string pickomino = "___________\n";
        pickomino += "| " + to_string(numero + VALEUR_PICKOMINO_MIN) + " | " +
                     to_string(nombreVerPickomino) + "🪱 |\n";
        pickomino += "‾‾‾‾‾‾‾‾‾‾‾\n";*/ //version horizontal

    if(jeu.plateau.pickominos[numero].etat == Etat::CACHE)
    {
        return (pickomino);
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

void positionnerCurseur(int x, int y)
{
    // Déplace le curseur à la position (x, y)

    std::cout << "\033[" << y << ";" << x << "H";
}