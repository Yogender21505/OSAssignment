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
	if(argc==1){
		printf("Enter the file name!\n");
	}
	else if(strcmp(argv[1],"-i")==0){
				int get=remove(argv[2]);
				if(get == 0){
					printf("Deleted\n" );
				}
				else{
					printf("Not Deleted ");

				}
			}
			
	else{
			int get = remove(argv[1]);
            if(get == 0){
                printf("Deleted\n" );
            }
            else{
                printf("Not Deleted");

            }
	}
	return 0;
}
