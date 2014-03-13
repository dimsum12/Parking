/*************************************************************************
                           Semaphore.h  -  description
                             -------------------
    début                : Jeudi 13 mars 2014
    copyright            : (C) 2014 par Vadim Caen et Quentin Dupont
    e-mail               : quentin.dupont@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Semaphore> (fichier Semaphore.h) -----------------
#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

void detruire_sem(int sem);

void changer_sem(int sem, int val);

int creer_sem(int nbSemElem, int mode);

void P(int sem);

void V(int sem);


#endif /* SEMAPHORE_H_ */
