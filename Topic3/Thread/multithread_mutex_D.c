#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <stdio.h>

unsigned int count;
pthread_mutex_t mutex;

void *fn_count(void *argv)
{  
    pthread_mutex_lock(&mutex);
    unsigned int i;
    unsigned int n = *(unsigned long*)argv;
    for (i = 1; i <= n; i++)
    {
        if (0 != i%2){
            count += 1;
        }
    }
    pthread_mutex_unlock(&mutex);
}

void main()
{
    int reval1, reval2;
    pthread_t thread0;
    pthread_t thread1;
    unsigned int num1 = 5E8;
    unsigned int num2 = 5E8;
    
    pthread_mutex_init(&mutex, NULL);    
    reval1 = pthread_create(&thread0, NULL, fn_count, (void*)&num1);
    reval2 = pthread_create(&thread1, NULL, fn_count, (void*)&num2);
    
    if (0 != reval1 || 0 != reval2)
    {
        printf("pthread_create() error\n");
        perror("False reason:");
    }
    
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    
    
    printf("%d number\n",count);
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);    
}
