#include <stdlib.h>

void main()
{
    int *p = malloc(sizeof(int) * 5);
    free(p);
}