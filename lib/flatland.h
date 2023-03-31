#ifndef FLATLAND_H
#define FLATLAND_H 1

#ifdef DEBUG
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...) 
#endif

#include "scanner.h"
#include "asteroid_cluster.h"

/*
 * flatland_protect
 * Core function, attempts to use the scanner to clear the cluster
 * :: void* cluster :: Cluster of asteroids heading for flatland
 * :: void* scanner :: Asteroid detecting scanner.
 * Acts in place to clear the asteroids.
 */
void flatland_protect(void* cluster, void* scanner);

typedef struct 
{
    float x;
    float y;
} vector2;

/*
 * triangulate
 * Returns 1 if there is a point of intersection between the two scans
 * else 0
 */
int triangulate(float s1_pos, float s1_dist, float s2_pos, float s2_dist, vector2* res);

#endif
