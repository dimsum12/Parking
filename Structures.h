/*************************************************************************
                           Structures.h  -  description
                             -------------------
    début                : Jeudi 13 mars 2014
    copyright            : (C) 2014 par Vadim Caen et Quentin Dupont
    e-mail               : quentin.dupont@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Structures> (fichier Structures.h) -----------------

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

//------------------------------------------------------------------------
// Rôle du module <Structures>
// TODO
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

#include <time.h>

//////////////////////////////////////////////////////////////////  PUBLIC
//------------------------------------------ Structures mémoires partagées

struct etat_parking{
	int typeUsager_Parking; 	//enum TypeUsager
	int numeroVoiture;
	time_t heureArrivee;

};

// Memoire partagee de requetes contenant un tableau de 3 requetes_contenu
struct requetes_contenu{
	int barriere; 				//enum TypeBarriere
	int typeUsager_Requetes; 	//enum TypeUsager
	time_t heureDepotRequete;
};

struct requetes{
	requetes_contenu tab_req [3];
};



#endif /* STRUCTURES_H_ */
