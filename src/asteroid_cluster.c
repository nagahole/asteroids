#include "asteroid_cluster.h"
#include <stdio.h>
#include "flatland.h"

/*
 * asteroid_cluster_create
 * Creates an asteroid cluster at the location of the first argument
 * :: void* data            :: The location of the cluster
 * :: const int n_asteroids :: The maximum number of asteroids in this cluster
 * :: const float tolerance :: The tolerance of all asteroids in this cluster
 * 
 * Formatting of asteroid clusters:
 * - First 4 bytes: Tolerance of all the asteroids in the cluster
 * - Second 4 bytes: The number of asteroids there are
 * - Next chunks of 4 bytes: Asteroid data
 */
void asteroid_cluster_create(
        void* data,
        const int n_asteroids,
        const float tolerance)
{
    ((float*) data)[0] = tolerance;
    ((int*) data)[1] = n_asteroids;

    //Number of actual asteroids stored - not *max* number of asteroids possible
    ((int*) data)[2] = 0; 
}

/*
 * asteroid_cluster_add_asteroid
 * Adds an asteroid to the cluster
 * :: void* cluster :: The cluster to add the asteroid to
 * :: void* poly_x  :: X polynomial for the asteroid
 * :: void* poly_y  :: Y polynomial for the asteroid
 * Acts in place, updating the cluster
 */
void asteroid_cluster_add_asteroid(void* cluster, void* poly_x, void* poly_y)
{
    int arr[SIZEOF_ASTEROID / 4]; //Helper array to help allocate space for the void pointer
    void* asteroid = &arr;

    asteroid_create(asteroid, ((float*) cluster)[0], poly_x, poly_y);

    int asteroids_stored = ((int*) cluster)[2];
    ((int*) cluster)[2]++;

    // divide by 4 to get offset in chunks of 4 bytes
    int offset = 3 + (asteroids_stored * (SIZEOF_ASTEROID / 4)); 

    int fx_args_count = ((int*) poly_x)[0];
    int fy_args_count = ((int*) poly_y)[0];

    //Basically memcpy
    for (int i = 0; i < 4 + fx_args_count + fy_args_count; i++) 
    {
        // Even if the type isn't correct, the bits are still copied over correctly anyways
        // Can use int too. Just need a 4 byte type
        ((float*) cluster)[offset + i] = ((float*) asteroid)[i];

    }
}

/*
 * int asteroid_cluster_clear
 * Checks if the cluster of asteroids has been cleared
 * :: void* asteroids :: Pointer to the asteroid cluster
 * Returns 1 if all asteroids are clear
 * Returns 0 otherwise
 */
int asteroid_cluster_clear(void* asteroids)
{
    int asteroids_count = ((int*) asteroids)[2];

    // time, stored at index 0, has the information of whether an asteroid is cleared or not
    for(int i = 0; i < asteroids_count; i++) 
    {
        int time = ((int*) asteroids)[3 + (i * SIZEOF_ASTEROID / 4)];

        if (time != ASTEROID_CLEARED_VALUE)
            return 0;
    }

    return 1;
}

/*
 * asteroid_cluster_scan
 * Performs a scan on the asteroid cluster from a point 
 * :: void* cluster :: The cluster
 * :: const float x :: X position of the scanner
 * :: const float y :: Y position of the scanner
 * Returns the minimum distance between any asteroid in the cluster and the scanner.
 * Returns INF if the distance is greater than 1000
 * Returns NaN if an asteroid has impacted
 */
float asteroid_cluster_scan(void* cluster, const float x, const float y)
{
    int asteroids_count = ((int*) cluster)[2];

    float closest_distance = -1;
    float closest_ast[2] = { -1, -1 };

    for(int i = 0; i < asteroids_count; i++) 
    {
        // offset for location of the current asteroid iter's position relative
        // to the void pointer
        int offset = (i * SIZEOF_ASTEROID / 4) + 3;
        // +3 accounts for the 3 values stored in the cluster

        int time = ((int*) cluster)[offset];

        if (time != ASTEROID_CLEARED_VALUE) 
        { 
            //If asteroid not cleared, THEN check for position

            void* asteroid = (void*) (((int*) cluster) + offset); 

            if (asteroid_impact(asteroid))
            {
                return -(0.0/0.0);
            }

            void* polynomial_x = (void*) (((int*) cluster) + offset + 2);
            float asteroid_x_pos = polynomial_evaluate(polynomial_x, time);

            int fx_args_count = ((int*) cluster)[offset + 2];

            void* polynomial_y = (void*) (((int*) cluster) + offset + 3 + fx_args_count);
            float asteroid_y_pos = polynomial_evaluate(polynomial_y, time);

            float distance = flatland_dist(asteroid_x_pos, asteroid_y_pos, x, y);

            if (
                distance <= 1000 && 
                (distance < closest_distance || closest_distance == -1)
            ) 
            {
                closest_distance = distance;
                closest_ast[0] = asteroid_x_pos;
                closest_ast[1] = asteroid_y_pos;
            }
        }
    }

    if (closest_distance == -1) // IE no asteroids within 1000 units
        return 1.0 / 0.0; // inf
    else 
    {   
        //DEBUG_PRINT("[%f, %f] Actual Pos\n", closest_ast[0], closest_ast[1]);
        return closest_distance;
    }
}


