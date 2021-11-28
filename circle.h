#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "shape.h"

class Circle:public Shape
{
public:
    Circle(float r):Shape(r, r){};
    float Area();
    char Type();
};

#endif
