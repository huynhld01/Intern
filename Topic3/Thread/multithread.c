#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <stdio.h>

unsigned int count;

void *fn_count(void *argv)
{
    unsigned int i;
    unsigned int local_count = 0;
    unsigned int n = *(unsigned long*)argv;
    for (i = 1; i <= n; i++)
    {
        if (0 != i%2){
            local_count += 1;
        }
    }
    count += local_count;
}

void main()
{
    time_t start, finish;
    int reval1, reval2;
    pthread_t thread0;
    pthread_t thread1;
    unsigned int num1 = 5E8;
    unsigned int num2 = 5E8;
    start = time(NULL);
    finish = time(NULL);
    
    reval1 = pthread_create(&thread0, NULL, fn_count, (void*)&num1);
    reval2 = pthread_create(&thread1, NULL, fn_count, (void*)&num2);
    
    if (0 != reval1 || 0 != reval2)
    {
        printf("pthread_create() error\n");
        perror("False reason:");
    }
    
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    
    finish = time(NULL);
    
    printf("%d number - %ld seconds\n",count, finish-start);
    pthread_exit(NULL);    
}
