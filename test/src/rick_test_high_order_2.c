#include "rick_test_high_order.h"

#define POLY_SIZE 10
#define X_COEFFICIENTS { 0, 0, 0, 0, 0, 0, 1, -1, 20, 0 }
#define Y_COEFFICIENTS { -0.0000835, 0.00118, -0.0033, -0.0101, 0.025, 0.0005, 0.1, -0.2, 0.05, 1000 }
#define SCANNER_POSITIONS { 0, 200, 400, 600, 800 }

int main()
{
    test_high_order();

    printf("Test passed!\n");
    return 0;
}

#define HIGH_ORDER_N_AST 1
#define TOLERANCE 1
#define N_SCANNER_POSITIONS 5
int test_high_order()
{

    char data[SIZEOF_ASTEROID_CLUSTER(HIGH_ORDER_N_AST)];
    asteroid_cluster_create(data, HIGH_ORDER_N_AST, TOLERANCE); 

    void* poly_x[SIZEOF_POLYNOMIAL(POLY_SIZE)];
    float elements_x[POLY_SIZE] = X_COEFFICIENTS;
    polynomial_create(poly_x, POLY_SIZE, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(POLY_SIZE)];
    float elements_y[POLY_SIZE] = Y_COEFFICIENTS;
    polynomial_create(poly_y, POLY_SIZE, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS)];
    float scanner_pos[N_SCANNER_POSITIONS] = SCANNER_POSITIONS; 
    scanner_create(scanner, N_SCANNER_POSITIONS, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}