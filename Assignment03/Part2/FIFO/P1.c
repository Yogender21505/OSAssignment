#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_NAME "StringFile"


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

// @https://beej.us/guide/bgipc/pdf/bgipc_A4.pdf

int main(void){
    int num, fd;
    char *arr[50];
    char * ( *ptr )[50] = &arr;

    for (int i = 0; i < 50; i++)
    {
        ( *ptr )[i] =randstring(5);
    }

    mknod(FIFO_NAME, S_IFIFO | 0666, 0);
    printf("waiting for readers...\n");
    fd = open(FIFO_NAME, O_WRONLY);
    printf("got a reader--type some stuff\n");

    for (int i = 0; i < 50; i++){
        char string[3000]="";
        int j=0;
        strcat(string,"{");
        for (j=0;j<5;j++){
           strcat(string,( *ptr )[i]);
           strcat(string," ");
           char ins[50];
           sprintf(ins,"%d",i);
           strcat(string,ins);
           strcat(string," ");
        //    printf("%s\n",( *str )[pos-1]);
        i++;
        if(i==50){
            break;
        }
        }
        strcat(string,"}");
        // strcat(string,"\0");

        if ((num = write(fd, string, strlen(string))) == -1){
            perror("write");
        }
        else{
            printf("%s",string);
            printf("P1: ID %d get Successfull\n",i-1);
        }
        i=i-1;
    }
    return 0;
}
