#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <errno.h>

int main()
{
    char *args1[]={"bash","compilationofKernel1.sh",NULL};
    char *args2[]={"bash","compilationofKernel2.sh",NULL};
    char *args3[]={"bash","compilationofKernel3.sh",NULL};
    struct sched_param param1,param2,param3;
    
    int pid1=fork();
    int pid2=fork();
    int pid3=fork();
    if(pid1==-1){
        printf("error creating process");
        return 1;
    }
    if (pid1==0 && pid2 >0 && pid3 > 0){
        param1.sched_priority = 1;
        sched_setscheduler(getpid(),SCHED_OTHER,&param1);
        // sleep(4);
        // printf("pid1\n");
        // sleep(10);
        execvp(args1[0],args1);
        return 0;
    }
    
    if(pid2==-1){
        printf("error creating process");
        return 1;
    }
    if (pid2==0 && pid1 >0 && pid3 > 0){
        // sleep(1);
        param2.sched_priority = 3;
        sched_setscheduler(getpid(),SCHED_OTHER,&param2);
        // printf("pid2\n");
        // sleep(10);
        execvp(args2[0],args2);
        return 0;
    }

    if(pid3==-1){
        printf("error creating process");
        return 1;
    }
    if (pid3==0 && pid1 >0 && pid2 > 0){
        // sleep(1);
        param3.sched_priority = 5;
        sched_setscheduler(getpid(),SCHED_OTHER,&param3);
        // printf("pid3\n");
        // sleep(10);
        execvp(args3[0],args3);
        return 0;
    }
    int pid1_res= waitpid(pid1,NULL,0);
    int pid2_res= waitpid(pid2,NULL,0);
    int pid3_res= waitpid(pid3,NULL,0);
	return 0;
}