#include "rick_test_quadratic.h"

#define X_COEFFICIENTS { -1, 20, 500 }
#define Y_COEFFICIENTS { -1, 1, 1000 }
#define SCANNER_POSITIONS { 0, 200, 400, 600, 800 }

int main()
{
    test_quadratic();

    printf("Test passed!\n");
    return 0;
}

#define QUADRATIC_N_AST 1
#define TOLERANCE 5
#define N_SCANNER_POSITIONS 5
int test_quadratic()
{
    char data[SIZEOF_ASTEROID_CLUSTER(QUADRATIC_N_AST)];
    asteroid_cluster_create(data, QUADRATIC_N_AST, TOLERANCE); 

    void* poly_x[SIZEOF_POLYNOMIAL(3)];
    float elements_x[3] = X_COEFFICIENTS;
    polynomial_create(poly_x, 3, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(3)];
    float elements_y[3] = Y_COEFFICIENTS;
    polynomial_create(poly_y, 3, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS)];
    float scanner_pos[N_SCANNER_POSITIONS] = SCANNER_POSITIONS; 
    scanner_create(scanner, N_SCANNER_POSITIONS, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}