#include "shape.h"

Shape::Shape()
{

}

Shape::Shape(float m)
{
    dim1 = dim2 = m;
}

Shape::Shape(float m, float n)
{
    dim1 = m;
    dim2 = n;
}

void Shape::SetD1(float m)
{
    dim1 = m;
}

void Shape::SetD2(float n)
{
    dim2 = n;
}

float Shape::GetD1()
{
    return dim1;
}

float Shape::GetD2()
{
    return dim2;
}
