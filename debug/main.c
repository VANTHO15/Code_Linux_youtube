#include "stdio.h"
void sum(int a, int b)
{
    printf("sum = %d\n",a+b);
}
int main()
{
    printf("hello ThoNV\n");
    for(int i =0;i< 10;i++)
    {
        printf(" i number = %d\n",i);
    }
    sum(1,2);
    return 1;
}