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
const int Id_mem_EtatParking;
const int Id_mem_NbPlaces;
const int Id_mem_Requetes;
const etat_parking * p_EtatParking;
const int * p_nbPlaces;
const requetes * p_Requetes;

// Sémaphores
const int Id_sem_Requetes;
const int Id_sem_EtatParking;
const int Id_sem_nbPlaces;

// PID
const pid_t noClavier, noEntreeABP, noEntreePBP, noEntreeGB, noHeure;

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
