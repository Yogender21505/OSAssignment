#include <linux/syscalls.h>
#include <stdio.h>


#define kernel_2d_memcpy =451;
void check(float two[3][3]){
  for (int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      printf("%lf ",two[i][j]);
    }
    printf("\n");
  }
}

int main ()    
{    
    float src[][3]={ {1,2,3},
                      {4,5,6},
                      {8,9,10}};

    float dest[][3]={{11,12,13},
                      {14,15,16},
                      {17,18,19}};
    int i,j;
    printf("copying 2d matrix\n");
    long sys=syscalls(kernel_2d_memcpy,dest,src,3,3);
    check(dest);
    if (!sys){
      printf("451 system call successful\n");
    }
}


/*Reference 
BOOKS,LINKS OF TUTORIALS,ONLINE PROBLEMS SOLVING WEBSITE SUCH AS STACKOVERFLOW
*/