#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "colorize.h"

using namespace std;

class Shape
{
protected:
    float dim1, dim2;
public:

    Shape()
    {

    }
    Shape(float m)
    {
        dim1 = dim2 = m;
    }
    Shape(float m, float n)
    {
        dim1 = m;
        dim2 = n;
    }
    void SetD1(float m)
    {
        dim1 = m;
    }
    void SetD2(float n)
    {
        dim2 = n;
    }
    float GetD1()
    {
        return dim1;
    }
    float GetD2()
    {
        return dim2;
    }
    virtual float Area() = 0;
    virtual char Type() = 0;
};

class Rect:public Shape
{
public:
    Rect(float m, float n):Shape(m, n)
    {

    }
    float Area()
    {
        return 1.0 * dim1 * dim2;
    }
    char Type()
    {
        return 'r';
    }
};

class Circle:public Shape
{
public:
    Circle(float r):Shape(r, r)
    {

    }
    float Area()
    {
        return 3.14 * dim1 * dim2;
    }
    char Type()
    {
        return 'c';
    }
};

class Triangle:public Shape
{
public:
    Triangle(float b, float h):Shape(b, h)
    {

    }
    float Area()
    {
        return 0.5 * dim1 * dim2;
    }
    char Type()
    {
        return 't';
    }
};

class Square:public Rect
{
public:
    Square(float m):Rect(m, m)
    {

    }
    char Type()
    {
        return 's';
    }
};

class GeoShape
{
    int Count;
    Shape** ShArr;
public:
    GeoShape(int shCount, Shape** shArr)
    {
        Count = shCount;
        ShArr = new Shape*[shCount];
        for (int i = 0; i < shCount; i++)
        {
            ShArr[i] = shArr[i];
        }
    }
    GeoShape(GeoShape& rg)
    {
        Count = rg.Count;
        ShArr = new Shape*[Count];
        for (int i = 0; i < Count; i++)
        {
            ShArr[i] = rg.ShArr[i];
        }
    }
    ~GeoShape()
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
    GeoShape operator=(GeoShape g)
    {
        Count = g.Count;
        ShArr = new Shape*[Count];
        for (int i = 0; i < Count; i++)
        {
            ShArr[i] = g.ShArr[i];
        }
        return *this;
    }
    int GetCount()
    {
        return Count;
    }
    void SetShArr (Shape* shPtr, int shID)
    {
        ShArr[shID] = shPtr;
    }
    Shape* GetShArr(int i)
    {
        Shape* shPtr;
        shPtr = ShArr[i];
        return shPtr;
    }
    float TotalArea()
    {
        float Total = 0;
        for (int i = 0; i < Count; i++)
        {
            Total += ShArr[i]->Area();
        }
        return Total;
    }
};

#define Start 0

//void gotoxy(int column, int line);
int up(int currRow, int first, int last);
int down(int currRow, int first, int last);
void ShapeMenuNav(int& shFlag, int& shRow, Shape** shArr, int& index, int shIndex);
void ShapeMenu();
void FillShape(Shape** shArr, char shapeType, int shIndex);
void FillGeo(Shape** shArr, int& index, int shIndex);
void Add(int& index, GeoShape** GeoArr, int GeoCount);
void RepShape(GeoShape** GeoArr, int GeoCount, int& index);
void Replace(GeoShape** GeoArr, int GeoCount);
void DispShape(GeoShape** GeoArr, int ind, int i, int& dispRow, int shapeNo, int& totalRows, int& mod);
void DispGeo(GeoShape** GeoArr, int ind, int& totalRows);
void Disp(GeoShape** GeoArr, int& index);
void DispAll(GeoShape** GeoArr, int& index, int GeoCount);
void Exit(int& flag, GeoShape** GeoArr, int GeoCount);
void MenuNav(int& flag, int& currRow, int& index, GeoShape** GeoArr, int GeoCount);
void KeyInstruct();
void MenuInit();

int main()
{
    int flag = 1;
    int currRow = Start+7;

    int index = 0;

    int GeoCount;

    system("cls");

    setColor("H", 0, Start);
    cout << "**** GeoShape Calculator ****" << endl;

    setColor("p", 0, 2);
    cout << "Welcome!";

    setColor("IR", 9, 2);
    cout << "Please enter the number of GeoShapes you would like to generate: ";

    setColor("IV");
    cin >> GeoCount;

    GeoShape** GeoArr;
    GeoArr = new GeoShape*[GeoCount];

    if (GeoArr != NULL)
    {
        do
        {
            MenuInit();
            MenuNav(flag, currRow, index, GeoArr, GeoCount);
        }
        while (flag);

        for (int k = 0; k < index; k++)
        {
            delete(GeoArr[k]);
        }
        delete(GeoArr);
    }
    else
    {
        setColor("W", 9, 4);
        cout << "Error! Unable to allocate in memory.";
    }
    getch();
    return 0;
}

