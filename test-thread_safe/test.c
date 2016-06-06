#include "malloc_count.h"
#include "stack_count.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

int test_count;
void *malloc_safety_test(void *ptr);


int main()
{

    pthread_t *thread;
    int *ThreadID_ptr  ;
    int  i;
    int iret;


    printf("How many  thread run ?");
    scanf("%d",&test_count);
    if(test_count < 0){
          printf("Wrong number.");
          return -1;
    }
   ThreadID_ptr    = malloc(sizeof(int)*test_count);
   thread               = malloc(sizeof(pthread_t)*test_count);

   for(i=0;i<test_count;i++){
        ThreadID_ptr[i] = i ;
   }
   for(i=0;i<test_count;i++){
            iret = pthread_create(thread+i,NULL,malloc_safety_test,(void *)(ThreadID_ptr+i));

   }
   for(i=0;i<test_count;i++){
            pthread_join(thread[i],NULL);
    } 
    malloc_count_print_status();

    return 0;
}


void *malloc_safety_test(void *ptr){
    
    const long count = 655350;
    long i ;
    int  Thread_ID = *(int *)ptr;
    printf("After create thread %d Mem status cur %d ,peak %d\n",Thread_ID,malloc_count_current(),malloc_count_peak());
    for(i=0;i<count;i++){
        void* a = malloc(10);
        free(a);
       
    }

}