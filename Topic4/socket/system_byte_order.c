#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(void)
{
    uint32_t i = 0x04030201;
    unsigned char *cp = (unsigned char *)&i;
    
    if (1 == *cp)
        printf("little-endian\n");
    else if (4 == *cp)
        printf("big-endian\n");
    else 
        printf("who know\n");
    return(0);
}
