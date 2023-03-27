#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"
#include "polynomial.h"
#include "test_quadratic.h"

int main()
{
    srand(time(NULL));
    test_quadratic();
    test_quadratic_random();
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
int test_quadratic()
{
    char data[SIZEOF_ASTEROID_CLUSTER(QUADRATIC_N_AST)];
    asteroid_cluster_create(data, QUADRATIC_N_AST, TOLERANCE); 

    void* poly_x[SIZEOF_POLYNOMIAL(3)];
    float elements_x[3] = {1, -4, 20};
    polynomial_create(poly_x, 3, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(3)];
    float elements_y[3] = {-1, 2, 1000};
    polynomial_create(poly_y, 3, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS_LINEAR)];
    float scanner_pos[N_SCANNER_POSITIONS_LINEAR] = {0, 200, 400, 600, 800}; 
    scanner_create(scanner, N_SCANNER_POSITIONS_LINEAR, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}

int test_quadratic_random()
{
    char data[SIZEOF_ASTEROID_CLUSTER(QUADRATIC_N_AST)];
    asteroid_cluster_create(data, QUADRATIC_N_AST, TOLERANCE); 

    void* poly_x[SIZEOF_POLYNOMIAL(3)];
    float elements_x[3] = {n_random() * 2, n_random() * 8 - 4, n_random() * 200};
    polynomial_create(poly_x, 3, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(3)];
    float elements_y[3] = {n_random() * -3, n_random() * 10, 1000};
    polynomial_create(poly_y, 3, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS_LINEAR)];
    float scanner_pos[N_SCANNER_POSITIONS_LINEAR] = {0, 200, 400, 600, 800}; 
    scanner_create(scanner, N_SCANNER_POSITIONS_LINEAR, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}