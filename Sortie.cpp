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
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

//-------------------------------------------------------- Include personnel

#include "Sortie.h"
#include "SharedPipe.h"
#include "Outils.h"
#include "Semaphore.h"
#include "Structures.h"

static int s_voiture;
static void handler_destruction(int noSignal);
static void handler_finGarage(int noSignal2);
static vector<pid_t> vVoituresASortir; //Contient tous les PID des voituriers en cours de sortie
requetes_contenu * premiereRequete;

extern int Id_sem_Requetes;
extern int Id_mem_EtatParking;
extern int Id_sem_Requetes;
extern int Id_sem_nbPlaces;
extern int Id_sem_place_libre_PBP;
extern int Id_sem_place_libre_ABP;
extern int Id_sem_place_libre_GB;

static struct sigaction action_sigchild;
static struct sigaction s_action_siguser2;

pid_t noVoiturier;

void Sortie(){

	//Creation du Handler de Signal SIGUSR2 de Destruction_Sortie
    s_action_siguser2.sa_handler = handler_destruction;
    s_action_siguser2.sa_flags = 0;
    sigaction(SIGUSR2, &s_action_siguser2, NULL);

	//Creation du Handler de Signal SIGCHLD pour .. TODO
    action_sigchild.sa_handler = handler_finGarage;
    action_sigchild.sa_flags = 0;
    sigaction(SIGCHLD, &action_sigchild, NULL);

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
	// Desarmement du handler_finGarage
    //action_sigchild.sa_flags = SIG_DFL;
	exit(0);
}

static void handler_finGarage(int noSignal2){
	// Reservation de la memoire partagee avec le semaphore
	P(Id_sem_Requetes);

	/* Lecture des requêtes*/
	// Attachement
	requetes *p_memRequetes = (requetes*) shmat(Id_mem_EtatParking,NULL,0);

	// Comparaisons
	bool aumoinsUneRequete = false;

	for(int i=0; i<3;i++)
	{
		if(p_memRequetes->tab_req[i].typeUsager_Requetes != AUCUN)
		{
			aumoinsUneRequete = true;

			if(p_memRequetes->tab_req[i].typeUsager_Requetes == PROF)
			{
				if(premiereRequete->typeUsager_Requetes == AUTRE)
				{
					premiereRequete = &(p_memRequetes->tab_req[i]);
				}
				else
				{
					if(DoitOnEchangerLesDeuxRequetesSiEllesSontDuMemeTypeUsager(premiereRequete,p_memRequetes->tab_req+i))
					{
						premiereRequete=&(p_memRequetes->tab_req[i]);
					}
				}
			}

			else { //Type Usager : AUTRE
				if(premiereRequete->typeUsager_Requetes == AUTRE)
				{
					if(DoitOnEchangerLesDeuxRequetesSiEllesSontDuMemeTypeUsager(premiereRequete,p_memRequetes->tab_req+i))
					{
						premiereRequete=&(p_memRequetes->tab_req[i]);
					}
				}
				// Sinon on ne remplace pas car c'est les PROFs sont prioritaires
			}
		}
	}
	// Liberation du sémaphore pour l'accès à la mémoire partagée
	V(Id_sem_Requetes);

	if (aumoinsUneRequete)
	{
		// Liberation du sémaphore correspondant à l'entrée
		if (premiereRequete->barriere == PROF_BLAISE_PASCAL)
		{
			V(Id_sem_place_libre_PBP);
		}
		else if (premiereRequete->barriere == AUTRE_BLAISE_PASCAL)
		{
			V(Id_sem_place_libre_ABP);
		}
		else if (premiereRequete->barriere == ENTREE_GASTON_BERGER)
		{
			V(Id_sem_place_libre_GB);
		}
	}
	else
	{
		P(Id_sem_nbPlaces);
	}
}

// On donne en paramètre deux pointeurs de struc requete_contenu et on compare leur date pour dire si la requete actuelle est plus vieille
bool DoitOnEchangerLesDeuxRequetesSiEllesSontDuMemeTypeUsager(requetes_contenu * premierRequeteActuelle,requetes_contenu * requeteAComparer){
	if (premierRequeteActuelle->heureDepotRequete < requeteAComparer->heureDepotRequete)
	{
		return false; // On ne doit pas échanger les requetes car celle actuelle est plus vieille
	}
	else return true;
}
