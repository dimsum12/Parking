/*
 * main.h
 *
 *  Created on: 21 févr. 2014
 *      Author: qdupont
 */

#ifndef MAIN_H_
#define MAIN_H_

int Id_mem_EtatParking;
int Id_mem_NbPlaces;
int Id_mem_Requetes;
etat_parking * p_EtatParking;
int * p_nbPlaces;
requetes * p_Requetes;

int Id_sem_Requetes;
int Id_sem_EtatParking;
int Id_sem_nbPlaces;
pid_t noClavier, noEntree, noHeure;

int main();
void Initialisation ();
void Destruction_main();
void handler_Destruction();

#endif /* MAIN_H_ */
