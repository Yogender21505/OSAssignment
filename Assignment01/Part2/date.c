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

int main(int argc, char const *argv[])
{
    time_t Time;
	struct tm *tm;
	time(&Time);
	tm=localtime(&Time);
    char buffer[100];
	if(argc==1){
    time_t Time;
	struct tm *tm;
	time(&Time);
	tm=localtime(&Time);
    char buffer[100];
    strftime(buffer,100,"%a %b %d %X %Z %Y ", tm);
	printf("%s\n", buffer);
	}

	if(strcmp(argv[1],"-I")==0){
		strftime(buffer,100,"%Y-%m-%d ", tm);
		printf("%s\n", buffer);
	}
	else if (strcmp(argv[1],"-R")==0){
		strftime(buffer,100,"%a, %d %b %Y %X %Z ", tm);
		printf("%s +0530\n", buffer);
	}

}
