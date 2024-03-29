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
#include <pthread.h>

/*
use with redirection(< > >>) to indicate to the function in which mode to open the file
and to know that redirection of the input OR output has to be done
*/
#define INPUT 0
#define OUTPUT 1
#define APPEND 2
const char* pthcommand;
/*
removes the newline and space character from the end and start of a char*
*/


void removeWhiteSpace(char* buf){
	if(buf[strlen(buf)-1]==' ' || buf[strlen(buf)-1]=='\n')
	buf[strlen(buf)-1]='\0';
	if(buf[0]==' ' || buf[0]=='\n') memmove(buf, buf+1, strlen(buf));
}

/*
tokenizes char* buf using the delimiter c, and returns the array of strings in param
and the size of the array in pointer nr
*/
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

/*
used for debugging purposes to print all the strings in a string array
*/

void print_params(char ** param){
	while(*param){
		printf("param=%s..\n",*param++);
	}
}

/*
loads and executes a single external command
*/

void *SyscallPthread(void *arg){
		//child
		system(pthcommand);
}

/*
loads and executes a series of external commands that are piped together
*/
void executePiped(char** buf,int nr){//can support up to 10 piped commands
	if(nr>10) return;
	
	int fd[10][2],i,pc;
	char *argv[100];

	for(i=0;i<nr;i++){
		tokenize_buffer(argv,&pc,buf[i]," ");
		if(i!=nr-1){
			if(pipe(fd[i])<0){
				perror("pipe creating was not successfull\n");
				return;
			}
		}
		if(fork()==0){//child1
			if(i!=nr-1){
				dup2(fd[i][1],1);
				close(fd[i][0]);
				close(fd[i][1]);
			}

			if(i!=0){
				dup2(fd[i-1][0],0);
				close(fd[i-1][1]);
				close(fd[i-1][0]);
			}
			execvp(argv[0],argv);
			perror("invalid input ");
			exit(1);//in case exec is not successfull, exit
		}
		//parent
		if(i!=0){//second process
			close(fd[i-1][0]);
			close(fd[i-1][1]);
		}
		wait(NULL);
	}
}

/*
loads and executes a series of external commands that have to be run asyncronously
*/
void executeAsync(char** buf,int nr){
	int i,pc;
	char *argv[100];
	for(i=0;i<nr;i++){
		tokenize_buffer(argv,&pc,buf[i]," ");
		if(fork()==0){
			execvp(argv[0],argv);
			perror("invalid input ");
			exit(1);//in case exec is not successfull, exit
		}
	}
	for(i=0;i<nr;i++){
		wait(NULL);
	}

}

/*
loads and executes a an external command that needs file redirection(input, output or append)
*/
void executeRedirect(char** buf,int nr,int mode){
	int pc,fd;
	char *argv[100];
	removeWhiteSpace(buf[1]);
	tokenize_buffer(argv,&pc,buf[0]," ");
	if(fork()==0){

		switch(mode){
		case INPUT:  fd=open(buf[1],O_RDONLY); break;
		case OUTPUT: fd=open(buf[1],O_WRONLY); break;
		case APPEND: fd=open(buf[1],O_WRONLY | O_APPEND); break;
		default: return;
		}

		if(fd<0){
			perror("cannot open file\n");
			return;
		}

		switch(mode){
		case INPUT:  		dup2(fd,0); break;
		case OUTPUT: 		dup2(fd,1); break;
		case APPEND: 		dup2(fd,1); break;
		default: return;
		}
		execvp(argv[0],argv);
		perror("invalid input ");
		exit(1);//in case exec is not successfull, exit
	}
	wait(NULL);
}


int main(char** argv,int argc)
{
	char buf[500],*buffer[100],buf2[500],buf3[500], *params1[100],*params2[100],*token,cwd[1024];
	int nr=0;

	do{

		//print current Directory
        
		if (getcwd(cwd, sizeof(cwd)) != NULL){
			printf("%s  ", cwd);
		}
		else{
			printf("getcwd failed\n");
		} 	
		// pthread_t th1;
		//read user input
		fgets(buf, 500, stdin);//buffer overflow cannot happen
		//check if only a simple command needs to be executed or multiple piped commands or other types
		// if(strchr(buf,'|')){//tokenize pipe commands
        //     tokenize_buffer(buffer,&nr,buf,"|");
		// 	executePiped(buffer,nr);
		// }
		// else if(strchr(buf,'&')){//asyncronous execution
		// 	tokenize_buffer(buffer,&nr,buf,"&");
		// 	executeAsync(buffer,nr);
		// }
		// else if(strstr(buf,">>")){//append output to file
		// 	tokenize_buffer(buffer,&nr,buf,">>");
		// 	if(nr==2)executeRedirect(buffer,nr,APPEND);
		// 	else printf("Incorrect output redirection!(has to to be in this form: command >> file)");
		// }
		// else if(strchr(buf,'>')){//redirect output to file
		// 	tokenize_buffer(buffer,&nr,buf,">");
		// 	if(nr==2)executeRedirect(buffer,nr, OUTPUT);
		// 	else printf("Incorrect output redirection!(has to to be in this form: command > file)");
		// }
		// else if(strchr(buf,'<')){//redirect file to input
		// 	tokenize_buffer(buffer,&nr,buf,"<");
		// 	if(nr==2)executeRedirect(buffer,nr, INPUT);
		// 	else printf("Incorrect input redirection!(has to to be in this form: command < file)");
		// }
		// else{//single command including internal ones
			tokenize_buffer(params1,&nr,buf," ");
			if(strstr(params1[0],"cd")){//cd builtin command
				chdir(params1[1]);
			}
			else if(strstr(params1[0],"exit")){//exit builtin command
				exit(0);
			}
			else{
				int i=0;
				char new[100]="";
				while(params1[i]!=NULL){
					if (strcmp(params1[i],"&t")!=0){
						strcat(new," ");
						strcat(new,params1[i]);
					}
					i++;
				}

				if (strcmp(params1[0],"&t")==0){
					pthread_t th1;
					pthcommand=new;
					pthread_create(&th1,NULL,SyscallPthread,(void*)&th1);
					pthread_join(th1,NULL);
				}
				else{
					system(new);
				}
            } 
		// }
	}while(1==1);
	return 0;
}
