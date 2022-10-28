#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
int main(int agrc,char* argv[]){
    int c;
    if (agrc==1){
        printf("Enter Filename to read");
    }
    if(strcmp(argv[1],"-p")==0){
        c=mkdir(argv[1],0777);
        if (!c){
            printf("Created\n");
        }
    }
    if(strcmp(argv[1],"-v")==0){
        c=mkdir(argv[1],0777);
        if (!c){
            printf("Mkdir Created Directory %s\n",argv[2]);
        }
    }
    else{
        c=mkdir(argv[1],0777);
        if (!c){
            printf("Created\n");
        }
        else{
            printf("Error");
        }
    }
}
