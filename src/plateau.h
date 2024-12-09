#ifndef PLATEAU_H
#define PLATEAU_H

#define NB_DES      8
#define NB_FACE_DES 6
#define FACE_VER    6

#define NB_PICKOMINOS        16
#define VALEUR_PICKOMINO_MIN 21
#define VALEUR_PICKOMINO_MAX (NB_PICKOMINOS + VALEUR_PICKOMINO_MIN - 1)
#define PALIER_VER_PICKOMINO 4

enum Etat
{
    CACHE   = -1,
    VISIBLE = 0
};

struct Pickomino
{
    int  numero;
    int  nbVers;
    Etat etat;
};

struct Plateau
{
    Pickomino pickominos[NB_PICKOMINOS];
    int       nbDes;
    int       des[NB_DES];
    int       desRetenus[NB_DES];
    int       totalRetenue;
};

void initialiserPlateau(Plateau& plateau);
void initialiserPickominos(Pickomino pickominos[NB_PICKOMINOS]);
void lancerDes(Plateau& plateau);
bool estDejaRetenue(const Plateau& plateau, int faceDe);
bool retenirDes(Plateau& plateau, int faceDe);
int  calculerTotalDesRetenus(Plateau& plateau);

#endif