#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char  *argv[])
{
    DIR *Direct;
	struct dirent *File;
	Direct = opendir(".");
	

	if(argc==1){
		if(Direct!= NULL){
			while((File= readdir(Direct)) != NULL){
				if(!(strcmp(File->d_name,".")==0))
					printf("%s\n",File->d_name );
			}
		}
		closedir(Direct);
	}
		if(strcmp(argv[1],"-d")==0){
		if(Direct!= NULL){
			while((File= readdir(Direct)) != NULL){
				if(!(strcmp(File->d_name,".")==0 || strcmp(File->d_name,"..")==0))
					printf("%s*/.\t",File->d_name );
			}
		}
		closedir(Direct);
	}
	
	if(strcmp(argv[1],"-i")==0){
		int count=0;
		if(Direct!= NULL){
			while((File= readdir(Direct)) != NULL){
				if(!(strcmp(File->d_name,".")==0 || strcmp(File->d_name,"..")==0))
					printf("%d %s\t",count++,File->d_name );
			}
		}
		closedir(Direct);
	}

	return 0;
}
