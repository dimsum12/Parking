/*************************************************************************
                           Entree  -  description
                             -------------------
    début                : Entree
    copyright            : (C) Entree par Vadim Caen et Quentin Dupont
    e-mail               : quentin.dupont@insa-lyon.fr
 *************************************************************************/

//---------- Réalisation du module <Entree> (fichier Entree.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <vector>

//------------------------------------------------------ Include personnel

#include "Entree.h"
#include "SharedPipe.h"
#include "Outils.h"
#include "Structures.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

static int pipeArriveePBP,pipeArriveeABP,pipeArriveeGB;
static char msgPipe[T_BUFF_PIPE];
static void handler_destruction(int noSignal);
static vector<pid_t> vVoituresAGarer;

/////////////////////////////////////////////////////////////////// PUBLIC
//---------------------------------------------------- Variables publiques

extern int Id_mem_EtatParking;

//---------------------------------------------------- Fonctions publiques
void Entree(TypeBarriere barriere)
{   
	//Afficher(MESSAGE, "DEBUG 1");
	//Initialisation

	// Attachement sur la mémoire de l'état parking
	requetes *p_memReq = (requetes*) shmat(Id_mem_EtatParking,NULL,0);

	//Creation du Handler de Destruction_Entree
	struct sigaction action_siguser2;
	action_siguser2.sa_handler = handler_destruction;
	action_siguser2.sa_flags = 0;
	sigaction(SIGUSR2, &action_siguser2, NULL);
	//Afficher(MESSAGE, "DEBUG 2");

	pipeArriveePBP = open(pathPipeArriveePBP,  O_RDONLY); //Afficher(MESSAGE, "DEBUG 3");
	pipeArriveeABP = open(pathPipeArriveeABP,  O_RDONLY); Afficher(MESSAGE, "DEBUG 7");
	pipeArriveeGB  = open(pathPipeArriveeGB,   O_RDONLY); Afficher(MESSAGE, "DEBUG 8");

	char temp[T_BUFF_PIPE * 2];

	for(;;)
	{

		if(barriere == PROF_BLAISE_PASCAL)
		{
			// TODO : Les requetes de cette porte se feront sur la première structure du tableau de structure
			p_memReq->tab_req[0].barriere = PROF_BLAISE_PASCAL;

			Afficher(MESSAGE, "PBP");
			read(pipeArriveePBP, msgPipe, T_BUFF_PIPE);
			Effacer(MESSAGE);
			sprintf(temp, "test ap: %s", msgPipe);
			Afficher(MESSAGE, temp);
			vVoituresAGarer.push_back(GarerVoiture(PROF_BLAISE_PASCAL));
		}
		else if(barriere == AUTRE_BLAISE_PASCAL)
		{
			p_memReq->tab_req[1].barriere = AUTRE_BLAISE_PASCAL;

			Afficher(MESSAGE, "ABP");
			read(pipeArriveeABP, msgPipe, T_BUFF_PIPE);
			Effacer(MESSAGE);
			sprintf(temp, "test ap: %s", msgPipe);
			Afficher(MESSAGE, temp);
			vVoituresAGarer.push_back(GarerVoiture(AUTRE_BLAISE_PASCAL));
		}
		else if(barriere == ENTREE_GASTON_BERGER )
		{
			p_memReq->tab_req[2].barriere = ENTREE_GASTON_BERGER;

			Afficher(MESSAGE, "GB");
			read(pipeArriveeGB, msgPipe, T_BUFF_PIPE);
			Effacer(MESSAGE);
			sprintf(temp, "test ap: %s", msgPipe);
			Afficher(MESSAGE, temp);
			vVoituresAGarer.push_back(GarerVoiture(ENTREE_GASTON_BERGER));

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

static void handler_destruction(int noSignal)
{
	//SIGUSR 2 voiturier
	// Destruction de toutes les tâches SortirVoiture en cours d'éxecution
	vector<pid_t>::iterator it ;
	for(it=vVoituresAGarer.begin();it!=vVoituresAGarer.end();it++)
	{
		if ( *(it) != -	1 )
		{
			kill(*(it),SIGUSR2);
		}
	}
	Destruction_Entree();
}


