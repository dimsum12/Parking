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
#include <signal.h>

#include "Entree.h"
#include "SharedPipe.h"
#include "Outils.h"

static int pipeArrivee;
static char msgPipe[T_BUFF_PIPE];
void Entree()
{   

    //Initialisation

    //Creation du Handler de Destruction_Entree
    struct sigaction action_siguser2;
    action_siguser2.sa_handler = handler_destruction;
    action_siguser2.sa_flags = 0;
    sigaction(SIGUSR2, &action_siguser2, NULL);

    pipeArrivee = open(pathPipeArrivee,  O_RDONLY);
    char temp[T_BUFF_PIPE * 2];

    for(;;)
    {
    	Afficher(MESSAGE, "test avant");
    	read(pipeArrivee, msgPipe, T_BUFF_PIPE);
    	sprintf(temp, "test apres : %s", msgPipe);
    	Afficher(MESSAGE, temp);
    	//char * tk; // Part of the msgPipe after strtokv
		//tk = strtok(msgPipe, ",");
		GarerVoiture(PROF_BLAISE_PASCAL);

    }
}

void Destruction_Entree()
{
    close(pipeArrivee);
    exit(0);
}

void handler_destruction(int noSignal) {
	//SIGUSR 2 voiturier
	Destruction_Entree();
}


