/*************************************************************************
                           Clavier.h  -  description
                             -------------------
    début                : Jeudi 13 mars 2014
    copyright            : (C) 2014 par Vadim Caen et Quentin Dupont
    e-mail               : quentin.dupont@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Clavier> (fichier Clavier.h) -----------------
#ifndef CLAVIER_H_
#define CLAVIER_H_

//------------------------------------------------------------------------
// Rôle du module <Clavier>
// Ce module gère les entrées utilisateurs et transmet les informations
// correspondantes.
//------------------------------------------------------------------------

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void Clavier();
// Mode d'emploi : trivial
//

void Commande(char c, unsigned int val);
// Mode d'emploi :
// TODO : Appelé par XXX de la classe XXX a chaque lecture clavier
//
//

void Arrivee(int type, int valeur);
// Mode d'emploi : TODO
//

void Destruction();
// Mode d'emploi : TODO
//


#endif /* CLAVIER_H_ */
