#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"
#include "polynomial.h"
#include "test_cubic.h"

int main()
{
    srand(time(NULL));
    float x_coeffs[4] = {0.2, 1, 4, 2};
    float y_coeffs[4] = {-1, 2, -5, 1000};
    test_cubic(x_coeffs, y_coeffs);
    printf("Test passed!\n");
    return 0;
}

double n_random()
{
    return (double) rand() / RAND_MAX;
}

#define QUADRATIC_N_AST 1
#define TOLERANCE 5
#define N_SCANNER_POSITIONS_LINEAR 5
int test_cubic(float* x_coeffs, float* y_coeffs)
{
    char data[SIZEOF_ASTEROID_CLUSTER(QUADRATIC_N_AST)];
    asteroid_cluster_create(data, QUADRATIC_N_AST, TOLERANCE); 

    void* poly_x[SIZEOF_POLYNOMIAL(4)];
    float* elements_x = x_coeffs;
    polynomial_create(poly_x, 4, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(4)];
    float* elements_y = y_coeffs;
    polynomial_create(poly_y, 4, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS_LINEAR)];
    float scanner_pos[N_SCANNER_POSITIONS_LINEAR] = {0, 200, 400, 600, 800}; 
    scanner_create(scanner, N_SCANNER_POSITIONS_LINEAR, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}