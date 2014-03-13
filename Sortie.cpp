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
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <vector>
//-------------------------------------------------------- Include personnel

#include "Sortie.h"
#include "SharedPipe.h"
#include "Outils.h"

static int s_voiture;
static void handler_destruction(int noSignal);
static vector<pid_t> vVoituresASortir; //Contient tous les PID des voituriers en cours de sortie

void Sortie(){

	//Creation du Handler de Signal SIGUSR2 de Destruction_Sortie
    struct sigaction action_siguser2;
    action_siguser2.sa_handler = handler_destruction;
    action_siguser2.sa_flags = 0;
    sigaction(SIGUSR2, &action_siguser2, NULL);


	unsigned int num_place = 0;
    s_voiture = open(pathPipeSortie, O_RDONLY);

    for(;;){
    	read(s_voiture,&num_place,sizeof(num_place));
    	vVoituresASortir.push_back(SortirVoiture(num_place));
    }

}


static void handler_destruction(int noSignal) {

	// Destruction de toutes les tâches SortirVoiture en cours d'éxecution
	vector<pid_t>::iterator it ;
	for(it=vVoituresASortir.begin();it!=vVoituresASortir.end();it++)
	{
		if ( *(it) != -	1 )
		{
			kill(*(it),SIGUSR2);
		}
	}
	exit(0);
}



