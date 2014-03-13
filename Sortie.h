/*************************************************************************
                           Sortie.h  -  description
                             -------------------
    début                : Jeudi 13 mars 2014
    copyright            : (C) 2014 par Vadim Caen et Quentin Dupont
    e-mail               : quentin.dupont@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Sortie> (fichier Sortie.h) -----------------

#ifndef SORTIE_H_
#define SORTIE_H_

//------------------------------------------------------------------------
// Rôle du module <Sortie>
// TODO
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

#include "Structures.h"

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Variables publiques


//---------------------------------------------------- Fonctions publiques

void Sortie();
// Mode d'emploi : TODO
//
bool DoitOnEchangerLesDeuxRequetesSiEllesSontDuMemeTypeUsager(requetes_contenu * premierRequeteActuelle,requetes_contenu * requeteAComparer);

#endif /* SORTIE_H_ */
