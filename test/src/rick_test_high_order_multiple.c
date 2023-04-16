#include "rick_test_high_order_multiple.h"

int main()
{
    test_high_order_multiple();
    return 0;
}
 
#define N_AST 2
#define TOLERANCE 1
#define N_SCANNER_POSITIONS 5
#define N_COEFFICIENTS 10
int test_high_order_multiple()
{
    char data[SIZEOF_ASTEROID_CLUSTER(N_AST)];
    asteroid_cluster_create(data, N_AST, TOLERANCE); 

    // Asteroid 1
    void* poly_x[SIZEOF_POLYNOMIAL(N_COEFFICIENTS)];
    float elements_x[N_COEFFICIENTS] = { 0, 0, 0, 0, 0, 0, 1, -1, 20, 0 };
    polynomial_create(poly_x, N_COEFFICIENTS, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(N_COEFFICIENTS)];
    float elements_y[N_COEFFICIENTS] = { -0.0000835, 0.00118, -0.0033, -0.0101, 0.025, 0.0005, 0.1, -0.2, 0.05, 1000 };
    polynomial_create(poly_y, N_COEFFICIENTS, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    // Asteroid 2
    elements_x[0] = 0;
    elements_x[1] = 0;
    elements_x[2] = 0;
    elements_x[3] = 0;
    elements_x[4] = 0;
    elements_x[5] = 0;
    elements_x[6] = 0;
    elements_x[7] = -0.02;
    elements_x[8] = 1;
    elements_x[9] = 0;
    polynomial_create(poly_x, N_COEFFICIENTS, elements_x);

    elements_y[0] = 0;
    elements_y[1] = 0;
    elements_y[2] = 0;
    elements_y[3] = 0;
    elements_y[4] = -0.002;
    elements_y[5] = 0.1;
    elements_y[6] = -1.25;
    elements_y[7] = 0.8;
    elements_y[8] = -25;
    elements_y[9] = 1000;
    polynomial_create(poly_y, N_COEFFICIENTS, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    //////////////

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS)];
    float scanner_pos[N_SCANNER_POSITIONS] = {0, 200, 400, 600, 800}; 
    scanner_create(scanner, N_SCANNER_POSITIONS, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}