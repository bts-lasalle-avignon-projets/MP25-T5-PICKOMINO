#include "plateau.h"

#define NB_DES 8
#define NB_FACE_DES 6
#define NB_PICKOMINO 16
#define VALEUR_PICKOMINO_MIN 21
#define VALEUR_PICKOMINO_MAX NB_PICKOMINO + VALEUR_PICKOMINO_MIN -1
#define NB_JOUEUR_MIN 2
#define NB_JOUEUR_MAX 7

int faceDes[NB_FACE_DES] {1, 2, 3, 4, 5, 6};
int desRetenu[NB_DES];
