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
#include <sys/types.h>
#include <sys/shm.h>

#include "Entree.h"
#include "SharedPipe.h"
#include "Outils.h"
#include "main.h"
#include "Semaphore.h"

static int pipeArriveePBP,pipeArriveeABP,pipeArriveeGB;
static char msgPipe[T_BUFF_PIPE];
void Entree(TypeBarriere barriere)
{   

    //Initialisation

    //Creation du Handler de Destruction_Entree
    struct sigaction action_siguser2;
    action_siguser2.sa_handler = handler_destruction;
    action_siguser2.sa_flags = 0;
    sigaction(SIGUSR2, &action_siguser2, NULL);

    pipeArriveePBP = open(pathPipeArriveePBP,  O_RDONLY);
    pipeArriveeABP = open(pathPipeArriveePBP,  O_RDONLY);
    pipeArriveeGB = open(pathPipeArriveePBP,   O_RDONLY);
    char temp[T_BUFF_PIPE * 2];

    for(;;)
    {



    	if(barriere == PROF_BLAISE_PASCAL)
    	{
    		Afficher(MESSAGE, "PBP");
    		read(pipeArriveePBP, msgPipe, T_BUFF_PIPE);
    		Effacer(MESSAGE);
    		sprintf(temp, "test ap: %s", msgPipe);
    		Afficher(MESSAGE, temp);
    		GarerVoiture(PROF_BLAISE_PASCAL);
    	}
    	else if(barriere == AUTRE_BLAISE_PASCAL)
    	{
    		Afficher(MESSAGE, "ABP");
    		read(pipeArriveeABP, msgPipe, T_BUFF_PIPE);
    		Effacer(MESSAGE);
    		sprintf(temp, "test ap: %s", msgPipe);
    		Afficher(MESSAGE, temp);
    		GarerVoiture(AUTRE_BLAISE_PASCAL);
    	}
    	else if(barriere == ENTREE_GASTON_BERGER )
    	{
    		Afficher(MESSAGE, "GB");
    		read(pipeArriveeGB, msgPipe, T_BUFF_PIPE);
    		Effacer(MESSAGE);
    		sprintf(temp, "test ap: %s", msgPipe);
    		Afficher(MESSAGE, temp);
    		GarerVoiture(ENTREE_GASTON_BERGER);

    	}
    }
}

void Destruction_Entree()
{
    close(pipeArriveePBP);
    close(pipeArriveeGB);
    close(pipeArriveeABP);
    exit(0);
}

void handler_destruction(int noSignal) {
	//SIGUSR 2 voiturier
	Destruction_Entree();
}


