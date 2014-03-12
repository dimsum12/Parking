/*
 * Semaphore.h
 *
 *  Created on: 13 mars 2014
 *      Author: qdupont
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

void detruire_sem(int sem);

void changer_sem(int sem, int val);

int creer_sem(int nbSemElem, int mode);

void P(int sem);

void V(int sem);


#endif /* SEMAPHORE_H_ */
