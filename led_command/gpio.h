
#ifndef GPIO_H 
#define GPIO_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <errno.h>


#define IN  	( 0 )	///< GPIO direction as input
#define OUT 	( 1 )	///< GPIO direction as output
 
#define LOW 	( 0 )	///< GPIO value Low
#define HIGH 	( 1 )	///< GPIO value High

#define BUFFER_MAX 		( 4 )
#define DIRECTION_MAX 	( 35 )

#define VALUE_MAX 		( 30 )


int32_t GPIOExport( int32_t pin_ );

int32_t GPIODirection( int32_t pin_, int32_t dir_ );

int32_t GPIOWrite( int32_t pin_, int32_t value_ );

#endif /// End of GPIO_H

