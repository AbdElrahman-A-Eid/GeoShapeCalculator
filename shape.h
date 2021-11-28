#ifndef SHAPE_H_
#define SHAPE_H_

class Shape
{
protected:
    float dim1, dim2;
public:
    Shape();
    Shape(float m);
    Shape(float m, float n);
    void SetD1(float m);
    void SetD2(float n);
    float GetD1();
    float GetD2();
    virtual float Area() = 0;
    virtual char Type() = 0;
};

#endif
