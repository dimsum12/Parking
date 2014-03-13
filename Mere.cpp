/*************************************************************************
                           Mere  -  description
                             -------------------
    début                : Mere
    copyright            : (C) Mere par Vadim Caen et Quentin Dupont
    e-mail               : quentin.dupont@insa-lyon.fr
 *************************************************************************/

//---------- Réalisation du module <Mere> (fichier Mere.cpp) -----

#define DROITS 0660

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

//------------------------------------------------------ Include personnel

#include "Outils.h"
#include "Clavier.h"
#include "Entree.h"
#include "Heure.h"
#include "Semaphore.h"
#include "Mere.h"
#include "SharedPipe.h"
#include "Sortie.h"
#include "Structures.h"

///////////////////////////////////////////////////////////////////  PRIVE
//-------------------------------------------------------------- Variables

// Mémoires partagées
int Id_mem_EtatParking;
int Id_mem_NbPlaces;
int Id_mem_Requetes;
etat_parking * p_EtatParking;
int * p_nbPlaces;
requetes * p_Requetes;

// Sémaphores
int Id_sem_Requetes;
int Id_sem_EtatParking;
int Id_sem_nbPlaces;
int Id_sem_place_libre_PBP;
int Id_sem_place_libre_ABP;
int Id_sem_place_libre_GB;

// PID
pid_t noClavier, noEntreeABP, noEntreePBP, noEntreeGB, noHeure, noSortie;

/////////////////////////////////////////////////////////////////// PUBLIC
//-----------------------------------------------------Fonctions publiques

int main()
{

	Initialisation();

	noHeure = ActiverHeure();

	if ( ( noClavier = fork()) == 0 )
	{
		Clavier();
	}
	else if ( (noEntreePBP = fork()) == 0)
	{
		Entree(PROF_BLAISE_PASCAL);
	}
	else if ( (noEntreeABP = fork()) == 0)
	{
		Entree(AUTRE_BLAISE_PASCAL);
	}
	else if ( (noEntreeGB = fork()) == 0)
	{
		Entree(ENTREE_GASTON_BERGER);
	}
	else if ( (noSortie = fork()) == 0)
	{
		Sortie();
	}
	else
	{
		// Creation du handler de destruction
		//		struct sigaction action_sigusr2;
		//		action_sigusr2.sa_handler = handler_Destruction();
		//		action_sigusr2.sa_flags = 0;
		//		sigaction(SIGUSR2, &action_sigusr2, NULL);

		waitpid(noClavier, NULL, 0);
		handler_Destruction();
		TerminerApplication();
		exit(0);


	}
	return 0;
}
void handler_Destruction()
{
	kill(noEntreeABP,SIGUSR2);
	kill(noEntreeGB,SIGUSR2);
	kill(noEntreePBP,SIGUSR2);
	kill(noHeure,SIGUSR2);
	kill(noSortie,SIGUSR2);
	Destruction_main();
}

void Initialisation ()
{
	//------------------------------------------------------------------- Pipes
	mkfifo(pathPipeArriveePBP , S_IWUSR | S_IRUSR );
	mkfifo(pathPipeArriveeABP , S_IWUSR | S_IRUSR );
	mkfifo(pathPipeArriveeGB ,  S_IWUSR | S_IRUSR );
	mkfifo(pathPipeSortie ,     S_IWUSR | S_IRUSR );


	///////////////////////////////////////////////////////  Memoires Partagees
	// ----------------------------------------------------------- Etat Parking
	// init Etat Parking
	Id_mem_EtatParking = shmget(IPC_PRIVATE,sizeof(etat_parking),IPC_CREAT | DROITS);

	// Attachement, on recupere l'adresse d'attachement (par un pointeur)
	p_EtatParking = (etat_parking*) shmat(Id_mem_EtatParking,NULL,0);

	//Detachement
	shmdt(p_EtatParking);

	// --------------------------------------------------------------- nbPlaces

	Id_mem_NbPlaces = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | DROITS);
	p_nbPlaces = (int*) shmat(Id_mem_NbPlaces,NULL,0);
	shmdt(p_nbPlaces);

	// --------------------------------------------------------------- Requetes

	Id_mem_Requetes = shmget(IPC_PRIVATE,sizeof(requetes),IPC_CREAT | DROITS);
	p_Requetes = (requetes*) shmat(Id_mem_EtatParking,NULL,0);
	shmdt(p_Requetes);

	///////////////////////////////////////////////////////////////// Semaphores
	Id_sem_Requetes = creer_sem(1,0);
	Id_sem_EtatParking = creer_sem(1,0);
	Id_sem_nbPlaces = creer_sem(1,0);

	Id_sem_place_libre_PBP = creer_sem(1,0);
	Id_sem_place_libre_ABP = creer_sem(1,0);
	Id_sem_place_libre_GB = creer_sem(1,0);


	//////////////////////////////////////////////////////////////////// Clavier

	InitialiserApplication(XTERM);

}

void Destruction_main ()
{
	///////////////////////////////////////////////////////////////// Semaphores
	detruire_sem(Id_sem_Requetes);
	detruire_sem(Id_sem_nbPlaces);
	detruire_sem(Id_sem_EtatParking);
	detruire_sem(Id_sem_place_libre_PBP);
	detruire_sem(Id_sem_place_libre_ABP);
	detruire_sem(Id_sem_place_libre_GB);

	///////////////////////////////////////////////////////  Memoires Partagees
	// ----------------------------------------------------------- Etat Parking

	//shmdt(p_EtatParking);// Detachement à faire dans la tâche
	shmctl(Id_mem_EtatParking,IPC_RMID,0);// Suppression


	// --------------------------------------------------------------- nbPlaces

	//shmdt(p_nbPlaces);// Detachement à faire dans la tâche
	shmctl(Id_mem_NbPlaces,IPC_RMID,0);

	// --------------------------------------------------------------- Requetes

	//shmdt(p_Requetes);// Detachement à faire dans la tâche
	shmctl(Id_mem_Requetes,IPC_RMID,0);

	///////////////////////////////////////////////////////////////////// Pipes
	unlink(pathPipeSortie);
	unlink(pathPipeArriveeGB);
	unlink(pathPipeArriveeABP);
	unlink(pathPipeArriveePBP);

}
