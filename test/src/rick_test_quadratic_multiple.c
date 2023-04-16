#include "rick_test_linear_multiple.h"

int main()
{
    test_linear_multiple();
    printf("Test passed!\n");
    return 0;
}
 
#define LINEAR_N_AST 3
#define TOLERANCE 1
#define N_SCANNER_POSITIONS 5
int test_linear_multiple()
{
    char data[SIZEOF_ASTEROID_CLUSTER(LINEAR_N_AST)];
    asteroid_cluster_create(data, LINEAR_N_AST, TOLERANCE); 

    // Asteroid 1
    void* poly_x[SIZEOF_POLYNOMIAL(3)];
    float elements_x[3] = { -1, 20, 500 };
    polynomial_create(poly_x, 2, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(3)];
    float elements_y[3] = { -1, 1, 1000};
    polynomial_create(poly_y, 2, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    // Asteroid 2
    elements_x[0] = 1;
    elements_x[1] = -5;
    elements_x[2] = 100;
    polynomial_create(poly_x, 2, elements_x);

    elements_y[0] = 1;
    elements_y[1] = -70;
    elements_y[2] = 1000;
    polynomial_create(poly_y, 2, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    //////////////

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS)];
    float scanner_pos[N_SCANNER_POSITIONS] = {0, 200, 400, 600, 800}; 
    scanner_create(scanner, N_SCANNER_POSITIONS, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}