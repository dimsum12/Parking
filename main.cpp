#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <time.h>

#include "Outils.h"
#include "Clavier.h"
#include "Entree.h"
#include "Heure.h"

#include "Structures.h"

#define DROITS 0660


static int Id_mem_EtatParking;
static int Id_mem_NbPlaces;
static int Id_mem_Requetes;
static etat_parking * p_EtatParking;
static int * p_nbPlaces;
static requetes * p_Requetes;


int main() {
	InitialiserApplication(XTERM);
	//sleep(10);
	pid_t noClavier, noEntree;
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
        Afficher(MESSAGE, "Test");
		waitpid(noClavier, NULL, 0);
		TerminerApplication();
		exit(0);

	}
    return 0;
}

void Initialisation (){

	// -------------------- Memoire Partagee ------------------- //
	// ---------------------- Etat Parking --------------------- //

	// init Etat Parking
	Id_mem_EtatParking = shmget(IPC_PRIVATE,sizeof(etat_parking),IPC_CREAT | DROITS);

	// Attachement, on recupere l'adresse d'attachement (par un pointeur)
	p_EtatParking = (etat_parking*) shmat(Id_mem_EtatParking,NULL,0);

	// ------------------------ nbPlaces ----------------------- //

	Id_mem_NbPlaces = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | DROITS);
	p_nbPlaces = (int*) shmat(Id_mem_NbPlaces,NULL,0);

	// ------------------------ Requetes ----------------------- //

	Id_mem_Requetes = shmget(IPC_PRIVATE,sizeof(requetes),IPC_CREAT | DROITS);
	p_Requetes = (requetes*) shmat(Id_mem_EtatParking,NULL,0);

	// ------------------- Fin Memoire Partagee -----------------//

}

void Destruction (){

	// -------------------- Memoire Partagee ------------------- //

	// Suppression Etat Parking
	shmctl(Id_mem_EtatParking,IPC_RMID,0);
	// Detachement
	shmdt(p_EtatParking);


}

