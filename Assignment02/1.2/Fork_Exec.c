#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <sched.h>
#include <sys/wait.h>

#define BILLION  1000000000L;
void removeWhiteSpace(char* buf){
	if(buf[strlen(buf)-1]==' ' || buf[strlen(buf)-1]=='\n')
	buf[strlen(buf)-1]='\0';
	if(buf[0]==' ' || buf[0]=='\n') memmove(buf, buf+1, strlen(buf));
}


void tokenize_buffer(char** param,int *nr,char *buf,const char *c){
	char *token;
	token=strtok(buf,c);
	int pc=-1;
	while(token){
		param[++pc]=malloc(sizeof(token)+1);
		strcpy(param[pc],token);
		removeWhiteSpace(param[pc]);
		token=strtok(NULL,c);
	}
	param[++pc]=NULL;
	*nr=pc;
}
void executeBasic(char** argv){
	if(fork()>0){
		//parent
		wait(NULL);
	}
	else{
		//child
		execvp(argv[0],argv);
		//in case exec is not successfull, exit
		perror("invalid input""\n");
		exit(1);
	}
}
void print(double *hist){
    for (int i=0;i<sizeof(hist)/sizeof(hist[0]);i++){
        printf("runtime taken by processes %lf",hist[i]);
    }

}

int main(char** argv,int argc)
{
	char buf[500],*buffer[100],buf2[500],buf3[500], *params1[100],*params2[100],*token,cwd[1024];
	int nr=0;
    double hist[3];
    int pos=0;
    struct timespec start, stop;
    double accum;
    FILE* filePointer; 
    filePointer = fopen("compilationofKernel.sh", "r");
    pid_t pid, pid1, pid2;

	while(1){
    
    pid = fork();
    if(fgets(buf, 500, filePointer)!=NULL){
                if (pid==-1){
                    abort();
                }
                else if (pid==0){
                    tokenize_buffer(params1,&nr,buf," ");
                    executeBasic(params1);
                    break;
                    raise(SIGSTOP);
                    

                }
                else{
                    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
                    perror( "clock gettime" );
                    return ;
                    }
                    waitpid(pid,NULL,WUNTRACED)
                    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
                    perror( "clock gettime" );
                    return ;
                    }
                        accum = ( stop.tv_sec - start.tv_sec )
                        + (double)( stop.tv_nsec - start.tv_nsec )
                        / (double)BILLION;
                // printf( "%lf\n", accum );
                        hist[pos++]=accum;
                    
                    kill(pid,SIGSTOP);
                }

    }
    pid1 = fork();
    if(fgets(buf, 500, filePointer)!=NULL){
            if (pid1==-1){
                abort();
            }
            else if (pid1==0){
                tokenize_buffer(params1,&nr,buf," ");
                executeBasic(params1);
                break;
                raise(SIGSTOP);


            }
            else{
                if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
                perror( "clock gettime" );
                return ;
                }
                waitpid(pid1,NULL,WUNTRACED);
                if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
                perror( "clock gettime" );
                return ;
                }
                    accum = ( stop.tv_sec - start.tv_sec )
                        + (double)( stop.tv_nsec - start.tv_nsec )
                        / (double)BILLION;
                // printf( "%lf\n", accum );
                hist[pos++]=accum;
                kill(pid1,SIGSTOP);
                
            }
    }

    pid2 = fork();
    if(fgets(buf, 500, filePointer)!=NULL){
            if (pid2==-1){
                abort();
            }
            else if (pid2==0){
                tokenize_buffer(params1,&nr,buf," ");
                executeBasic(params1);
                break;
                raise(SIGSTOP);

            }
            else{
                if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
                perror( "clock gettime" );
                return ;
                }
                waitpid(pid2,NULL,WUNTRACED);
                if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
                perror( "clock gettime" );
                return ;
                }
                    accum = ( stop.tv_sec - start.tv_sec )
                        + (double)( stop.tv_nsec - start.tv_nsec )
                        / (double)BILLION;
                // printf( "%lf\n", accum );
                hist[pos++]=accum;
                kill(pid2,SIGSTOP);
            }
    }
    else{
        print(hist);
        exit(0);
    }

    }
	return 0;
}