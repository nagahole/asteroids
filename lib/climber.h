#ifndef CLIMBER_H
#define CLIMBER_H

#include <stddef.h>

///////////////////////////////////////
// MACROS AND VARIABLES
///////////////////////////////////////

#define BYTE char

//////////////////////////////////////
// FUNCTION DECLARATIONS
/////////////////////////////////////


// You want to write this function
int climber(
    int (*hills)(const void*),
    char* (*hills_format)(),
    size_t num_attempts);


/*
 * useless_climber
 *
 * THIS CODE IS ONLY FOR DEMONSTRATION
 * IT SHOULD NOT BE YOUR FINAL CLIMBER 
 *
 * A useless climber, only passes a single integer in its location
 * buffer
 *
 * :: int (*hills)(const void*) :: Pointer to a hills function
 * :: char* (*hills_format) :: Pointer to a hills format function
 * :: size_t num_attempts :: number of attempts that may be made
 *
 *  Returns the best value it found
 */
int useless_climber(
    int (*hills)(const void*),
    char* (*hills_format)(),
    size_t num_attempts);


#endif