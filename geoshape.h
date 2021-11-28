#ifndef GEOSHAPE_H_
#define GEOSHAPE_H_

class GeoShape
{
    int Count;
    Shape** ShArr;
public:
    GeoShape(int shCount, Shape** shArr);
    GeoShape(GeoShape& rg);
    ~GeoShape();
    GeoShape operator=(GeoShape g);
    int GetCount();
    void SetShArr (Shape* shPtr, int shID);
    Shape* GetShArr(int i);
    float TotalArea();
};

#endif
