#include <stdio.h>
#include "test.h"
#include "polynomial.h"
#include "rick_test_polynomial.h"

int main()
{
    test_polynomial();
    return 0;
}

int test_polynomial()
{
    const float tolerance = 1E-5;

    void* poly[SIZEOF_POLYNOMIAL(4)];
    float elements[4] = { 2, 4, 6, 8 };
    polynomial_create(poly, 4, elements);

    for (int t = 0; t < 10; t++)
    {    
        float res = (2 * (t * t * t) + 4 * (t * t) + 6 * (t) + 8 - polynomial_evaluate(poly, t));
        assert(res * res < tolerance); 
    }
    
    return 0;
}


