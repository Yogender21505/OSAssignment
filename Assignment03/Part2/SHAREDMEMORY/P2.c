#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#include<time.h>

#define BILLION  1000000000L;
char *randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";        
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {            
            for (int n = 0;n < length;n++) {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
    //@https://codereview.stackexchange.com/questions/29198/random-string-generator-in-c
}


int main(){
int i;
void *shared_memory;

int shmid;
shmid=shmget((key_t)2345, 1024, 0666|IPC_CREAT); //creates shared memory segment with key 2345, having size 1024 bytes.

shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment
// read(0,buff,100); //get some input from user
int num, fd;
char *arr[50];
char * ( *ptr )[50] = &arr;

for (int i = 0; i < 50; i++)
{
	( *ptr )[i] =randstring(5);
}

char buff[3000]="";

struct timespec start, stop;
    double accum;
if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      return ;
}
for (int i = 0; i < 50; i++){

        int j=0;
        strcat(buff,"{");
        for (j=0;j<5;j++){
           strcat(buff,( *ptr )[i]);
           strcat(buff," ");
           char ins[50];
           sprintf(ins,"%d",i);
           strcat(buff,ins);
           strcat(buff," ");
        //    printf("%s\n",( *str )[pos-1]);
        i++;
        if(i==50){
            break;
        }
        }
        strcat(buff,"}\n");
		
        // strcat(string,"\0");

            printf("P1: ID %d get Successfull\n",i-1);
        i=i-1;
    }
	strcpy(shared_memory,buff);
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      return ;
    }
    accum = ( stop.tv_sec - start.tv_sec )
             + (double)( stop.tv_nsec - start.tv_nsec )
               / (double)BILLION;
    printf( "%lf\n", accum );
	return 0;

}