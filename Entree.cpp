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
static char msgPipe[T_BUFF_PIPE];
void Entree()
{   

    //Initialisation
    pipeArrivee = open(pathPipeArrivee,  O_RDONLY);
    char temp[T_BUFF_PIPE * 2];

    for(;;)
    {
    	Afficher(MESSAGE, "test avant");
    	read(pipeArrivee, msgPipe, T_BUFF_PIPE);
    	sprintf(temp, "test apres : %s", msgPipe);
    	Afficher(MESSAGE, temp);

    }
}

void Destruction_Entree()
{
    close(pipeArrivee);
    exit(0);
}


