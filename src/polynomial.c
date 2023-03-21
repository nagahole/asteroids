#include "polynomial.h"

/* polynomial_create
 */
void polynomial_create(
        void* data,
        int n_elements,
        float* elements)
{
    /* Data is in the format of: 
     * - First 4 bytes: int denoting number of coefficients
     * - Bytes in consecutive chunks of 4: Coefficients of elements
     */
    ((int*) data)[0] = n_elements;

    for (int i = 0; i < n_elements; i++) 
    {
        ((float*) data)[i + 1] = elements[i];
    }

    return;
}

/*
 * Polynomial evaluate
 */
float polynomial_evaluate(void* polynomial, int t)
{
    int n_elements = ((int*) polynomial)[0];

    float res = 0;

    for (int i = 0; i < n_elements; i++) 
    {
        float coefficient = ((float*) polynomial)[i + 1];
        float buf = coefficient;

        //Basically pow(polynomial[i + 1], n_elements - 1)
        for (int j = 0; j < n_elements - 2 - j; j++) {
            buf *= coefficient;
        }

        res += buf;
    }

    return res;
}
