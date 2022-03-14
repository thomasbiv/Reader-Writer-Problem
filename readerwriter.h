#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

int read_cnt = 0;
sem_t wrt;
sem_t mutex;

void* writeThread (void* arg){
    while(true){
        sem_wait(wrt);
        
        /*Writing here*/
        printf("Writer is in... writing\n");
        reading_writing();
        
        sem_post(wrt);
    }
}

void* readThread (void* arg){
    while(true) {    
        sem_wait(mutex);  
        read_cnt++;
        if (read_cnt == 1){
            sem_wait(wrt);
        }
        sem_post(mutex);

        /*Reading here*/
        printf("Reader is in... reading\n");
        reading_writing();

        sem_wait(mutex);
        read_cnt--;
        if (read_cnt == 0){
            sem_post(wrt);
            sem_post(mutex);
        }
    }
}

void reading_writing(){     
    int x = 0, T;
    T = rand() % 10000;   
    for(i = 0; i < T; i++)   
        for(j = 0; j < T; j++)    
            x = i * j;  
}