/*
 * void asteroid_cluster_intercept
 * Checks if a given x, y coordinate intercepts with any of the asteroids in the cluster
 * :: void* cluster :: Pointer to cluster of asteroids
 * :: const float x :: x coordinate to attempt to intercept 
 * :: const float y :: y coordinate to attempt to intercept
 * Returns nothing
 */
void asteroid_cluster_intercept(
        void* asteroids,
        const float x,
        const float y)
{
    asteroid_cluster_update(asteroids);

    DEBUG_PRINT("Intercepting at [%f, %f]\n", x, y);

    float tolerance = ((float*) asteroids)[0];
    int asteroids_count = ((int*) asteroids)[2];

    for(int i = 0; i < asteroids_count; i++) 
    {
        // offset for location of the current asteroid iter's position relative
        // to the void pointer
        int offset = (i * SIZEOF_ASTEROID / 4) + 3;
        // +3 accounts for the 3 values stored in the cluster

        int time = ((int*) asteroids)[offset];

        if (time != ASTEROID_CLEARED_VALUE) 
        { 
            //If asteroid not cleared, THEN check for position

            void* polynomial_x = (void*) (((int*) asteroids) + offset + 2);
            float asteroid_x_pos = polynomial_evaluate(polynomial_x, time);

            int fx_args_count = ((int*) asteroids)[offset + 2];

            void* polynomial_y = (void*) (((int*) asteroids) + offset + 3 + fx_args_count);
            float asteroid_y_pos = polynomial_evaluate(polynomial_y, time);

            float distance = flatland_dist(asteroid_x_pos, asteroid_y_pos, x, y);

            if (distance <= tolerance)
            {
                //Sets time to asteroid_cleared_value
                DEBUG_PRINT("HIT!\n");
                ((int*) asteroids)[offset + 0] = ASTEROID_CLEARED_VALUE;
            }
        }
    }
}

/*
 * asteroid_cluster_impact
 * Checks if any asteroid has impacted at y <= 0
 * :: void* cluster :: Pointer to the cluster
 * Returns 1 if an impact has occurred, 0 otherwise
 */
int asteroid_cluster_impact(void* cluster)
{
    int asteroids_count = ((int*) cluster)[2];

    for(int i = 0; i < asteroids_count; i++) 
    {
        // offset for location of the current asteroid iter's position relative
        // to the void pointer
        int offset = (i * SIZEOF_ASTEROID / 4) + 3;
        // +3 accounts for the 3 values stored in the cluster

        int time = ((int*) cluster)[offset];

        if (time != ASTEROID_CLEARED_VALUE) 
        { 
            //If asteroid not cleared, THEN check for position

            int fx_args_count = ((int*) cluster)[offset + 2];

            void* polynomial_y = (void*) (((int*) cluster) + offset + 3 + fx_args_count);
            float asteroid_y_pos = polynomial_evaluate(polynomial_y, time);

            if (asteroid_y_pos <= 0)
                return 1;
        }
    }

    return 0;
}

/*
 * void asteroid_cluster_update
 * Updates the position of all asteroids in the cluster
 * :: void* cluster :: Pointer to asteroid cluster object
 * Returns nothing, all updates occur in place
 */
void asteroid_cluster_update(void* cluster)
{
    int asteroids_count = ((int*) cluster)[2];

    for(int i = 0; i < asteroids_count; i++) 
    {
        // offset for location of the current asteroid iter's position relative
        // to the void pointer
        int offset = (i * SIZEOF_ASTEROID / 4) + 3;
        // +3 accounts for the 3 values stored in the cluster

        int time = ((int*) cluster)[offset];

        if (time != ASTEROID_CLEARED_VALUE) 
        { 
            //If asteroid not cleared, THEN update position

            void* asteroid = (void*) (((int*) cluster) + offset); 

            asteroid_update(asteroid);
        }
    }
}

/*
 * get_tolerance
 * Gets the tolerance of an asteroid cluster
 * :: void* cluster :: Pointer to cluster
 * Returns the tolernace of all asteroids in that cluster
 */
float get_tolerance(void* cluster) 
{
    return ((float*) cluster)[0];
}
