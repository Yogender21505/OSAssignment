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
void createsemaphore(){
        int i;
        for(i=0;i<n;i++){
        sprintf(semaphorename,"%d",getpid()+i);
        semaphore[i]=sem_open(semaphorename,O_CREAT,0644,1);
    }
}
int main()
{
    int i,j=0;
    n = 5;

    //Creating Semaphore for all philospher working
    createsemaphore();

    //Creating process
    for(i=0;i<n;i++){
        ppid[i]=fork();
        
        if(ppid[i]==0){
                    break;
        }
    }

    // when philosopher 5 is eating he takes fork 1 and fork 5
    if(i==5){
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

    do
    {
        sem_wait(semaphore[val%n]);
        if(!sem_trywait(semaphore[(val+1)%n])){
            break;
        }
        else{sem_post(
            semaphore[val%n]);
        }
        
    }while(1);
    sem_post(semaphore[val%n]);
    sem_post(semaphore[(val+1)%n]);

    do
    {
        sem_wait(semaphore[val%n]);
        if(!sem_trywait(semaphore[(val+1)%n])){
            break;
        }
        else{sem_post(
            semaphore[val%n]);
        }
        
    }while(1);
    

    printf("%d Eating\n",val+1);

    sleep(2);

    sem_post(semaphore[val%n]);
    sem_post(semaphore[(val+1)%n]);

    // printf("%d Finished Eating\n",val+1);
}

//The sem_open() function opens a named semaphore, returning a semaphore pointer 
// that may be used on subsequent calls
// to sem_post(), sem_post_np(), 
// sem_wait(), sem_wait_np(),
// sem_trywait(), sem_getvalue(), 
// and sem_close(). When a semaphore 
// is being created, the parameters mode and value must be specified on the
// call to sem_open(). If a semaphore is created, then the maximum SEM_VALUE_MAX
// of the semaphore is set to SEM_VALUE_MAX and the title of the semaphore
// is set to the last 16 characters of the name.

//@https://stackoverflow.com/questions/19837412/how-to-replace-sem-init-with-sem-open-for-non-pointer-semaphore
//