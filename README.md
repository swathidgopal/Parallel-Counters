# Parallel-Counters
Here we implement four different ways to explore the fundamental issues of concurrency without the distractions of elaborate data structures or complex synchronization primitives.
1. Naïve counter : For each running thread, we increment the common counter by one in the loop. However, the threads access the counter atthe same time, resulting in an inaccurate result.
2. Naïve counter plus : Synchronization is used to lock the threads and provide the accurate counter output. We use mutex to lock the thread before incrementing it and then release it so that other threads can
access it.
3. Atomic counter : __atomic fetch add is an atomic operation that we use. Other threads can't access the counter while it's being incrementedbecause this action employs atomic variables.
4. Scalable counter : We scale the counter across the CPU cores.
