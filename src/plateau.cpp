#include "plateau.h"
#include <cstdlib>
#include <ctime>

#define NB_PICKOMINO         16

int faceDes[NB_FACE_DES]{ 1, 2, 3, 4, 5, 6 };
int desRetenu[NB_DES];

void lanceeDes(int aleatoireDes[]) {
    srand(time(NULL));
    for(int i = 0; i < NB_DES; i++)
    {
        aleatoireDes[i] = rand() % NB_FACE_DES + 1;
    }
}