int down(int currRow, int first, int last)
{
    if (currRow < Start+last)
    {
        currRow++;
    }
    else
    {
        currRow = Start+first;
    }
    gotoxy(5, currRow);
    return currRow;
}

int up(int currRow, int first, int last)
{
    if (currRow > Start+first)
    {
        currRow--;
    }
    else
    {
        currRow = Start+last;
    }
    gotoxy(5, currRow);
    return currRow;
}

void ShapeMenuNav(int& shFlag, int& shRow, Shape** shArr, int& index, int shIndex)
{
    gotoxy(5, shRow);

    char ch = getch();

    if ((int)ch == -32)                 // Extended Keys
    {
        ch = getch();

        switch ((int)ch)
        {
        case 80:                        // Down Arrow Key
            shRow = down(shRow, 3, 6);
            break;
        case 72:                        // Up Arrow Key
            shRow = up(shRow, 3, 6);
            break;
        case 71:                        // Home Key
            shRow = 7;
            gotoxy(5, shRow);
            break;
        }
    }
    else if ((int)ch == 13)             // Enter Key
    {
        char shapeType;

        switch(shRow)
        {
        case Start+3:
            shFlag = 0;
            shapeType = 'r';
            break;
        case Start+4:
            shFlag = 0;
            shapeType = 's';
            break;
        case Start+5:
            shFlag = 0;
            shapeType = 't';
            break;
        case Start+6:
            shFlag = 0;
            shapeType = 'c';
            break;
        }
        FillShape(shArr, shapeType, shIndex);
    }
    else                                // Number Keys
    {

        switch(ch)
        {
        case '1':
            shRow = Start+3;
            gotoxy(5, shRow);
            break;
        case '2':
            shRow = Start+4;
            gotoxy(5, shRow);
            break;
        case '3':
            shRow = Start+5;
            gotoxy(5, shRow);
            break;
        case '4':
            shRow = Start+6;
            gotoxy(5, shRow);
            break;
        }
    }
}

void ShapeMenu()
{
    system("cls");

    setColor("H", 0, Start);
    cout << "---- Shape Selection Screen ----" << endl;

    setColor("IR", 0, Start+2);
    cout << "Please choose the shape you would like to create:" << endl;

    setColor("RP", 5, Start+3);

    cout << "1) Rectangle";

    gotoxy(5, Start+4);
    cout << "2) Square";

    gotoxy(5, Start+5);
    cout << "3) Triangle";

    gotoxy(5, Start+6);
    cout << "4) Circle" << endl;

}

void FillShape(Shape** shArr, char shapeType, int shIndex)
{
    system("cls");

    float d1, d2;
    int mod = 0;

    char shName[10];
    char shDim1[7];
    char shDim2[7];

    strcpy(shDim1, "");
    strcpy(shDim2, "");

    switch(shapeType)
    {
    case 'r':
        strcpy(shName, "Rectangle");
        strcpy(shDim1, "Length");
        strcpy(shDim2, "Width");
        break;
    case 's':
        strcpy(shName, "Square");
        strcpy(shDim1, "Side");
        break;
    case 't':
        strcpy(shName, "Triangle");
        strcpy(shDim1, "Base");
        strcpy(shDim2, "Height");
        break;
    case 'c':
        strcpy(shName, "Circle");
        strcpy(shDim1, "Radius");
        break;
    }

    setColor("H", 0, Start);
    cout << "---- " << shName << " Creation Screen ----" << endl;

    setColor("IR", 0, Start+2);
    cout << "Please enter the required data below:" << endl;

    setColor("B", 1, Start+3);
    cout << "{";

    setColor("AFI", 5, Start+4);
    cout << shDim1 << ": ";
    setColor("RP", 14, Start+4);
    cin >> d1;

    if (strlen(shDim2) > 3)
    {
        setColor("AFI", 5, Start+5);
        cout << shDim2 << ": ";
        setColor("RP", 14, Start+5);
        cin >> d2;

        setColor("B", 1, Start+6);
        cout << "}";
        mod = 1;
    }
    else
    {
        setColor("B", 1, Start+5);
        cout << "}";
    }

    if (shapeType == 'r')
    {
        shArr[shIndex] = new Rect(d1, d2);
    }
    else if (shapeType == 's')
    {
        shArr[shIndex] = new Square(d1);
    }
    else if (shapeType == 't')
    {
        shArr[shIndex] = new Triangle(d1, d2);
    }
    else if (shapeType == 'c')
    {
        shArr[shIndex] = new Circle(d1);
    }

    setColor("SM", 0, Start+7+mod);
    cout << "Your " << shName << " is created successfully!";
    getch();
}

