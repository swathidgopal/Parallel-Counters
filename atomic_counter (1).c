#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define COUNTER_VALUE (1UL << 24)
#define MAX_THREADS 100
long int count =0;





void *atomic_Counter(void *arg)
{
	int x=0;
    for(x=0; x < COUNTER_VALUE; x++){__atomic_fetch_add(&count, 1, __ATOMIC_SEQ_CST);}
    return NULL;
}





int main(int argc, char** argv)
{
    int  n;
    n = atoi(argv[1]);
    clock_t begin= clock();
    pthread_t ptid[n];
    int i;
    for (i = 0; i < n; ++i){
        pthread_create(&ptid[i], NULL, atomic_Counter, NULL);   
    }
    for (i = 0; i < n; ++i){
        pthread_join(ptid[i], NULL);
    }
    clock_t finish = clock();
    assert(count == n * COUNTER_VALUE);
    double t_time = (double)(finish - begin);
    t_time=t_time*1000/ CLOCKS_PER_SEC;
    printf("\nCounter finish in %f ms", t_time);
    printf("\nThe value of counter is %ld", count);
    printf("\nThe value should be %ld\n", n*COUNTER_VALUE);
    return 0;
}





