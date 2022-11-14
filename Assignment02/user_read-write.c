#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>


#define DataSize 25

int main(){
    int fd;
    char kernelData[DataSize];
    char *userData = "Linux Device Driver";

    fd = open("/dev/new_device", O_RDWR);
    if (fd<0){
        pritnf("the file opened failed.\n");
        return -1;
    }
    else{
        printf("the file opened with fd as %d\n",fd);
    }
    write (fd,userData,DataSize);
    printf("the data write to the device %s\n",userData);
    read(fd,kernelData,DataSize);
    printf("the data read from the device.: %s\n",kernelData);
    closed(fd);
    printf("the file is closed with the fd in read 1: %d\n",fd);
    return 0;
}