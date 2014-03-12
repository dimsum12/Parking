#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "Clavier.h"
#include "Menu.h"
#include "Outils.h"
#include "SharedPipe.h"
 
static int sortie_voiture;
static int arrivee_voiture;
        

void Clavier() {

    	
        // Initialisation
        //pathPipeArrivee = "./arrivee_voiture"; 
        //pathPipeSortie  = "./sortie_voiture"; 
        mkfifo(pathPipeArrivee , S_IWUSR);
        mkfifo(pathPipeSortie , S_IWUSR);
        
        arrivee_voiture = open(pathPipeArrivee, O_NONBLOCK | O_WRONLY);
        sortie_voiture = open(pathPipeSortie, O_NONBLOCK | O_WRONLY);
	for(;;)
	{
        // Moteur
		Menu();
	}
        

}

void Commande(char code, unsigned int valeur)
{
	switch (code){
		case 'Q' :
            Destruction();
            exit(0);
		    break;
		case 'P' :
			Arrivee(AUTRE, valeur);
			break;
	}
}

void Arrivee(int type, int valeur)
{
    char buff[T_BUFF_PIPE];
    sprintf(buff,"%d,%d",type,valeur);
    write(arrivee_voiture, buff, T_BUFF_PIPE);
}

void Destruction()
{
    unlink(pathPipeArrivee);
    unlink(pathPipeSortie);
}
