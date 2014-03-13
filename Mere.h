/*************************************************************************
                           Mere.h  -  description
                             -------------------
    début                : Jeudi 13 mars 2014
    copyright            : (C) 2014 par Vadim Caen et Quentin Dupont
    e-mail               : quentin.dupont@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Mere> (fichier Mere.h) -----------------

#ifndef MERE_H_
#define MERE_H_

//------------------------------------------------------------------------
// Rôle du module <Mere>
// TODO
//------------------------------------------------------------------------

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

#include "Structures.h"

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Variables publiques

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

// PID
pid_t noClavier, noEntreeABP, noEntreePBP, noEntreeGB, noHeure, noSortie;

//---------------------------------------------------- Fonctions publiques

int main();
// Mode d'emploi : trivial
//
void Initialisation ();
// Mode d'emploi : TODO
//
void Destruction_main();
// Mode d'emploi : TODO
//
void handler_Destruction();
// Mode d'emploi : TODO
//

#endif /* MERE_H_ */
