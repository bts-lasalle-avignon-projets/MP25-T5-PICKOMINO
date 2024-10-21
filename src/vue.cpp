#include "vue.h"
#include "plateau.h"
#include <iostream>

void affichageDesAleatoires(int aleatoireDes[]){
    cout << "   Dés obtenue    :    ";
    for (int i = 0; i < NB_DES; i++)
    {
        if(aleatoireDes[i] == 6)
            cout << "V    ";
        else
            cout << aleatoireDes[i] << "    ";
    }
    cout << endl;
}
