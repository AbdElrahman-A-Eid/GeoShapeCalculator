#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "shape.h"
#include "rect.h"
#include "circle.h"
#include "triangle.h"
#include "square.h"
#include "geoshape.h"
#include "colorize.h"

using namespace std;

GeoShape::GeoShape(int shCount, Shape** shArr)
{
    Count = shCount;
    ShArr = new Shape*[shCount];
    for (int i = 0; i < shCount; i++)
    {
        ShArr[i] = shArr[i];
    }
}

GeoShape::GeoShape(GeoShape& rg)
{
    Count = rg.Count;
    ShArr = new Shape*[Count];
    for (int i = 0; i < Count; i++)
    {
        ShArr[i] = rg.ShArr[i];
    }
}

GeoShape::~GeoShape()
{
    for (int i = 0; i < Count; i++)
    {
        delete(ShArr+i);
    }
    delete (ShArr);
    setColor("W");
    cout << "The GeoShape consisting of " << Count << " shape(s) is Destroyed!" << endl;
    setColor("S");
}

GeoShape GeoShape::operator=(GeoShape g)
{
    Count = g.Count;
    ShArr = new Shape*[Count];
    for (int i = 0; i < Count; i++)
    {
        ShArr[i] = g.ShArr[i];
    }
    return *this;
}

int GeoShape::GetCount()
{
    return Count;
}

void GeoShape::SetShArr (Shape* shPtr, int shID)
{
    ShArr[shID] = shPtr;
}

Shape* GeoShape::GetShArr(int i)
{
    Shape* shPtr;
    shPtr = ShArr[i];
    return shPtr;
}

float GeoShape::TotalArea()
{
    float Total = 0;
    for (int i = 0; i < Count; i++)
    {
        Total += ShArr[i]->Area();
    }
    return Total;
}
