#include <stdio.h>
#include <time.h>

unsigned long int count;

int main()
{
    time_t begin, end;
    unsigned int i;

    begin = time(NULL);
    end = time(NULL);

    for (i = 1; i <= 10E8; i++)
    {
        if (0 != i%2)
            count += 1;        
    }
    
    end = time(NULL);
    printf("%ld number - %lu seconds\n", count, end-begin);
    return 0;  
}
