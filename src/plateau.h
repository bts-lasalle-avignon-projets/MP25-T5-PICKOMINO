#ifndef PLATEAU_H
#define PLATEAU_H

#define NB_DES      8
#define NB_FACE_DES 6
#define FACE_VER    6

#define NB_PICKOMINO 16

struct Plateau
{
    int nbDes;
    int des[NB_DES];
    int desRetenus[NB_DES];
};

void intialiserPlateau(Plateau& plateau);
void lancerDes(int des[NB_DES], int nbDes);

#endif