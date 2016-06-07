#include "malloc_count.h"
#include "stack_count.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void *malloc_safety_test(void *ptr);
#define ALLOCATE_TOTAL_ROUNDS 655350

int main(int argc, char **argv)
{
        pthread_t *tid;
        int *thread_id_msg;
        int num_threads;
        int thread_idx;
        if (argc != 2)
        {
                printf("usage: %s <num of thread>\n", argv[0]);
                exit(0);
        }
        num_threads = atoi(argv[1]);

        tid = malloc(sizeof(pthread_t) * num_threads);
        thread_id_msg = malloc(sizeof(int) * num_threads);    

        for (thread_idx = 0; thread_idx < num_threads; ++thread_idx)
                thread_id_msg[thread_idx] = thread_idx;
          /* Create threads and wait for them to finish */
        for (thread_idx = 0; thread_idx < num_threads; ++thread_idx)
        {
                printf("In main: Creating thread %d\n", thread_id_msg[thread_idx]);
                pthread_create(&tid[thread_idx], NULL, malloc_safety_test, &thread_id_msg[thread_idx]);
        }

        for (thread_idx = 0; thread_idx < num_threads; ++thread_idx)
                pthread_join(tid[thread_idx], NULL);
#if 0
        /*Check result*/
        if (cnt != (NUM_THREADS * niters))
                printf("BOOM! cnt=%d\n", cnt);
        else
                printf("OK cnt=%d\n", cnt);
#endif
        malloc_count_print_status();
        pthread_exit(NULL);


}


void *malloc_safety_test(void *ptr)
{
        long round;
        int  thread_id = *(int *)ptr;
        printf("[thread:%d] Mem status cur %d ,peak %d\n", thread_id, 
                        malloc_count_current(),malloc_count_peak());
        for(round = 0 ; round < ALLOCATE_TOTAL_ROUNDS ; round++)
        {
            void* a = malloc(10);
            free(a);
        }
}