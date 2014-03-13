/*
 * Sortie.cpp
 *
 *  Created on: 13 mars 2014
 *      Author: qdupont
 */
#include <fcntl.h>

#include "Sortie.h"
#include "SharedPipe.h"

static int s_voiture;

void Sortie(){

    s_voiture = open(pathPipeSortie, O_NONBLOCK | O_RDONLY);

}
