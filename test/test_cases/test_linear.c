#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"
#include "polynomial.h"
#include "test_linear.h"

int main()
{
    srand(time(NULL));
    test_linear();
    test_linear_random();
    printf("Test passed!\n");
    return 0;
}

double n_random()
{
    int r = rand();
    return (double) r / RAND_MAX;
}

/*
 * Simple y = 1000 - x trajectory
 */ 
#define LINEAR_N_AST 1
#define TOLERANCE 1
#define N_SCANNER_POSITIONS_LINEAR 5
int test_linear()
{
    char data[SIZEOF_ASTEROID_CLUSTER(LINEAR_N_AST)];
    asteroid_cluster_create(data, LINEAR_N_AST, TOLERANCE); 

    void* poly_x[SIZEOF_POLYNOMIAL(2)];
    float elements_x[2] = {1, 0};
    polynomial_create(poly_x, 2, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(2)];
    float elements_y[2] = {-2, 1000};
    polynomial_create(poly_y, 2, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS_LINEAR)];
    float scanner_pos[N_SCANNER_POSITIONS_LINEAR] = {0, 50, 100, 150, 200}; 
    scanner_create(scanner, N_SCANNER_POSITIONS_LINEAR, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}

int test_linear_random()
{
    char data[SIZEOF_ASTEROID_CLUSTER(LINEAR_N_AST)];
    asteroid_cluster_create(data, LINEAR_N_AST, TOLERANCE); 

    void* poly_x[SIZEOF_POLYNOMIAL(2)];
    float elements_x[2] = {n_random() * 4 - 2, 0};
    polynomial_create(poly_x, 2, elements_x);

    void* poly_y[SIZEOF_POLYNOMIAL(2)];
    float elements_y[2] = {n_random() * -4 - 1, 1000};
    polynomial_create(poly_y, 2, elements_y);
    
    asteroid_cluster_add_asteroid(data, poly_x, poly_y);

    char scanner[SIZEOF_SCANNER(N_SCANNER_POSITIONS_LINEAR)];
    float scanner_pos[N_SCANNER_POSITIONS_LINEAR] = {0, 150, 300, 450, 600}; 
    scanner_create(scanner, N_SCANNER_POSITIONS_LINEAR, scanner_pos); 

    flatland_protect(data, scanner);

    assert(asteroid_cluster_impact(data) == 0);

    return 0;
}