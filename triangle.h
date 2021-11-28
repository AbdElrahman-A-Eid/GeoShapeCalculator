#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "shape.h"

class Triangle:public Shape
{
public:
    Triangle(float b, float h):Shape(b, h){};
    float Area();
    char Type();
};

#endif
