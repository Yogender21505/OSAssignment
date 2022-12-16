#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

// sem_t room;
// sem_t chopstick[5];

// #define philosopher[5]={0,1,2,3,4};
// int Forks[]={0,0,0,0,0,0};
// void * philosopher(void *);
// void eat(int);
// int main()
// {
// 	int i;
// 	pthread_t tid[5];
	
// 	// sem_init(&room,0,4);
	
// 	for(i=0;i<5;i++)
// 		Forks[i]=1;
		
// 	for(i=0;i<5;i++){
// 		a[i]=philosopher[i];
// 		pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);
// 	}
// 	for(i=0;i<5;i++)
// 		pthread_join(tid[i],NULL);
// }

// void * philosopher(void * num)
// {
// 	int phil=*(int *)num;

// 	// sem_wait(&room);
// 	// // printf("\nPhilosopher %d has entered room",phil);
// 	// sem_wait(&chopstick[phil]);
// 	// sem_wait(&chopstick[(phil+1)%5]);

// 	eat(phil);
// 	sleep(2);
// }

// void eat(int phil)
// {
// 	printf("\nPhilosopher %d is eating",phil);
// }


#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>


void *func(int n);

pthread_t philosopher[5];
pthread_mutex_t Forks[5];

int main(){
    int i,k;
    void *msg;

    for(i=1;i<=5;i++){
        k=pthread_mutex_init(&Forks[i],NULL); // Initialized the mutex for thread
    }
    for(i=1;i<=5;i++){
        k=pthread_create(&philosopher[i],NULL,(void *)func,(int *)i); // Create pthread for Philospher
    }
    for(i=1;i<=5;i++){
        k=pthread_join(philosopher[i],&msg); // Joining pthread one by one 
    }
    // for(i=1;i<=5;i++)
    //     k=pthread_mutex_destroy(&Forks[i]); // destroying mutex due to 
    
    return 0;
}
void *func(int n){
    // printf("\nPhilosopher %d is thinking ",n);
    //Take Fork
    pthread_mutex_lock(&Forks[n]);          // when philosopher 5 is eating he takes fork 1 and fork 5
    pthread_mutex_lock(&Forks[(n+1)%5]);
    //Eating
    printf("\nPhilosopher %d is eating ",n);

    sleep(5);
    //Putting Fork
    pthread_mutex_unlock(&Forks[n]);
    pthread_mutex_unlock(&Forks[(n+1)%5]);

    //Finished Eating
    // printf("\nPhilosopher %d Finished eating ",n);
}