void FillGeo(Shape** shArr, int& index, int shIndex)
{
    int shFlag = 1;
    int shRow = 3;
    while (shFlag)
    {
        ShapeMenu();
        ShapeMenuNav(shFlag, shRow, shArr, index, shIndex);
    }
}

void Add(int& index, GeoShape** GeoArr, int GeoCount)
{
    int shCount;

    system("cls");

    setColor("H", 0, Start);
    cout << "**** GeoShape Calculator ****" << endl;

    if (index < GeoCount)
    {
        setColor("p", 0, 2);
        cout << "Hi Again!";

        setColor("IR", 10, 2);
        cout << "Please enter the number of shapes you would like to create within this GeoShape: ";

        setColor("IV");
        cin >> shCount;

        Shape** shArr;
        shArr = new Shape*[shCount];

        for (int i = 0; i < shCount; i++)
        {
            FillGeo(shArr, index, i);
        }

        GeoArr[index] = new GeoShape(shCount, shArr);
        index++; // GeoShape Current Count
    }
    else
    {

        setColor("W", 0, 2);
        cout << "You have already populated all of the " << GeoCount << " GeoShapes!" << endl;

        setColor("IR", 0, 4);
        cout << "Would you like to replace/overwrite a specific GeoShape? (y/n) ";
        char answer;
        cin >> answer;

        if (tolower(answer) == 'n')
        {
            setColor("RP", 0, 6);
            cout << "You will be redirected to the main menu shortly...";
            Sleep(1500);
        }
        else if (tolower(answer) == 'y')
        {
            // Replace
            Replace(GeoArr, GeoCount);
        }
    }
}

void RepShape(GeoShape** GeoArr, int GeoCount, int& index)
{
    int i;
    int shID;
    system("cls");

    setColor("H", 0, Start);
    cout << "---- Shape Data Replacement Screen ----" << endl;

    setColor("IR", 0, 2);
    cout << "Please enter the GeoShape number to which the shape be replaced belongs: ";
    setColor("IV");
    cin >> i;
    i--;

    if (i < index)
    {
        setColor("p", 0, 4);
        cout << "Hi Again!";

        setColor("IR", 10, 4);
        cout << "Please enter the number of the shape you would like to replace within GeoShape no " << i+1 << ": ";

        setColor("IV");
        cin >> shID;
        shID--;

        int shCount = GeoArr[i]->GetCount();

        if (shID < shCount)
        {
            Shape** shptr;
            shptr = new Shape*[shCount];


            if (shptr != NULL)
            {

                for (int k = 0; k < shCount; k++)
                {
                    shptr[k] = GeoArr[i]->GetShArr(k);
                }

                FillGeo(shptr, i, shID);

                GeoArr[i]->SetShArr(shptr[shID], shID);

                delete(shptr);
                setColor("SM");
                cout << "\nShape no. " << shID+1 << " within GeoShape no. " << i+1 << " has been replaced successfully!" << endl;
                getch();
            }
            else
            {
                setColor("W", 9, 6);
                cout << "Error! Unable to allocate in memory.";
            }
        }
        else
        {
            setColor("W", 0, 6);
            cout << "You are trying to replace a shape with a number that doesn't exist within GeoShape no " << i+1 << "." << endl;
            setColor("RP", 0, 7);
            cout << "You will be redirected to the main menu shortly...";
            Sleep(2000);
        }
    }
    else
    {
        setColor("W", 0, 4);
        cout << "You are trying to replace a GeoShape with a number that doesn't exist.\n" << endl;
        setColor("RP", 0, 5);
        cout << "You will be redirected to the main menu shortly...";
        Sleep(2000);
    }
}

void Replace(GeoShape** GeoArr, int GeoCount)
{
    int i;
    int shCount;
    system("cls");

    setColor("H", 0, Start);
    cout << "---- GeoShape Data Replacement Screen ----" << endl;

    setColor("IR", 0, 2);
    cout << "Please enter the GeoShape number to be replaced: ";
    cin >> i;
    i--;

    if (i < GeoCount)
    {
        setColor("p", 0, 4);
        cout << "Hi Again!";

        setColor("IR", 10, 4);
        cout << "Please enter the number of shapes you would like to create within this GeoShape: ";

        setColor("IV");
        cin >> shCount;

        Shape** shArr;
        shArr = new Shape*[shCount];

        for (int j = 0; j < shCount; j++)
        {
            FillGeo(shArr, i, j);
        }

        GeoArr[i] = new GeoShape(shCount, shArr);

        setColor("SM");
        cout << "\nGeoShape no. " << i+1 << " has been replaced successfully! Now containing a total of " << shCount << " shapes!" << endl;
        getch();
    }
    else
    {
        setColor("W", 0, 4);
        cout << "You are trying to replace a GeoShape with a number that doesn't exist.\n" << endl;
        setColor("RP", 0, 5);
        cout << "You will be redirected to the main menu shortly...";
        Sleep(2000);
    }
}

