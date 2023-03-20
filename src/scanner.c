#include "scanner.h"
#define NULL ((void *) 0)

// Constructor
/*
 * scanner_create
 * Constructor for the scanner object
 * :: const int n_scanners :: number of scanner positions
 * :: scanner_pos :: X positions of the scanners 
 * All operations act in place
 */
void scanner_create(
        void* data,
        const int n_scanners,
        float* scanner_pos)
{
    // TODO
}

// Getters
/*
 * get_num_scanners
 * Gets the number of scanner positions in this scanner
 * 
 * :: void* scanner :: Pointer to the scanner object
 *
 */
int get_num_scanners(void* scanner)
{
    // TODO
    return 0;
}


/*
 * get_scanner_positions
 * Returns a pointer to an array of scanner positions
 * 
 * :: void* scanner :: Pointer to the scanner object
 *
 */
float* get_scanner_positions(void* scanner)
{
    // TODO
    return NULL;
}


/*
 * scan
 * Performs a scan, setting the distances in place
 *
 * :: void* scanners :: Pointer to a scanner object
 * :: void* asteroid_cluster :: Pointer to the cluster to scan
 * :: float* distances :: Array of distances to populate
 *
 * Acts in place, nothing is returned
 */
float* scan(
        void* scanners,
        void* asteroid_cluster)
{
    // TODO
    return NULL;
}
