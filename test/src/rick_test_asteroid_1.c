#include "rick_test_asteroid.h"

int main()
{
    test_asteroid_quadratic();
    return 0;
}

#define N_COEFFICIENTS 3
#define N_AST 1
#define TOLERANCE 1E-5
#define TEST_ITERATIONS 10

void test_asteroid_quadratic()
{
    // Asteroid follows y = x^2 + 1 path, where x = time
    // Create cluster object
    char data[SIZEOF_ASTEROID_CLUSTER(N_AST)];
    asteroid_cluster_create(data, N_AST, TOLERANCE); 

    // Create Polynomial
    char poly_y[SIZEOF_POLYNOMIAL(N_COEFFICIENTS)];
    float poly_y_vals[N_COEFFICIENTS] = { 1, 2, 4 };
    polynomial_create(poly_y, N_COEFFICIENTS, poly_y_vals);

    char poly_x[SIZEOF_POLYNOMIAL(N_COEFFICIENTS)];
    float poly_x_vals[N_COEFFICIENTS] = { 1, 1, 1 };
    polynomial_create(poly_x, N_COEFFICIENTS, poly_x_vals);

    // Add asteroid to cluster
    asteroid_cluster_add_asteroid(data, poly_x, poly_y); 

    assert(0 == asteroid_cluster_clear(data));

    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        float dist = asteroid_cluster_scan(
            data, 
            1 * (i * i) + 1 * (i) + 1, 
            1 * (i * i) + 2 * (i) + 4
        );

        assert(FLOAT_CMP(dist, 0.0, TOLERANCE));

        asteroid_cluster_update(data);
    }

    int iter = TEST_ITERATIONS + 1;

    // Try to shoot asteroid down
    asteroid_cluster_intercept(
        data, 
        iter * iter + iter + 1, 
        iter * iter + 2 * iter + 4
    );
    

    assert(1 == asteroid_cluster_clear(data));
    return;
}
