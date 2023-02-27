#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"

#define LED  (31)

int main()
{
    printf(" *********************************");

    GPIOExport(LED);
    GPIODirection(LED, OUT);
    GPIOWrite(LED, 1);
    
    return 0;
}
