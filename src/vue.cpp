#include "vue.h"
#include "joueur.h"
#include <iostream>
#include <limits>

using namespace std;

void changerCouleurParDefaut(const int& numero)
{
    if(numero == 0)
        std::cout << "\x1b[97;40m"; // noir
    else
        std::cout << "\x1b[0m"; // Réinitialise les couleurs
}

int definirNombreJoueurs()
{
    int nombreJoueurs;

    do
    {
        cout << "Nombre de joueurs (entre " << NB_JOUEURS_MIN << " et " << NB_JOUEURS_MAX << ") ? ";
        cin >> nombreJoueurs;
        if(cin.fail())
        {
            cin.clear(); // Réinitialise l'état d'erreur
            continue;
        }
    } while(nombreJoueurs < NB_JOUEURS_MIN || nombreJoueurs > NB_JOUEURS_MAX);
    viderTampon();
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
        viderTampon();
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
        viderTampon();
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

void viderTampon()
{
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void afficherVersion()
{
    cout << "-----------------------------------------------" << endl;
    cout << "-------------------Pickomino-------------------" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "-----------------Version " << VERSION << "-----------------" << endl;
    cout << "-----------------------------------------------" << endl;
}

void afficherRegles()
{
    cout << "\n********************REGLES*********************" << endl;
    cout << "Lire le README pour avoir les règles complètes.\n" << endl;
    cout << "Voici les 4 couleurs pour différencier les pickominos : \n" << endl;
    for(int i = 0; i < NB_PICKOMINO_EXEMPLE; i++)
    {
        cout << afficherPickominoExemple(i) << endl;
    }
}

string afficherPickominoExemple(const int& numeroExemple)
{
    string description[NB_LIGNE_PICKOMINO];
    string pickomino[NB_LIGNE_PICKOMINO];
    pickomino[0]                = "╭────╮";
    pickomino[1]                = "│ 21 │";
    pickomino[2]                = "├────┤";
    pickomino[3]                = "│ 1v │";
    pickomino[4]                = "╰────╯";
    string pickominoDescription = "";
    if(numeroExemple == 0)
    {
        description[0] = "   Ceci est le pickomino classique appartenant\n";
        description[1] = "   à la brochette. Peut être gagné :\n";
        description[2] = "   Avec le bon score de dés.\n";
        description[3] = "   Indisponible si score inférieur.\n";
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
        description[1] = "   à un autre joueur.\n";
        description[2] = "   Peut être gagné :\n";
        description[3] = "   Uniquement avec le bon score de dés.\n";
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
        description[2] = "   Il peut être pris par un adversaire\n";
        description[3] = "   ou replacer sur la brochette.\n";
        description[4] = "   \n";
        for(int i = 0; i < NB_LIGNE_PICKOMINO; i++)
        {
            pickominoDescription += MAGENTA + pickomino[i] + RESET_COLOR + description[i];
        }
        return (pickominoDescription);
    }
    else
    {
        pickomino[1]   = "│    │";
        pickomino[2]   = "│    │";
        pickomino[3]   = "│    │";
        description[0] = "   Ce pickomino est indisponible (retourné).\n";
        description[1] = "   Il est verrouillé indéfiniment par le jeu.\n";
        description[2] = "   \n";
        description[3] = "   \n";
        description[4] = "   \n";
        for(int i = 0; i < NB_LIGNE_PICKOMINO; i++)
        {
            pickominoDescription += pickomino[i] + description[i];
        }
        return (pickominoDescription);
    }
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
    cout << "***********************************************\n" << endl;
    cout << "C'est le tour de " << JAUNE << jeu.joueurs[joueurQuiJoue].nom << RESET_COLOR << " !"
         << endl;
    afficherPileJoueur(joueurQuiJoue, jeu);
}

void afficherPileJoueur(const int& joueurQuiJoue, const Jeu& jeu)
{
    if(jeu.joueurs[joueurQuiJoue].sommetPile > 0)
    {
        string pileAffichage[NB_PICKOMINOS];
        int    indexSommet     = jeu.joueurs[joueurQuiJoue].sommetPile;
        int    index           = 0;
        string pickominoJoueur = "";
        cout << "Votre pile : " << endl;

        /*for(int i = 1; i <= jeu.joueurs[joueurQuiJoue].sommetPile; i++)
        {
            // cout << jeu.joueurs[joueurQuiJoue].pilePickominos[i].numero << " ";
            int numero =
              convertirNumeroPickomino(jeu.joueurs[joueurQuiJoue].pilePickominos[i].numero);
            numero2 -= 1;

            pileAffichage[i] = afficherPickominoPileJoueur(numero, joueurQuiJoue, jeu);
            pickominoJoueur += pileAffichage[i];
        }*/
        for(int i = indexSommet; i > 0; i--)
        {
            int numero =
              convertirNumeroPickomino(jeu.joueurs[joueurQuiJoue].pilePickominos[i].numero);

            pileAffichage[index] = afficherPickominoPileJoueur(numero, joueurQuiJoue, jeu);
            pickominoJoueur += pileAffichage[index];
            index += 1;
        }

        cout << pickominoJoueur << endl;
    }
}

void afficherBrochette(const int& joueurQuiJoue, const Jeu& jeu)
{
    string brochetteAffichage[NB_PICKOMINOS];
    string pickominoBrochette = "";
    cout << "Brochette : " << endl;
    for(int j = 0; j < NB_LIGNE_PICKOMINO; j++)
    {
        for(int i = 0; i < NB_PICKOMINOS; i++)
        {
            brochetteAffichage[i] = afficherPickominoBrochette(i, joueurQuiJoue, j, jeu);
            pickominoBrochette += brochetteAffichage[i];
        }
        pickominoBrochette += "\n";
    }
    cout << pickominoBrochette << endl;
}

string afficherPickominoBrochette(const int& numero,
                                  const int& joueurQuiJoue,
                                  const int& numeroLigne,
                                  const Jeu& jeu)
{
    int    nombreVerPickomino = jeu.plateau.pickominos[numero].nbVers;
    string pickomino;

    if(numeroLigne == 0)
    {
        if(jeu.plateau.pickominos[numero].etat == Etat::CACHE &&
           jeu.plateau.pickominos[numero].appartenance == Appartenance::JOUEUR)
            pickomino = afficherPickominoVide();

        else
            pickomino = "╭────╮";
    }
    else if(numeroLigne == 1)
    {
        if(jeu.plateau.pickominos[numero].etat == Etat::CACHE &&
           jeu.plateau.pickominos[numero].appartenance == Appartenance::JOUEUR)
            pickomino = pickomino = afficherPickominoVide();

        else if(jeu.plateau.pickominos[numero].etat == Etat::CACHE)
            pickomino = "│    │";

        else
            pickomino = "│ " + to_string(numero + VALEUR_PICKOMINO_MIN) + " │";
    }
    else if(numeroLigne == 2)
    {
        if(jeu.plateau.pickominos[numero].etat == Etat::CACHE &&
           jeu.plateau.pickominos[numero].appartenance == Appartenance::JOUEUR)
            pickomino = afficherPickominoVide();

        else if(jeu.plateau.pickominos[numero].etat == Etat::CACHE)
            pickomino = "│    │";

        else
            pickomino = "├────┤";
    }
    else if(numeroLigne == 3)
    {
        if(jeu.plateau.pickominos[numero].etat == Etat::CACHE &&
           jeu.plateau.pickominos[numero].appartenance == Appartenance::JOUEUR)
            pickomino = afficherPickominoVide();

        else if(jeu.plateau.pickominos[numero].etat == Etat::CACHE)
            pickomino = "│    │";

        else
            pickomino = "│ " + to_string(nombreVerPickomino) + "v │";
    }
    else
    {
        if(jeu.plateau.pickominos[numero].etat == Etat::CACHE &&
           jeu.plateau.pickominos[numero].appartenance == Appartenance::JOUEUR)
            pickomino = afficherPickominoVide();
        else
            pickomino = "╰────╯";
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

string afficherPickominoPileJoueur(const int& numero, const int& joueurQuiJoue, const Jeu& jeu)
{
    int    nombreVerPickomino = jeu.plateau.pickominos[numero].nbVers;
    string pickomino;

    /*if(numeroLigne == 0) //affichage pile sur l'horizontal
    {
        pickomino = "┌──┐";
    }
    else if(numeroLigne == 1)
    {
        pickomino = "│" + to_string(numero + VALEUR_PICKOMINO_MIN) + "│";
    }
    else if(numeroLigne == 2)
    {
        pickomino = "├──┤";
    }
    else if(numeroLigne == 3)
    {
        pickomino = "│" + to_string(nombreVerPickomino) + "v│";
    }
    else
    {
        pickomino = "└──┘";
    }*/
    // if(index < 2)
    //{
    pickomino = "┌────┬────┐\n";
    pickomino += "│ " + to_string(numero + VALEUR_PICKOMINO_MIN) + " │ " +
                 to_string(nombreVerPickomino) + "v │\n";
    pickomino += "└────┴────┘\n";
    /*}
    else if(index == 0)
    {
        pickomino = "├────┼────┤\n";
        pickomino += "│ " + to_string(numero + VALEUR_PICKOMINO_MIN) + " │ " +
                     to_string(nombreVerPickomino) + "v │\n";
        pickomino += "└────┴────┘\n";
    }
    else
    {
        pickomino = "├────┼────┤\n";
        pickomino += "│ " + to_string(numero + VALEUR_PICKOMINO_MIN) + " │ " +
                     to_string(nombreVerPickomino) + "v │\n";
        pickomino += "├────┼────┤\n";
    }*/
    if(jeu.plateau.pickominos[numero].etat == Etat::VISIBLE)
    {
        return (MAGENTA + pickomino + RESET_COLOR);
    }
    else
    {
        return (pickomino);
    }
}

string afficherPickominoVide()
{
    return ("      ");
}