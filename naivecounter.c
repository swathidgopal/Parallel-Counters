#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define COUNTER_VALUE (1UL << 24)
#define MAX_THREADS 50
long int count =0;




void *naive_Counter(void *input){
    int x=0;
    for(x=0; x < COUNTER_VALUE; x++){count=count+1;}  
    pthread_exit(NULL);
}




int main(int argc, char** argv) {
    int thread, n;
    n = atoi(argv[1]);    
    pthread_t ptid[n];
    float time_elapsed;
    if(argc < 2) 
    {
        printf("Enter Number of threads\n");
        exit(1); 
    } 
    struct timeval begin;
    struct timeval finish;
    gettimeofday(&begin, NULL); 
    clock_t starting = clock();
    int i=0;
    for(i = 0; i < n; i++)
    {
        thread = pthread_create(&ptid[i], NULL, naive_Counter, NULL);
        if(thread)        {exit(1);}
    }
    clock_t ending = clock();
    gettimeofday(&finish, NULL); 
     double total= ((finish.tv_sec - begin.tv_sec)*1000) + finish.tv_usec - begin.tv_usec;
    double t_time = (double)(ending - starting);
    t_time=(double) t_time*10000/ CLOCKS_PER_SEC;
    printf("\nCounter finish in %lf ms", total );
    printf("\nThe value of the counter should be %ld\n", n*COUNTER_VALUE); 
    printf("\nThe value of counter is %ld\n", count);
    pthread_exit(NULL);
    return 0;
}





