#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_t philosopher[5];
int philosopher_flag[5]={0};
int Forks[5]={0};
void * func(void * i);
int bowl[2]={0};
int i;
int main(){
    int k;
    void *msg;
    
    //@https://stackoverflow.com/questions/29050328/pthread-join-function-in-c
    for(i=1;i<=4;i++){
        pthread_create(&philosopher[i],NULL,func,(void*)&i); // Create pthread for Philospher
        sleep(3);
        pthread_join(philosopher[i],NULL); // Joining pthread one by one 
        sleep(2);
    }

    if(i==5){
        printf("\nPhilosopher %d is Eating ",5);
        printf("\nPhilosopher %d Finished eating ",5);
    }
    return 0;
}
void * func(void * i){
    // printf("\nPhilosopher %d is thinking ",n);
    //Take Fork
    int n=*(int *)i;
    if (bowl[0]==0){
        n=*(int *)i;
            if (Forks[n]==0 && Forks[(n+1)%5]==0){
                printf("\nPhilosopher %d is Eating ",n);

                Forks[n]=1;
                Forks[(n+1)%5]=1;
                bowl[0]=1;
                printf("\nPhilosopher %d Finished eating ",n);
                Forks[n]=0;
                Forks[(n+1)%5]=0;
                bowl[0]=0;

            }
            else{
                sleep(3);
            } 
            if (*(int *)i==5){
                exit(1);
            }
    }
    if (bowl[1]==0){
            *(int *)i=*(int *)i+1;
           n=*(int *)i;
            if (Forks[n]==0 && Forks[(n+1)%5]==0){
                printf("\nPhilosopher %d is Eating ",n);
                if (n==5){
                    printf("\nPhilosopher %d Finished eating ",n);
                    exit(1);
                }
                Forks[n]=1;
                Forks[(n+1)%5]=1;
                bowl[1]=1;
                printf("\nPhilosopher %d Finished eating ",n);
                Forks[n]=0;
                Forks[(n+1)%5]=0;
                bowl[1]=0;

            }
            else{
                sleep(3);
            } 
            if (*(int *)i==5){
                exit(1);
            }
    }

      
     //@ https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
}