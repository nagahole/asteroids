#include "asteroid_cluster.h"


void asteroid_cluster_create(
        void* data,
        int n_asteroids,
        float tolerance)
{
    // TODO
}

void asteroid_cluster_add_asteroid(void* cluster, void* poly_x, void* poly_y)
{
    // TODO
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
    // TODO
    return 0;
}

float asteroid_cluster_scan(void* asteroids, float x, float y)
{
    // TODO
    return 0;
}


/*
 * void asteroid_cluster_intercept
 * Checks if a given x, y coordinate intercepts with any of the asteroids in the cluster
 * :: void* asteroids :: Pointer to cluster of asteroids
 * :: float x :: x coordinate to attempt to intercept 
 * :: float y :: y coordinate to attempt to intercept
 * Returns nothing
 */
void asteroid_cluster_intercept(void* asteroids, float x, float y)
{
    // TODO
    return;
}

int asteroid_cluster_impact(void* asteroids)
{
    // TODO
    return 0;
}

/*
 * void asteroid_cluster_update
 * Updates the position of all asteroids in the cluster
 * :: void* asteroids :: Pointer to asteroid cluster object
 * Returns nothing, all updates occur in place
 */
void asteroid_cluster_update(void* asteroids)
{
    // TODO
    return;
}



