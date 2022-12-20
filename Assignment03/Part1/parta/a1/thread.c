#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_t philosopher[5];
int Forks[5]={0};
void * func(void * i);

int main(){
    int i,k;
    void *msg;
    //@https://stackoverflow.com/questions/29050328/pthread-join-function-in-c
    for(i=1;i<=5;i++){
        pthread_create(&philosopher[i],NULL,func,(void*)&i); // Create pthread for Philospher
        pthread_join(philosopher[i],&msg); // Joining pthread one by one 
        sleep(2);
    }

    return 0;
}
void * func(void * i){
    // printf("\nPhilosopher %d is thinking ",n);
    //Take Fork
    int n=*(int *)i;
    
    if (Forks[n]==0 && Forks[(n+1)%5]==0){
        printf("\nPhilosopher %d is Eating ",n);
        Forks[n]=1;
        Forks[(n+1)%5]=1;
    printf("\nPhilosopher %d Finished eating ",n);
    Forks[n]=0;
        Forks[(n+1)%5]=0;

    }else{
        sleep(3);
    }       
     //@ https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
}