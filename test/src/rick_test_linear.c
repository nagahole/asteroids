#include "rick_test_linear.h"

#define X_COEFFICIENTS {1, 0}
#define Y_COEFFICIENTS {-2, 1000}
#define SCANNER_POSITIONS {0, 50, 100, 150, 200}

int main()
{
    test_linear();
    printf("Test passed!\n");
    return 0;
}

/*
 * Simple y = 1000 - x trajectory
 */ 
#define LINEAR_N_AST 1
#define TOLERANCE 1
#define N_SCANNER_POSITIONS 5
int test_linear()
{
    char data[SIZEOF_ASTEROID_CLUSTER(LINEAR_N_AST)];
    asteroid_cluster_create(data, LINEAR_N_AST, TOLERANCE); 

    void* poly_x[SIZEOF_POLYNOMIAL(2)];
    float elements_x[2] = X_COEFFICIENTS;
    polynomial_create(poly_x, 2, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(2)];
    float elements_y[2] = Y_COEFFICIENTS;
    polynomial_create(poly_y, 2, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS)];
    float scanner_pos[N_SCANNER_POSITIONS] = SCANNER_POSITIONS; 
    scanner_create(scanner, N_SCANNER_POSITIONS, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}