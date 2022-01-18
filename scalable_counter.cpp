#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>

#define COUNTER_VALUE (1UL << 24)

typedef struct counter
{
    unsigned long int value;
    pthread_mutex_t lock;
} counter;

void init_counter(counter *c)
{
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void *increment(void *arg)
{
    unsigned long int local_value = 0;
    counter *c = (counter *)arg;

    for (unsigned long int i = 0; i < COUNTER_VALUE ; i++) {
        local_value++;
    }
    pthread_mutex_lock(&c->lock);
    c->value = c->value + local_value;
    pthread_mutex_unlock(&c->lock);
    return NULL;
}

int main(void)
{
    counter c;
    unsigned int thread_count;
    pthread_t *threads;
    init_counter(&c);
    struct timespec tstart={0,0}, tend={0,0};
    uint64_t total_time = 0;

    printf("How many threads you want to create? ");
    scanf("%d", &thread_count);
    // thread_count = argv[0];

    threads = (pthread_t *) malloc (sizeof(pthread_t) * thread_count);

    clock_gettime(CLOCK_MONOTONIC, &tstart);

    for (unsigned int i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], NULL, increment, &c);
    }

    for (unsigned int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &tend);
    total_time = (COUNTER_VALUE * (tend.tv_sec - tstart.tv_sec)) +
        (tend.tv_nsec - tstart.tv_nsec);

    printf("Final value of counter : %ld in %lu milli-seconds.\n", c.value,
            (total_time/1000000));

    return 0;
}
