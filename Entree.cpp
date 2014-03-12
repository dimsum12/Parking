/*
 * Entree.cpp
 *
 *  Created on: 12 mars 2014
 *      Author: vcaen
 */


#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "Entree.h"
#include "SharedPipe.h"
#include "Outils.h"

static int pipeArrivee;

void Entree()
{   

    int *typeBarriere;
    //Initialisation
    pipeArrivee = open(pathPipeArrivee, O_NONBLOCK | O_RDONLY);

    for(;;)
    {
    	read()
    }


}

void Destruction_Entree()
{
    close(pipeArrivee);
    exit(0);
}


