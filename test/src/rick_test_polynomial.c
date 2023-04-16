#include <stdio.h>
#include "test.h"
#include "polynomial.h"
#include "rick_test_polynomial.h"

int main()
{

    test_cubic();
    return 0;
}

int test_cubic()
{
    const float tolerance = 1E-5;

    void* poly[SIZEOF_POLYNOMIAL(4)];
    float elements[4] = { 1, 0, 0, 0 };
    polynomial_create(poly, 4, elements);

    for (int t = 0; t < 10; t++)
    {    
        float res = (t * t * t - polynomial_evaluate(poly, t));
        assert(res * res < tolerance); 
    }
    
    return 0;
}


