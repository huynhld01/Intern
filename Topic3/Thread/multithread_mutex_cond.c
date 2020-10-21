#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <stdio.h>

#define T1  9
#define T2  14 
#define DONE 20

int count;
pthread_mutex_t mutex_count = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_condition = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t var_condition = PTHREAD_COND_INITIALIZER;

void *fn_count1();
void *fn_count2();


void main()
{
    pthread_t thread1, thread2;
    int ret1, ret2;
    
    ret1 = pthread_create( &thread1, NULL, &fn_count1, NULL);
    ret2 = pthread_create( &thread2, NULL, &fn_count2, NULL);
    if ( 0 != ret1 || 0 != ret2 )
    {
        perror("False reason:");
    }
    pthread_join( thread1, NULL );
    pthread_join( thread2, NULL );
    
}

void *fn_count1()
{
    for (;;)
    {
        pthread_mutex_lock( &mutex_condition );
        while (count >= T1 && count <= T2 )
        {
            pthread_cond_wait( &var_condition, &mutex_condition );
        }
        pthread_mutex_unlock( &mutex_condition );

        pthread_mutex_lock( &mutex_count );
        count++;
        printf("count value fn_count1: %d\n", count);
        sleep(2);
        pthread_mutex_unlock( &mutex_count );
        if ( count >= DONE ) 
            pthread_exit(NULL);
    }
}


void *fn_count2()
{
    for (;;)
    {
        pthread_mutex_lock( &mutex_condition );
        while( count < T1 || count > T2 )
        {
            pthread_cond_signal( &var_condition );
        }
        pthread_mutex_unlock( &mutex_condition );
        
        pthread_mutex_lock( &mutex_count );
        count++;
        printf("count value fn_count2: %d\n", count);
        sleep(2);
        pthread_mutex_unlock( &mutex_count );
        
        if (count >= DONE ) 
            pthread_exit(NULL);
    }
}
