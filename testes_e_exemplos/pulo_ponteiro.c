#include <stdio.h>


int main(void){

    double *p;
    double x[] = {10,11};
    p = x;

    printf("%p \n", p);
    ++p;
    printf("%p", p);
    return 0;
};