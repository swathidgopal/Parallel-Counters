#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COUNTER_VALUE (1UL << 24)
#define MAX_THREADS 100
pthread_mutex_t m_lock = PTHREAD_MUTEX_INITIALIZER;
long int count =0;



void *naive_Counter(void *input)
{
  pthread_mutex_lock( &m_lock );	
  long int x;	
  for(x=0; x < COUNTER_VALUE; x++){count=count+1;}
    pthread_mutex_unlock( &m_lock );
    pthread_exit(NULL);
}



int main(int argc, char** argv) {
  struct timespec tstart={0,0} ,tend={0,0};

  int thread, y;
    y = atoi(argv[1]);// to convert cmd line argument to integer
	if(y > MAX_THREADS) y = MAX_THREADS;
    pthread_t ptid[y];
    float time_elapsed;
    if(argc < 2) 
    {   printf("Enter Number of threads\n");
        exit(1); 
    }
     struct timeval begin;
     struct timeval finish;
     gettimeofday(&begin, NULL); 
     clock_t starting = clock();
     // clock_gettime(CLOCK_MONOTONIC, &tstart);
    int i;
    for(i = 0; i < y; i++)
    {
        thread = pthread_create(&ptid[i], NULL, naive_Counter, NULL);
        if(thread)
        {exit(1);}
    }
    for(i=0; i<y; i++)
    {
        pthread_join(ptid[i], NULL);
    }
    // clock_gettime(CLOCK_MONOTONIC, &tend);
    // total_time=(COUNTER_VALUE * (tend.tv_sec - tstart.tv_sec))+(tend.tv_nsec -tstart.tv_nsec);
     clock_t ending = clock();
        gettimeofday(&finish, NULL);
     double total= ((finish.tv_sec - begin.tv_sec)*1000) + finish.tv_usec - begin.tv_usec;
     double t_time = (double)(ending - starting);
     t_time=(double) t_time*1000/ CLOCKS_PER_SEC;
     // t_time=(double) t_time/1000;
    printf("\nCounter finish in %lf ms", t_time );
    printf("\nThe value of counter should be %ld", y*COUNTER_VALUE);
    printf("\nThe value of counter is %ld\n", count);
    pthread_exit(NULL);
    return 0;
}





