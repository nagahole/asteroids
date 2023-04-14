#include "maths.h"
#include "flatland.h"
#include <stdio.h>

#define SQRT_PRECISION 10000
#define SIN_PRECISION 2 * 10000

double flatland_dist(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    return flatland_sqrt(dx * dx + dy * dy);
}

double flatland_sin(float x)
{
    double res = 0;
    double sign = 1;

    for (int power = 1; power <= SIN_PRECISION; power += 2, sign = -sign) 
    {
        res += sign * (flatland_pow(x, power) / flatland_factorial(power));
    }

    return res;

    return x;
}

double flatland_cos(float x)
{
    return flatland_sin(x + PI / 2);
}

double flatland_sqrt(float x)
{
    if (x == 0.0) 
    {
        return 0.0;
    }

    if (x < 0)
    {
        return -(0.0 / 0.0);
    }

    double r = x / 2;

    for ( int i = 0; i < SQRT_PRECISION; i++ ) 
    {
            r = (r + x / r) / 2;
    }

    return r;
}

double flatland_pow(float base, int power) 
{
    float absolute = 1;

    for (int i = 0; i < flatland_abs(power); i++) 
    {
        absolute *= base;
    }

    if (power < 0)
        return 1.0 / absolute;
    else
        return absolute;
}

double flatland_abs(float n) 
{
    if (n > 0)
        return n;
    else
        return -n;
}

double flatland_factorial(int n) 
{
    double res = 1;

    for (int i = n; i > 0; i--) {
        res *= i;
    }

    return res;
}