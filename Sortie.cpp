/*************************************************************************
                           Sortie  -  description
                             -------------------
    début                : Sortie
    copyright            : (C) Sortie par Vadim Caen et Quentin Dupont
    e-mail               : quentin.dupont@insa-lyon.fr
*************************************************************************/

//---------- Réalisation du module <Sortie> (fichier Sortie.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

#include <fcntl.h>

//-------------------------------------------------------- Include personnel

#include "Sortie.h"
#include "SharedPipe.h"

static int s_voiture;

void Sortie(){

    s_voiture = open(pathPipeSortie, O_NONBLOCK | O_RDONLY);

}
