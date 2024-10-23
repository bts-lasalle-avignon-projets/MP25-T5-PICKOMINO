#include "vue.h"
#include "plateau.h"
#include <iostream>

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
