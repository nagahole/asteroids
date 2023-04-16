#include "rick_test_cubic.h"

#define X_COEFFICIENTS { 0, -0.01, 1, 0 }
#define Y_COEFFICIENTS { -0.1, 2.5, -20, 1000 }
#define SCANNER_POSITIONS { 0, 200, 400, 600, 800 }

int main()
{
    test_cubic();
    return 0;
}

#define CUBIC_N_AST 1
#define TOLERANCE 1
#define N_SCANNER_POSITIONS 5
int test_cubic()
{
    char data[SIZEOF_ASTEROID_CLUSTER(CUBIC_N_AST)];
    asteroid_cluster_create(data, CUBIC_N_AST, TOLERANCE); 

    void* poly_x[SIZEOF_POLYNOMIAL(4)];
    float elements_x[4] = X_COEFFICIENTS;
    polynomial_create(poly_x, 4, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(4)];
    float elements_y[4] = Y_COEFFICIENTS;
    polynomial_create(poly_y, 4, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS)];
    float scanner_pos[N_SCANNER_POSITIONS] = SCANNER_POSITIONS; 
    scanner_create(scanner, N_SCANNER_POSITIONS, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}