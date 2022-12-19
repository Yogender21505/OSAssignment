#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

pthread_t philosopher[5];
pthread_mutex_t Forks[5];
void * func(void * i);

int main(){
    int i,k;
    void *msg;
    for(i=1;i<=5;i++){
        pthread_mutex_init(&Forks[i],NULL); // Initialized the mutex for thread
        pthread_create(&philosopher[i],NULL,func,(void*)&i); // Create pthread for Philospher
        sleep(2);
        pthread_join(philosopher[i],&msg); // Joining pthread one by one 
    }

    return 0;
}
void * func(void * i){
    // printf("\nPhilosopher %d is thinking ",n);
    //Take Fork
    int n=*(int *)i;
    pthread_mutex_lock(&Forks[n]);          // when philosopher 5 is eating he takes fork 1 and fork 5
    pthread_mutex_lock(&Forks[(n+1)%5]);
    //Eating
    printf("\nPhilosopher %d is eating ",n);

    sleep(3);
    //Putting Fork
    pthread_mutex_unlock(&Forks[n]);
    pthread_mutex_unlock(&Forks[(n+1)%5]);

    //Finished Eating
    printf("\nPhilosopher %d Finished eating ",n);
}