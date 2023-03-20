#ifndef ASTEROID_CLUSTER_H
#define ASTEROID_CLUSTER_H

#include "asteroid.h"

#define SIZEOF_ASTEROID_CLUSTER(n) (sizeof(int) * 3 + sizeof(float) + n * sizeof(char) + n * SIZEOF_ASTEROID)

/*
 * asteroid_cluster_update
 * Updates asteroid positions in the cluster
 *  
 */
void asteroid_cluster_update(void* asteroids);

// Adds an asteroid to the cluster
void asteroid_cluster_add_asteroid(void* cluster, void* poly_x, void* poly_y);

// Initialises a new cluster at data
void asteroid_cluster_create(
        void* data,
        int n_asteroids,
        float tolerance
        );

// Checks if the cluster is empty, i.e. all asteroids intercepted
int asteroid_cluster_clear(void* asteroids);

// Checks if any asteroid has impacted at y=0
int asteroid_cluster_impact(void* asteroids);

// Scans the cluster from x, y 
float asteroid_cluster_scan(void* asteroids, float x, float y);

// Tries to intercept any asteroid at x, y
void asteroid_cluster_intercept(void* asteroids, float x, float y);

#endif
