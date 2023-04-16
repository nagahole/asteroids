#include "rick_test_scanner.h"

#define POLY_COEFFICIENTS 1
#define N_AST 100
#define TOLERANCE 1E-5
#define N_SCANNERS 100
#define SCANNER_GAP 10

int main()
{
    test_scanner();
    return 0;
}

void test_scanner()
{
    // Series of asteroids 100 directly above each scanner
    // Create cluster object
    char cluster[SIZEOF_ASTEROID_CLUSTER(N_AST)];
    asteroid_cluster_create(cluster, N_AST, TOLERANCE); 

    // Create Polynomial
    char poly_x[SIZEOF_POLYNOMIAL(POLY_COEFFICIENTS)];
    float poly_x_vals[POLY_COEFFICIENTS];

    char poly_y[SIZEOF_POLYNOMIAL(POLY_COEFFICIENTS)];
    float poly_y_vals[POLY_COEFFICIENTS] = { 100 };
    polynomial_create(poly_y, POLY_COEFFICIENTS, poly_y_vals);

    for (int i = 0; i < N_AST; i++)
    {
        poly_x_vals[0] = i * SCANNER_GAP;
        polynomial_create(poly_x, POLY_COEFFICIENTS, poly_x_vals);

        // Add asteroid to cluster
        // Use previously created polynomial
        asteroid_cluster_add_asteroid(cluster, poly_x, poly_y); 
    }
    
    assert(0 == asteroid_cluster_clear(cluster));
 
    // Create the scanner
    char scanner[SIZEOF_SCANNER(N_SCANNERS)];
    float scanner_pos[N_SCANNERS];

    for (int i = 0; i < N_SCANNERS; i++)
    {
        scanner_pos[i] = i * SCANNER_GAP;
    }

    scanner_create(scanner, N_SCANNERS, scanner_pos); 

    // Scan
    float* dist = scan(scanner, cluster);
   
    // Check the output 
    for(int i = 0; i < N_SCANNERS; i++)
    {
        assert(FLOAT_CMP(dist[i], 100, TOLERANCE));
    }

    return;
}
