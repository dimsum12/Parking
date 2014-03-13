/*
 * Semaphore.cpp
 *
 *  Created on: 13 mars 2014
 *      Author: qdupont
 */

#include "Semaphore.h"
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>

#define CREER 0
#define UTILISER 1

void detruire_sem(int sem) {
        semctl(sem, 0, IPC_RMID, 0);
};
void changer_sem(int sem, int val) {
        struct sembuf sb[1];
        sb[0].sem_num = 0;
        sb[0].sem_op = val;
        sb[0].sem_flg = 0;
        semop(sem, sb, 1);
}
int creer_sem(int nbSemElem, int mode) {
        int sem;
        if (mode == CREER) {
                sem = semget(IPC_PRIVATE, nbSemElem, IPC_CREAT | IPC_EXCL  | 0660);
                semctl(sem, 0, SETVAL, 1);
        }
        else if (mode == UTILISER) {
                sem = semget(IPC_PRIVATE, nbSemElem, 0666);
        }
        return sem;
}
void P(int sem) {
        changer_sem(sem, -1);
}
void V(int sem) {
        changer_sem(sem, 1);
}



