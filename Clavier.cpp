#include "Menu.h"

void Clavier() {
	for(;;)
	{
		Menu();
	}
}

void Commande(char code, unsigned int valeur){
	switch (code){
		case 'Q' : exit(0);
		break;
	}
}
