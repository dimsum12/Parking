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
#include "Outils.h"

static int s_voiture;

void Sortie(){

	unsigned int num_place = 0;
    s_voiture = open(pathPipeSortie, O_RDONLY);

    for(;;){
    	read(s_voiture,&num_place,sizeof(num_place));
    	SortirVoiture(num_place);
    }

}
