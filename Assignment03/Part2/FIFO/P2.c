#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_NAME "StringFile"
int main(void){
    char s[80];
    int num, fd;
    mknod(FIFO_NAME, S_IFIFO | 0666, 0);
    printf("waiting for writers...\n");
    fd = open(FIFO_NAME, O_RDONLY);
    int x=1;
    printf("got a writer\n");
    do {
        if(x>2){
        if ((num = read(fd, s, 47)) == -1){
            perror("read");
        }
        else {
            s[strlen(s)] = '\0';
            printf("P2: String ID: \"%s\"\n",s);
        }}

        else{
            x++;
            if ((num = read(fd, s, 42)) == -1){
            perror("read");
        }
        else {
            s[strlen(s)] = '\0';
            printf("P2: String ID: \"%s\"\n",s);
        }
        }
    } while (num > 0);

    return 0;
}
