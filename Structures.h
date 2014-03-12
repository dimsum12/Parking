/*
 * Structures.h
 *
 *  Created on: 12 mars 2014
 *      Author: qdupont
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <time.h>

struct etat_parking{
	int typeUsager_Parking; //enum TypeUsager
	int numeroPlace;
	time_t heureArrivee = time(NULL);

};

struct requetes{
	int barriere; //enum TypeBarriere
	int typeUsager_Requetes; //enum TypeUsager
	time_t heureDepotRequete = time(NULL);

};


#endif /* STRUCTURES_H_ */
