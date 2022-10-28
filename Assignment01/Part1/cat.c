#include <stdio.h>
#include <string.h>

int main(int argc,char* argv[]){
    FILE* file_name;
    if (argc==1){
        printf("Enter Filename to read");
    }
    if(strcmp(argv[1],"-n")==0){
        file_name =fopen(argv[2],"r");
        if( file_name == NULL){
            printf("Error");
        }
        else{
            int count=1;
            char *s=NULL;
            size_t len;
            int i;
            while((i= getline(&s,&len,file_name))!=-1){
                printf("%d %s",count++,s);
            }
            fclose(file_name);
        }

	}
    else{
    file_name=fopen(argv[1],"r");
    if (!file_name || argc!=2){
        printf("Error");
    }
    char s;
    while((s=fgetc(file_name))!=EOF){
        printf("%c",s);
    }
    fclose(file_name);
    }

}
