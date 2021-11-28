#include "triangle.h"

float Triangle::Area()
{
    return 0.5 * dim1 * dim2;
}

char Triangle::Type()
{
    return 't';
}
