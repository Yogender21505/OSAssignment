#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#define NAME "StringFile"
#define PORT 8080
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

int main(int argc, char const* argv[])
{
	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;
	
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}
    ////////////Initializing random string and store them as a array///////////
    int num, fd;
    char *arr[50];
    char * ( *ptr )[50] = &arr;

    for (int i = 0; i < 50; i++)
    {
        ( *ptr )[i] =randstring(5);
    }
    ///////////////////////////////////////////////////////////////////////////
    serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd
		= connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
    ////////////////Transfering Strings to Server //////////////////
    struct timespec start, stop;
    double accum;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
        perror( "clock gettime" );
        return ;
    }
    fd = open(NAME, O_WRONLY);
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

        send(sock, string, strlen(string), 0);
        printf("P1: ID %d Successfull\n",i-1);
        i=i-1;
        }
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      return ;
    }
    accum = ( stop.tv_sec - start.tv_sec )
             + (double)( stop.tv_nsec - start.tv_nsec )
               / (double)BILLION;
    printf( "%lf\n", accum );
	// closing the connected socket
	close(client_fd);
	return 0;
}
//@reference taken from https://www.geeksforgeeks.org/socket-programming-cc/