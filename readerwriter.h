#include <pthread.h>
#include <semaphore.h>

//Lock struct
typedef struct _rwlock_t {
    sem_t wrt;
    sem_t mutex;
    sem_t mutex2;
    int readers;
} rwlock_t;

//Declare functions
void rwlock_init(rwlock_t *lock);
void wait_readlock(rwlock_t *lock);
void post_readlock(rwlock_t *lock);
void wait_writelock(rwlock_t *lock);
void post_writelock(rwlock_t *lock);