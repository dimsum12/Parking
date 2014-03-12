/*
 * Entree.cpp
 *
 *  Created on: 12 mars 2014
 *      Author: vcaen
 */


#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "Entree.h"
#include "SharedPipe.h"
#include "Outils.h"

static int pipeArrivee;
static int typeBarriere;
void Entree()
{   

    typeBarriere = 0;
    //Initialisation
    pipeArrivee = open(pathPipeArrivee,  O_RDONLY);

    //for(;;)
    
    	read(pipeArrivee, &typeBarriere, sizeof(typeBarriere));
    	char temp[64];
    	sprintf(temp, "%d", typeBarriere);
    	Afficher(MESSAGE, "test");
    
}

void Destruction_Entree()
{
    close(pipeArrivee);
    exit(0);
}


