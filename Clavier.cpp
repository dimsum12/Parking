/*************************************************************************
                           Clavier  -  description
                             -------------------
    début                : Clavier
    copyright            : (C) Clavier par Vadim Caen et Quentin Dupont
    e-mail               : quentin.dupont@insa-lyon.fr
*************************************************************************/

//---------- Réalisation du module <Clavier> (fichier Clavier.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

//------------------------------------------------------ Include personnel

#include "Clavier.h"
#include "Menu.h"
#include "Outils.h"
#include "SharedPipe.h"
 
static int sortie_voiture;
static int arrivee_voiturePBP, arrivee_voitureABP, arrivee_voitureGB;
        

void Clavier() {
		Afficher(MESSAGE, "DEBUG 4");
        arrivee_voiturePBP = open(pathPipeArriveePBP,   O_WRONLY);
        arrivee_voitureABP = open(pathPipeArriveeABP,   O_WRONLY);
        arrivee_voitureGB =  open(pathPipeArriveeGB,    O_WRONLY);
        //sortie_voiture = open(pathPipeSortie, O_NONBLOCK | O_WRONLY);
        Afficher(MESSAGE, "DEBUG 5");
	for(;;)
	{
        // Moteur
		Menu();
	}
        

}

void Commande(char code, unsigned int valeur)
{
	switch (code)
	{
		case 'Q' :
            Destruction();
            exit(0);
		    break;
		case 'P' :
			Arrivee(PROF, valeur);
			break;
		case 'A' :
			Arrivee(AUTRE, valeur);
			break;
	}
}

void Arrivee(int type, int valeur)
{
    char buff[T_BUFF_PIPE];
    sprintf(buff,"%d,%d",type,valeur);



    if(type == PROF && valeur == 1)
    {
    	//Afficher(MESSAGE, buff);
    	write(arrivee_voiturePBP, buff, T_BUFF_PIPE);
    } else if((type == PROF && valeur == 2) || (type == AUTRE && valeur == 2))
    {
    	//Afficher(MESSAGE, buff);
    	write(arrivee_voitureGB, buff, T_BUFF_PIPE);
    } else if(type == AUTRE && valeur == 1)
    {
    	//Afficher(MESSAGE, buff);
    	write(arrivee_voitureABP, buff, T_BUFF_PIPE);
    }
}

void Destruction()
{

}
