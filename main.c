#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include "readerwriter.h"

int main()
{
    //variables
    struct _rwlock_t *lock = malloc(sizeof(struct _rwlock_t));
    char rw;
    FILE *file;
    int error;
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 1, 1);

    //open inputfile
    file = fopen("scenarios.txt", "r");

    //initialize lock
    rwlock_init(lock);

    //for threads
    pthread_t thread;

    if (file)
    {
        //scan input file
        printf("Scenario Starts:\n");
        while (fscanf(file, "%c", &rw) != EOF)
        {

            if (rw == 'r')
            {

                //if read create a thread to run the readThread
                error = pthread_create(&thread, NULL, (void *)readThread, (void *)&lock);
                printf("Create reader\n");
                if (error != 0)
                {
                    printf("Can't create thread.\n");
                    return 1;
                }
            }

            else if (rw == 'w')
            {

                //if write create a thread to run the writeThread
                error = pthread_create(&thread, NULL, (void *)writeThread, (void *)&lock);
                printf("Create writer\n");
                if (error != 0)
                {
                    printf("Can't create thread.\n");
                    return 1;
                }
            }
        }
    }

    //close file
    fclose(file);

    //exit threads
    pthread_exit(NULL);

    return 0;
}