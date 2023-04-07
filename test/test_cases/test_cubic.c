#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"
#include "polynomial.h"
#include "test_cubic.h"

#define N_RANDOM_TESTS 10

int main()
{
    srand(time(NULL));
    float x_coeffs[4] = { 0, 0, 3, 0 };
    float y_coeffs[4] = { -0.00007, 0.009, 0, 1000 };
    test_cubic(x_coeffs, y_coeffs);

    for(int i = 0; i < N_RANDOM_TESTS; i++)
    {

        x_coeffs[0] = n_random() * 0.001;
        x_coeffs[1] = n_random() * 0.01;
        x_coeffs[2] = n_random() * 0.1;
        x_coeffs[3] = n_random() * 1;

        y_coeffs[0] = n_random() * -0.00001;
        y_coeffs[1] = n_random() * 0.01 - 0.005;
        y_coeffs[2] = n_random() * 10 - 0.5;
        y_coeffs[3] = n_random() * 50 + 100;

        test_cubic(x_coeffs, y_coeffs);
    }

    printf("Test passed!\n");
    return 0;
}

double n_random()
{
    return (double) rand() / RAND_MAX;
}

#define QUADRATIC_N_AST 1
#define TOLERANCE 1
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