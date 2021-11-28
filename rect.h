#ifndef RECT_H_
#define RECT_H_

#include "shape.h"

class Rect:public Shape
{
public:
    Rect(float m, float n):Shape(m, n){};
    float Area();
    char Type();
};

#endif
