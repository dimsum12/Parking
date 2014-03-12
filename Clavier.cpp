#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Clavier.h"
#include "Menu.h"
#include "SharedPipe.h"
        
static int sortie_voiture;
static int arrivee_voiture;
        

void Clavier() {
        // Initialisation
        arrivee_voiture = mkfifo(pathPipeArrivee , S_IWUSR);
        sortie_voiture = mkfifo(pathPipeSortie , S_IWUSR);
        
        open(pathPipeArrivee, O_NONBLOCK | O_WRONLY);
        open(pathPipeSortie, O_NONBLOCK | O_WRONLY);
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
	}
}

void Destruction() 
{
    unlink(pathPipeArrivee);
    unlink(pathPipeSortie);
}
