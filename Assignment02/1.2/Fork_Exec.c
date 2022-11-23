#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    char buf[500],*buffer[100],buf2[500],buf3[500], *params1[100],*params2[100],*token,cwd[1024];
	int nr=0;
    char *args1[]={"bash","compilationofKernel1.sh",NULL};
    char *args2[]={"bash","compilationofKernel2.sh",NULL};
    char *args3[]={"bash","compilationofKernel3.sh",NULL};


    int pid1=fork();
    if(pid1==-1){
        printf("error creating process");
        return 1;
    }
    if (pid1==0){
        // sleep(4);
        // printf("pid1\n");
        execvp(args1[0],args1);
        return 0;
    }
    int pid2=fork();
    if(pid2==-1){
        printf("error creating process");
        return 1;
    }
    if (pid2==0){
        // sleep(1);
        // printf("pid2\n");
        execvp(args2[0],args2);
        return 0;
    }
    int pid3=fork();
    if(pid3==-1){
        printf("error creating process");
        return 1;
    }
    if (pid3==0){
        // sleep(1);
        // printf("pid3\n");
        
        execvp(args3[0],args3);
        return 0;
    }
    int pid1_res= waitpid(pid1,NULL,0);
    // printf("pid1 =%d\n",pid1_res);
    int pid2_res= waitpid(pid2,NULL,0);
    // printf("pid2 =%d \n",pid2_res);
    int pid3_res= waitpid(pid3,NULL,0);
    // printf("pid3 =%d \n",pid3_res);
	return 0;
}