#include "rick_test_quadratic_multiple.h"

int main()
{
    test_quadratic_multiple();
    return 0;
}
 
#define N_AST 2
#define TOLERANCE 1
#define N_SCANNER_POSITIONS 5
int test_quadratic_multiple()
{
    char data[SIZEOF_ASTEROID_CLUSTER(N_AST)];
    asteroid_cluster_create(data, N_AST, TOLERANCE); 

    // Asteroid 1
    void* poly_x[SIZEOF_POLYNOMIAL(3)];
    float elements_x[3] = { 0.5, 0, 50 };
    polynomial_create(poly_x, 3, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(3)];
    float elements_y[3] = { 1, -63.4, 1000};
    polynomial_create(poly_y, 3, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    // Asteroid 2
    elements_x[0] = -0.5;
    elements_x[1] = 25;
    elements_x[2] = 50;
    polynomial_create(poly_x, 3, elements_x);

    elements_y[0] = -0.5;
    elements_y[1] = 1;
    elements_y[2] = 1000;
    polynomial_create(poly_y, 3, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    //////////////

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS)];
    float scanner_pos[N_SCANNER_POSITIONS] = {0, 200, 400, 600, 800}; 
    scanner_create(scanner, N_SCANNER_POSITIONS, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}