#include "readerwriter.h"

//Initialize lock
void rwlock_init(rwlock_t *lock) {
    lock->readers = 0;
    sem_init(&lock->mutex, 0, 1);
    sem_init(&lock->mutex2, 0, 1);
    sem_init(&lock->wrt, 0, 1);
}

//Acquire writelock
void wait_writelock(rwlock_t *lock) {
    sem_wait(&lock->mutex);
    sem_wait(&lock->wrt);
}

//Release writelock
void post_writelock(rwlock_t *lock) {
    sem_post(&lock->wrt);
    sem_post(&lock->mutex);
}

//Acquire readlock
void wait_readlock(rwlock_t *lock) {
    sem_wait(&lock->mutex);
    sem_wait(&lock->mutex2);
    lock->readers++;
    if (lock->readers == 1) {
        sem_wait(&lock->wrt); // first reader acquires writelock
    }
    sem_post(&lock->mutex2);
    sem_post(&lock->mutex);

}

//Release readlock
void post_readlock(rwlock_t *lock) {
    sem_wait(&lock->mutex2);
    lock->readers--;
    if (lock->readers == 0) {
        sem_post(&lock->wrt); // last reader releases writelock
    }
    sem_post(&lock->mutex2);
}