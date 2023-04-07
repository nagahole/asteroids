#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"
#include "polynomial.h"
#include "test_high_order.h"

#define N_RANDOM_TESTS 10
#define ORDER 10

int main()
{
    srand(time(NULL));
    float x_coeffs[ORDER];
    float y_coeffs[ORDER];

    for(int i = 0; i < N_RANDOM_TESTS; i++)
    {

        for(int j = 0; j < ORDER; j++)
        {
            x_coeffs[j] = flatland_pow(10, 3 * j - 24) * n_random();
            y_coeffs[j] = flatland_pow(10, 2 * j - 20) * n_random();
        }

        y_coeffs[0] = (n_random() - 1.1) * flatland_pow(10, -10);
        y_coeffs[ORDER - 1] += 1000;

        test_high_order(x_coeffs, y_coeffs);
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
int test_high_order(float* x_coeffs, float* y_coeffs)
{
    DEBUG_PRINT("Y Coeffs: [");
    for(int i = 0; i < ORDER; i++)
    {
        DEBUG_PRINT("%f, ", y_coeffs[i]);
    }

    DEBUG_PRINT("\b\b]\n");
    DEBUG_PRINT("X Coeffs: [");

    for(int i = 0; i < ORDER; i++)
    {
        DEBUG_PRINT("%f, ", x_coeffs[i]);
    }

    DEBUG_PRINT("\b\b]\n");

    char data[SIZEOF_ASTEROID_CLUSTER(QUADRATIC_N_AST)];
    asteroid_cluster_create(data, QUADRATIC_N_AST, TOLERANCE); 

    void* poly_x[SIZEOF_POLYNOMIAL(ORDER)];
    float* elements_x = x_coeffs;
    polynomial_create(poly_x, ORDER, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(ORDER)];
    float* elements_y = y_coeffs;
    polynomial_create(poly_y, ORDER, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS_LINEAR)];
    float scanner_pos[N_SCANNER_POSITIONS_LINEAR] = {0, 200, 400, 600, 800}; 
    scanner_create(scanner, N_SCANNER_POSITIONS_LINEAR, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}