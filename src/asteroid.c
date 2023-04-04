#include "asteroid.h"

// Public functions that are declared in the header

/*
 * asteroid_create
 * Creates an asteroid
 * :: void* data :: The location to store the asteroid data
 * :: fx_args    :: The polynomial for the x coordinates
 * :: fy_args    :: The polynomial fo rthe y coordinates 
 * Acts in place.
 *
 * Format of asteroid:
 * - First 4 bytes: time t (initiated at 0)
 * - Second 4 bytes: tolerance
 * - Third 4 bytes: Number of coefficients for x polynomial
 * - Four+ chunks of 4 bytes: Coefficients of x polynomial
 * - Next 4 byte: Number of coefficients for y polynomial
 * - Next chunks of 4 bytes: Coefficients of y polynomial
 */

void asteroid_create(
        void* data,
        const float tolerance,
        void* fx_args,
        void* fy_args)
{ 
    int fx_args_count = ((int*) fx_args)[0];
    int fy_args_count = ((int*) fy_args)[0];

    ((int*) data)[0] = 0; //time = 0
    ((float*) data)[1] = tolerance;
    ((int*) data)[2] = fx_args_count;

    for(int i = 0; i < fx_args_count; i++) 
    {
        ((float*) data)[3 + i] = ((float*) fx_args)[i + 1];
    }

    ((int*) data)[fx_args_count + 3] = fy_args_count;
    
    for(int i = 0; i < fy_args_count; i++)
    {
        ((float*) data)[fx_args_count + 4 + i] = ((float*) fy_args)[i + 1];
    }

    return;
}


/*
 * asteroid_update
 * :: void* asteroid ::
 * Updates the position of the asteroid
 */
void asteroid_update(void* asteroid)
{
    ((int* ) asteroid)[0]++; //Increments time t by 1
}

/*
 * asteroid_impact
 * Checks if an asteroid has impacted on flatland
 * :: void* asteroid :: The asteroid that may have impacted
 * Returns 1 if an impact has occured, and 0 otherwise
 */
int asteroid_impact(void* asteroid)
{
    int time = ((int*) asteroid)[0];

    if (time == ASTEROID_CLEARED_VALUE)
        return 0;

    int fx_args_count = ((int*) asteroid)[2];

    //cast to int so can jump in bytes of 4 using square bracket notation
    void* y_polynomial= (void*) ((int*) asteroid + 3 + fx_args_count); 

    return polynomial_evaluate(y_polynomial, time) <= 0;
}



/*
 * asteroid_intercept
 * Attempts to intercept an asteroid at location (x, y)
 * :: void* asteroid  :: Asteroid object to intercept
 * :: float x         :: Guess of the x coordinate
 * :: float y         :: Guess of the y coordinate 
 * :: float tolerance :: The maximum permitted error for the guess
 * Returns 1 if the asteroid is intercepted, and 0 otherwise
 */
char asteroid_intercept(
        void* asteroid,
        const float x,
        const float y)
{
    int time = ((int*) asteroid)[0];

    if (time == ASTEROID_CLEARED_VALUE)
        return 1;

    float tolerance = ((float*) asteroid)[1];

    int intercepted = asteroid_distance(asteroid, x, y) <= tolerance;

    if (intercepted)
    {
        ((int*) asteroid)[0] = ASTEROID_CLEARED_VALUE;
    }

    return intercepted;
}

/*
 * asteroid_distance
 * :: void* asteroid ::
 * :: float x        ::
 * :: float y        ::
 * Returns the distance between the asteroid and x, y. 
 */
float asteroid_distance(
        void* asteroid,
        const float x,
        const float y)
{
    int time = ((int*) asteroid)[0];

    int fx_args_count = ((int*) asteroid)[2];

    void* x_polynomial = (void*) ((int*) asteroid + 2);
    float asteroid_x_pos = polynomial_evaluate(x_polynomial, time);

    void* y_polynomial = (void*) ((int*) asteroid + 3 + fx_args_count);
    float asteroid_y_pos = polynomial_evaluate(y_polynomial, time);

    float dx = asteroid_x_pos - x;
    float dy = asteroid_y_pos - y;

    return flatland_sqrt((dx * dx) + (dy * dy));
}
