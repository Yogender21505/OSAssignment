#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#define PORT 8080
#define NAME "StringFile"
int main(int argc, char const* argv[])
{
	int server_fd, new_socket, valread,fd;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[80];
    

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }



    int num;
    fd = open(NAME, O_RDONLY);
    int x=1;
    printf("got a writer\n");
    do {
        
        if(x>2){
        if ((num = read(new_socket, buffer, 47)) == -1){
            perror("read");
        }
        else {
            buffer[strlen(buffer)] = '\0';
            printf("P2: String ID: \"%s\"\n",buffer);
        }}

        else{
            x++;
            if ((num = read(new_socket, buffer, 42)) == -1){
            perror("read");
        }
        else {
            buffer[strlen(buffer)] = '\0';
            printf("P2: String ID: \"%s\"\n",buffer);
        }
        }
    } while (num > 0);

	close(new_socket);
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}

//@reference taken from https://www.geeksforgeeks.org/socket-programming-cc/