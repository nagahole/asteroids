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
    ((int*) data)[0] = n_scanners;

    for(int i = 0; i < n_scanners; i++) 
    {
        ((float*) data)[1 + i] = scanner_pos[i];
    }
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
    return ((int*) scanner)[0];
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
    return ((float*) scanner) + 1;
}


/*
 * scan
 * Performs a scan
 * :: void* scanner_array         :: Scanner object
 * :: void* asteroid_cluster :: Asteroid cluster to scan
 */
float* scan(
        void* scanners,
        void* asteroid_cluster)
{
    asteroid_cluster_update(asteroid_cluster);

    int scanners_count = ((int*) scanners)[0];

    for (int i = 0; i < scanners_count; i++) 
    {
        float scanner_x_pos = ((float*) scanners)[1 + i];
        float scan = asteroid_cluster_scan(asteroid_cluster, scanner_x_pos, 0);

        ((float*) scanners)[i + scanners_count + 1] = scan;
    }

    /*
     * I do not know any way around this. Right now what I'm doing is
     * making the size of scanner 2x its normal size, and allocating
     * the latter half of its memory to a distance array for scans
     */

    return ((float*) scanners) + scanners_count + 1;
}