void DispShape(GeoShape** GeoArr, int ind, int j, int& dispRow, int shapeNo, int& totalRows, int& mod)
{
    char shapeType;
    shapeType = GeoArr[ind]->GetShArr(j)->Type();

    char shName[10];
    char shDim1[7];
    char shDim2[7];

    strcpy(shDim1, "");
    strcpy(shDim2, "");

    switch(shapeType)
    {
    case 'r':
        strcpy(shName, "Rectangle");
        strcpy(shDim1, "Length");
        strcpy(shDim2, "Width");
        break;
    case 's':
        strcpy(shName, "Square");
        strcpy(shDim1, "Side");
        break;
    case 't':
        strcpy(shName, "Triangle");
        strcpy(shDim1, "Base");
        strcpy(shDim2, "Height");
        break;
    case 'c':
        strcpy(shName, "Circle");
        strcpy(shDim1, "Radius");
        break;
    }

    setColor("W", 4, dispRow);
    cout << "Shape no. " << j+1 << " (" << shName << ") in GeoShape no. " << ind+1 << ":" << endl;

    setColor("B", 5, dispRow+1);
    cout << "{";

    setColor("DI", 9, dispRow+2);
    cout << shDim1 << ": ";
    setColor("DV", 18, dispRow+2);
    cout << GeoArr[ind]->GetShArr(j)->GetD1();

    if (strlen(shDim2) > 3)
    {
        setColor("DI", 9, dispRow+3);
        cout << shDim2 << ": ";
        setColor("DV", 18, dispRow+3);
        cout << GeoArr[ind]->GetShArr(j)->GetD2();

        setColor("B", 5, dispRow+4);
        cout << "}";

        if (j+1 < shapeNo)
        {
            dispRow += 6;
            totalRows += 6;
        }
        mod = 1;
    }
    else
    {
        setColor("B", 5, dispRow+3);
        cout << "}";

        if (j+1 < shapeNo)
        {
            dispRow += 5;
            totalRows += 5;
        }
        else
        {
            mod = 0;
        }
    }
}

void DispGeo(GeoShape** GeoArr, int ind, int& totalRows)
{
    int mod = 0;
    int j;
    int shapeNo;
    shapeNo = GeoArr[ind]->GetCount();

    setColor("P", 0, totalRows-2);
    cout << "GeoShape no. " << ind+1 << " Data" << endl;

    setColor("W", 0, totalRows-1);
    cout << "{";

    int dispRow = totalRows;

    for (j = 0; j < shapeNo; j++)
    {
        DispShape(GeoArr, ind, j, dispRow, shapeNo, totalRows, mod);
    }

    setColor("IR", 4, totalRows+5+mod);
    cout << "Total area of the GeoShape component(s) is: " << GeoArr[ind]->TotalArea() << ".";

    setColor("W", 0, totalRows+6+mod);
    cout << "}" << endl;
    totalRows += (5+mod);

    setColor("SM", 10, totalRows+2);
    cout << "A total of " << shapeNo << " shape(s) are displayed successfully in GeoShape no. " << ind+1 << "!" << endl;
}

void Disp(GeoShape** GeoArr, int& index)
{
    int totalRows = 4;
    int ind;
    system("cls");
    setColor("H", 0, Start);
    cout << "**** GeoShape Calculator ****" << endl;

    setColor("IR", 0, 2);
    cout << "Please enter the number of the GeoShape to display: ";
    setColor("IV");
    cin >> ind;
    ind--;

    if (ind >= index)
    {
        setColor("W", 0, 4);
        cout << "There is no data inserted for the specified GeoShape yet." << endl;
        setColor("RP", 0, 5);
        cout << "You will be redirected to the main menu shortly...";
        Sleep(2000);
        return;
    }
    else
    {
        system("cls");
        setColor("H", 0, Start);
        cout << "---- GeoShape Data Display Screen ----";

        DispGeo(GeoArr, ind, totalRows);
        /*
                int shapeNo;
                shapeNo = GeoArr[ind]->GetCount();
                setColor("SM", 10, totalRows+3);
                cout << "A total of " << shapeNo << " shape(s) are displayed successfully in GeoShape no. " << ind+1 << "!" << endl;
        */
    }
    getch();
}

