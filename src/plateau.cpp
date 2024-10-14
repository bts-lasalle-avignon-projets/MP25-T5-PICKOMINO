#include "plateau.h"

#define NB_DES 8
#define NB_FACE_DES 6
#define NB_PICKOMINO 16
#define VALEUR_PICKOMINO_MIN 21
#define VALEUR_PICKOMINO_MAX NB_PICKOMINO + VALEUR_PICKOMINO_MIN -1

int faceDes[6] {1, 2, 3, 4, 5, 6};
int desRetenu[8];