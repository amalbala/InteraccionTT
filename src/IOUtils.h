

#ifndef IOUTILS
#define IOUTILS


#include <stdlib.h>

#include "geometry.h"

using namespace std;

int loadOBJ(mesh *malla, char* filename);
int saveOBJ(mesh *malla, char* filename);

#endif
