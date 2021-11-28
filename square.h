#ifndef SQAURE_H_
#define SQAURE_H_

#include "rect.h"

class Square:public Rect
{
public:
    Square(float m):Rect(m, m){};
    char Type();
};

#endif

