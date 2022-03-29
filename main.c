#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "readerwriter.h"

//Initialize lock and threads
rwlock_t lock;
pthread_t wThreads[15], rThreads[15]; //max 15 threads

//Declare functions
void* readThread (void* arg);
void* writeThread (void* arg);
void reading_writing();

int main()
{
    //variables
    FILE *file;
    int error;
    char buff[15];
    int scen_count = 0;
    int read_count = 0;
    int write_count = 0;
    int iter = 0;
    rwlock_init(&lock);

    //open inputfile
    file = fopen("scenarios.txt", "r");

    if (file)
    {
        //scan input file
        printf("Scenario Starts:\n");
        //while (fscanf(file, "%c", &rw) != EOF)
        while (fgets(buff, 15, file))
        {

            scen_count++;
            while(buff[iter] != EOF)
            {
                if (buff[iter] == 'r')
                {
                    //if read create a thread to run the readThread
                    error = pthread_create(&rThreads[read_count], NULL, (void *)readThread, (void *)&lock);
                    printf("Create reader\n");
                    read_count++;
                    if (error != 0)
                    {
                        printf("Can't create thread.\n");
                        return 1;
                    }
                }

                else if (buff[iter] == 'w')
                {
                    //if write create a thread to run the writeThread
                    error = pthread_create(&wThreads[write_count], NULL, (void *)writeThread, (void *)&lock);
                    printf("Create writer\n");
                    write_count++;
                    if (error != 0)
                    {
                        printf("Can't create thread.\n");
                        return 1;
                    }
                }
                iter++;
            }

            //Join all threads once all tasks are completed
            for (iter = 0; iter < read_count; iter++)
            {
                pthread_join(rThreads[iter], NULL);
            }

            for (iter = 0; iter < write_count; iter++)
            {
                pthread_join(wThreads[iter], NULL);
            }
        }
    }
    else {
        printf("Error opening file.\n");
        return 1;
    }

    //close file
    fclose(file);

    //exit threads
    //pthread_exit(NULL);
    return 0;
}


void* readThread (void* arg){
    wait_readlock(&lock);

    /*Reading here*/
    printf("Reader is in... reading\n");
    reading_writing();
    printf("Finished reading.\n");

    post_readlock(&lock);

    return NULL;
    
}

void* writeThread (void* arg){
    wait_writelock(&lock);
        
    /*Writing here*/
    printf("Writer is in... writing\n");
    reading_writing();
    printf("Finished writing.\n");
    
    post_writelock(&lock); //

    return NULL;
}

//"Reading" and "Writing" time waster
void reading_writing(){     
    int x = 0, i, j, T;
    T = rand() % 10000;
    for(i = 0; i < T; i++){
        for(j = 0; j < T; j++){
            x = i * j;
        }  
    }   
}

