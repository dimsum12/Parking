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
// Mode d'emploi :
//    <sem>    : valeur entière correspondant à l'Id du sémaphore obtenu lors de sa création
//    - supprime le sémaphore ayant l'Id correspondant à <sem>
//
// Contrat :
//    - on rentre un Id de sémaphore existant
//


void changer_sem(int sem, int val);
// Mode d'emploi :
//    <sem>    : valeur entière correspondant à l'Id du sémaphore obtenu lors de sa création
//    <val>    : operation du sémaphore
//     *  1 : pour l'operation V, incrementation
//     * -1 : pour l'operation P, décrementation
//    - opère un changement sur sémaphore ayant l'Id correspondant à <sem>. Le changement correspondant à <val>
//
// Contrat :
//    - on rentre un Id de sémaphore existant dans <sem>
//    - on rentre une opération valide : -1,0,1
//


int creer_sem(int nbSemElem, int mode);
// Mode d'emploi : TODO
//

void P(int sem);
// Mode d'emploi : TODO
//

void V(int sem);
// Mode d'emploi : TODO
//

#endif /* SEMAPHORE_H_ */
