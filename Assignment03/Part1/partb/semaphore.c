#include<stdio.h>
#include<fcntl.h>
#include<semaphore.h>
#include<sys/wait.h>
#include<pthread.h>
#include<stdlib.h>
#include <unistd.h>

sem_t *semaphore[20];
pid_t ppid[5];
char semaphorename[5];
int n;
int Eating(int val);

int main()
{
    int i,j=0;
    n = 5;

    //Creating Semaphore for all philospher working
    for(i=0;i<n;i++){
        sprintf(semaphorename,"%d",getpid()+i);
        semaphore[i]=sem_open(semaphorename,O_CREAT|O_EXCL,0666,1);
    }

    //Creating process
    for(i=0;i<n;i++){
        ppid[i]=fork();
        if(ppid[i]==0)
        break;
    }
    // when philosopher 5 is eating he takes fork 1 and fork 5
    if(i==n){
        int status;
        for(i=0;i<n;i++){
            waitpid(ppid[i],&status,WUNTRACED);
        }
        

        //waitpid is a function which waits for the child process to finish executing after that //control switches back to parent
        for(i=0;i<n;i++){
            sem_close(semaphore[i]);
            sprintf(semaphorename,"%d",getpid()+i);
            sem_unlink(semaphorename);
        }
    }
    else{
        Eating(i);
    }

}
int Eating(int val){
    // printf("%d Thinking\n",val+1);
    while(1)
    {
        sem_wait(semaphore[val%n]);
        if(!sem_trywait(semaphore[(val+1)%n])){
            break;
        }
        else{sem_post(
            semaphore[val%n]);
        }
        
    }
    sem_post(semaphore[val%n]);
    sem_post(semaphore[(val+1)%n]);

    while(1)
    {
        sem_wait(semaphore[val%n]);
        if(!sem_trywait(semaphore[(val+1)%n])){
            break;
        }
        else{sem_post(
            semaphore[val%n]);
        }
        
    }
    

    printf("%d Eating\n",val+1);

    sleep(2);

    sem_post(semaphore[val%n]);
    sem_post(semaphore[(val+1)%n]);

    // printf("%d Finished Eating\n",val+1);
}
