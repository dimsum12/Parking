#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

#include "Outils.h"
#include "Clavier.h"
#include "Entree.h"
#include "Heure.h"
#include "Semaphore.h"
#include "main.h"

#include "Structures.h"

#define DROITS 0660


static int Id_mem_EtatParking;
static int Id_mem_NbPlaces;
static int Id_mem_Requetes;
static etat_parking * p_EtatParking;
static int * p_nbPlaces;
static requetes * p_Requetes;

static int Id_sem_Requetes;
static pid_t noClavier, noEntree;

int main() {
	InitialiserApplication(XTERM);
	//sleep(10);

	//ActiverHeure();

	if ( ( noClavier = fork()) == 0 )
	{
	    Clavier();
	}
	else if ( (noEntree = fork()) == 0)
	{
	    Entree();
	}
        else
	{
		// Creation du handler de destruction
//		struct sigaction action_sigusr2;
//		action_sigusr2.sa_handler = handler_Destruction();
//		action_sigusr2.sa_flags = 0;
//		sigaction(SIGUSR2, &action_sigusr2, NULL);

		Afficher(MESSAGE, "Test");
		waitpid(noClavier, NULL, 0);
		handler_Destruction();
		TerminerApplication();
		exit(0);


	}
    return 0;
}
void handler_Destruction(){
	kill(noEntree,SIGUSR2);
	//Destruction_main();
}

void Initialisation (){

	// -------------------- Memoire Partagee ------------------- //
	// ---------------------- Etat Parking --------------------- //

	// init Etat Parking
	Id_mem_EtatParking = shmget(IPC_PRIVATE,sizeof(etat_parking),IPC_CREAT | DROITS);

	// Attachement, on recupere l'adresse d'attachement (par un pointeur)
	p_EtatParking = (etat_parking*) shmat(Id_mem_EtatParking,NULL,0);

	//Detachement
	shmdt(p_EtatParking);

	// ------------------------ nbPlaces ----------------------- //

	Id_mem_NbPlaces = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | DROITS);
	p_nbPlaces = (int*) shmat(Id_mem_NbPlaces,NULL,0);
	shmdt(p_nbPlaces);

	// ------------------------ Requetes ----------------------- //

	Id_mem_Requetes = shmget(IPC_PRIVATE,sizeof(requetes),IPC_CREAT | DROITS);
	p_Requetes = (requetes*) shmat(Id_mem_EtatParking,NULL,0);
	shmdt(p_Requetes);

	// ------------------------ Sémaphore -----------------------//
	Id_sem_Requetes = creer_sem(1,0);

}

void Destruction_main (){

	// -------------------- Memoire Partagee ------------------- //
	// ---------------------- Etat Parking --------------------- //

	//shmdt(p_EtatParking);// Detachement à faire dans la tâche
	shmctl(Id_mem_EtatParking,IPC_RMID,0);// Suppression


	// ------------------------ nbPlaces ----------------------- //

	//shmdt(p_nbPlaces);// Detachement à faire dans la tâche
	shmctl(Id_mem_NbPlaces,IPC_RMID,0);

	// ------------------------ Requetes ----------------------- //

	//shmdt(p_Requetes);// Detachement à faire dans la tâche
	shmctl(Id_mem_Requetes,IPC_RMID,0);

	// ------------------- Fin Memoire Partagee -----------------//
}