void DispAll(GeoShape** GeoArr, int& index, int GeoCount)
{
    int totalRows = 4;
    system("cls");
    if (index == 0)
    {
        setColor("W");
        cout << "\n\nThere is no data inserted for any GeoShape yet." << endl;
        setColor("RP");
        cout << "\nYou will be redirected to the main menu shortly...";
        Sleep(2000);
        return;
    }
    else
    {
        system("cls");
        setColor("H", 0, Start);
        cout << "---- GeoShapes Data Display Screen ----";

        for (int k = 0; k < index; k++)
        {
            DispGeo(GeoArr, k, totalRows);
            totalRows += 6;
        }

        setColor("p");
        cout << "\nA total of " << index << " GeoShape(s) are displayed successfully!" << endl;
        getch();
    }

}

void Exit(int& flag, GeoShape** GeoArr, int GeoCount)
{
    flag = 0;
    setColor("p");
    cout << "\n\n\tThank you for using my GeoShape Calculator! The program will exit...\n" << endl;

    setColor("IR");
    cout << "\tMy Regards" << endl;

    setColor("DI");
    cout << "\t- Piain" << endl;
    setColor("S");
}

void MenuNav(int& flag, int& currRow, int& index, GeoShape** GeoArr, int GeoCount)
{
    gotoxy(5, currRow);

    char ch = getch();

    if ((int)ch == -32)                 // Extended Keys
    {
        ch = getch();

        switch ((int)ch)
        {
        case 80:                        // Down Arrow Key
            currRow = down(currRow, 7, 11);
            break;
        case 72:                        // Up Arrow Key
            currRow = up(currRow, 7, 11);
            break;
        case 71:                        // Home Key
            currRow = 7;
            gotoxy(5, currRow);
            break;
        }
    }
    else if ((int)ch == 13)             // Enter Key
    {
        switch(currRow)
        {
        case Start+7:
            Add(index, GeoArr, GeoCount);
            break;
        case Start+8:
            RepShape(GeoArr, GeoCount, index);
            break;
        case Start+9:
            Disp(GeoArr, index);
            break;
        case Start+10:
            DispAll(GeoArr, index, GeoCount);
            break;
        case Start+11:
            Exit(flag, GeoArr, GeoCount);
            break;
        }
    }
    else                                // Number Keys
    {

        switch(ch)
        {
        case '1':
            currRow = Start+7;
            gotoxy(5, currRow);
            break;
        case '2':
            currRow = Start+8;
            gotoxy(5, currRow);
            break;
        case '3':
            currRow = Start+9;
            gotoxy(5, currRow);
            break;
        case '4':
            currRow = Start+10;
            gotoxy(5, currRow);
            break;
        case '5':
            currRow = Start+11;
            gotoxy(5, currRow);
            break;
        }
    }
}

void KeyInstruct()
{
    setColor("SH", 0, Start+2);
    cout << "Key Instructions:" << endl;

    setColor("II", 0, Start+3);
    cout << "Up Arrow";

    setColor("IV", 8, Start+3);
    cout << " Navigate Upwards";

    setColor("II", 30, Start+3);
    cout << "Down Arrow";

    setColor("IV", 40, Start+3);
    cout << " Navigate Downwards";

    setColor("II", 70, Start+3);
    cout << "1~5 Keys";

    setColor("IV", 78, Start+3);
    cout << " Menu Navigation Shortcut";

    // stRow+4

    setColor("II", 0, Start+4);
    cout << "Home";

    setColor("IV", 4, Start+4);
    cout << " Go to First Option";

    setColor("II", 30, Start+4);
    cout << "Enter";

    setColor("IV", 35, Start+4);
    cout << " Choose Highlighted Operation";
}

void MenuInit()
{
    system("cls");

    setColor("H", 0, Start);
    cout << "**** GeoShape Calculator ****" << endl;

    KeyInstruct();

    setColor("IR", 0, Start+6);
    cout << "Please choose the operation you would like to perform:" << endl;

    setColor("RP", 5, Start+7);

    cout << "1) Add GeoShape";

    gotoxy(5, Start+8);
    cout << "2) Replace Shape in GeoShape";

    gotoxy(5, Start+9);
    cout << "3) Display GeoShape";

    gotoxy(5, Start+10);
    cout << "4) Display All GeoShapes" << endl;

    gotoxy(5, Start+11);
    cout << "5) Exit" << endl;
}
