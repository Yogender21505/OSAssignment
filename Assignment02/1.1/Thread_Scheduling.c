#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sched.h>

#define BILLION  1000000000L;
int Priority[3][3]={{1,1,1},{4,4,4},{8,8,8}};
int len=0;
pthread_t tha;
pthread_t thb;
pthread_t thc;

void* countA(void* arg)
{
        (void)arg;

    int policy = SCHED_OTHER;   // any higher policy will cause 'pthread_setschedparam()` to fail.

    struct sched_param param;
    param.sched_priority = Priority[len][0];   // any higher priority will cause 'pthread_setschedparam()` to fail.
    pthread_t tha;
    pthread_setschedparam(tha, policy, &param );
    long long int count =0;
    for (long long int i=1;i<4294967296;i++){
        count++;
    }
    }

void* countB(void* arg)
{
        (void)arg;


    int policy = SCHED_RR;   // any higher policy will cause 'pthread_setschedparam()` to fail.


    struct sched_param param;
    param.sched_priority = Priority[len][0];   // any higher priority will cause 'pthread_setschedparam()` to fail.


    // printf( "in Thread: tha = %d\n", (int)thb );

    int ret= pthread_setschedparam( thb, policy, &param );
    if(ret==0)
    {
    long long int count=0;
    for (long long int i=1;i<4294967296;i++){
      count++;
    }
    }

}
void* countC(void* arg)
{
        (void)arg;

        int policy = SCHED_FIFO;   // any higher policy will cause 'pthread_setschedparam()` to fail.


        struct sched_param param;
        param.sched_priority = Priority[len][0];    // any higher priority will cause 'pthread_setschedparam()` to fail.


        // printf( "in Thread: tha = %d\n", (int)thc );

        int ret= pthread_setschedparam( thc, policy, &param );
        long long int count=0;
        if(ret==0)
        {
        for (long long int i=1;i<4294967296;i++){
          count++;
        }
        }
}
  
void Thr_A()
{

    // any priority and/or scheduling changes should be
    // applied via the second parameter to 'pthread_create()';
    
    pthread_create( &tha, NULL, countA, NULL);
    pthread_join( tha, NULL );

}

void Thr_B()
{
    // any priority and/or scheduling changes should be
    // applied via the second parameter to 'pthread_create()'
    pthread_create( &thb, NULL, countA, NULL);
    pthread_join( thb, NULL );

}
void Thr_C()
{

    // any priority and/or scheduling changes should be
    // applied via the second parameter to 'pthread_create()'
    pthread_create( &thc, NULL, countA, NULL);
    pthread_join( thc, NULL );

}
void red () {
  printf("\033[1;31m");
}
void yellow() {
  printf("\033[1;33m");
}
void reset () {
  printf("\033[0m");
}
void printHistogram ( double *hist, double n );

void printHistogram(double *hist, double n) {
      int i;
      double j;
      n=3;
      printf("------- Priority with %d ------\n",Priority[len][0]);
      for (i = 0; i < n; i++) {
      if (i==0){
        red();
        printf("Sched_Other_%d ",Priority[len][0]);
          for ( j = 0; j < hist[i]; j=j+0.1) {
          printf("|");
          }
          printf(" %lf",hist[i]);
      }
      if (i==1){
          yellow();
          printf("Sched_RR_%d    ",Priority[len][1]);
          for ( j = 0; j < hist[i]; j=j+0.1) {
          printf("|");
          }
          printf(" %lf",hist[i]);
      }
      if (i==2){
        reset();
          printf("Sched_FIFO_%d  ",Priority[len][2]);
          for ( j = 0; j < hist[i]; j=j+0.1) {
          printf("|");
          }
          printf(" %lf",hist[i]);
      }
      printf("\n");
      
   }
}
void func(){
  double hist[3];
    int pos=0;
        struct timespec start, stop;
    double accum;

    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      return ;
    }

    Thr_A();

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      return ;
    }

    accum = ( stop.tv_sec - start.tv_sec )
             + (double)( stop.tv_nsec - start.tv_nsec )
               / (double)BILLION;
    // printf( "%lf\n", accum );
    hist[pos++]=accum;

    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      return ;
    }


    Thr_B();

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      return ;
    }

    accum = ( stop.tv_sec - start.tv_sec )
             + (double)( stop.tv_nsec - start.tv_nsec )
               / (double)BILLION;
    // printf( "%lf\n", accum );
    hist[pos++]=accum;


    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      return ;
    }


    Thr_C();

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      return ;
    }

    accum = ( stop.tv_sec - start.tv_sec )
             + (double)( stop.tv_nsec - start.tv_nsec )
               / (double)BILLION;
    // printf( "%lf\n", accum );
    hist[pos]=accum;

    printHistogram(hist, 0.1);
}
// Driver code
int main()
{
    for (int i=0;i<3;i++){
        printf("--------------------------------------------\n");
          func();

          len++;
    }
    printf("--------------------------------------------\n");

    return 0;
}