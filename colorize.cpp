#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

using namespace std;

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}

void setColor(char* textType)
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);

    int colorID;
    int i = 0;
    switch(tolower(textType[i]))
    {
    case 'w':
        colorID = 12;
        break;
    case 'h':
        colorID = 10;
        break;
    case 'b':
        colorID = 9;
        break;
    case 's':
        i++;
        switch(tolower(textType[i]))
        {
        case '\0':
            colorID = 15;
            break;
        case 'h':
            colorID = 12;
            break;
        case 'm':
            colorID = 10;
            break;
        case 'p':
            colorID = 31;
            break;
        }
        break;
    case 'i':
        i++;
        switch(tolower(textType[i]))
        {
        case 'r':
            colorID = 14;
            break;
        case 'i':
            colorID = 23;
            break;
        case 'v':
            colorID = 15;
            break;
        }
        break;
    case 'd':
        i++;
        switch(tolower(textType[i]))
        {
        case 'i':
            colorID = 11;
            break;
        case 'v':
            colorID = 15;
            break;
        }
        break;
    case 'f':
        i++;
        switch(tolower(textType[i]))
        {
        case 'i':
            colorID = 14;
            break;
        case 'v':
            colorID = 11;
            break;
        }
        break;
    case 'r':
        i++;
        switch(tolower(textType[i]))
        {
        case 'p':
            colorID = 8;
            break;
        }
        break;
    case 'l':
        i++;
        switch(tolower(textType[i]))
        {
        case 'b':
            colorID = 1;
            break;
        }
        break;
    case 'a':
        i++;
        switch(tolower(textType[i]))
        {
        case 'd':
            i++;
            switch(tolower(textType[i]))
            {
            case 'h':
                colorID = 1;
                break;
            case 'v':
                colorID = 6;
                break;
            }
            break;
        case 'f':
            i++;
            switch(tolower(textType[i]))
            {
            case 'h':
                colorID = 9;
                break;
            case 'v':
                colorID = 15;
                break;
            }
            break;
        }
    case 'p':
        colorID = 13;
        break;
    }

    SetConsoleTextAttribute(console_color, colorID);

}

void setColor(char* textType, int column, int line)
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);

    int colorID;
    int i = 0;
    switch(tolower(textType[i]))
    {
    case 'w':
        colorID = 12;
        break;
    case 'h':
        colorID = 10;
        break;
    case 'b':
        colorID = 9;
        break;
    case 's':
        i++;
        switch(tolower(textType[i]))
        {
        case '\0':
            colorID = 15;
            break;
        case 'h':
            colorID = 12;
            break;
        case 'm':
            colorID = 10;
            break;
        case 'p':
            colorID = 31;
            break;
        }
        break;
    case 'i':
        i++;
        switch(tolower(textType[i]))
        {
        case 'r':
            colorID = 14;
            break;
        case 'i':
            colorID = 23;
            break;
        case 'v':
            colorID = 15;
            break;
        }
        break;
    case 'd':
        i++;
        switch(tolower(textType[i]))
        {
        case 'i':
            colorID = 11;
            break;
        case 'v':
            colorID = 15;
            break;
        }
        break;
    case 'f':
        i++;
        switch(tolower(textType[i]))
        {
        case 'i':
            colorID = 14;
            break;
        case 'v':
            colorID = 11;
            break;
        }
        break;
    case 'r':
        i++;
        switch(tolower(textType[i]))
        {
        case 'p':
            colorID = 8;
            break;
        }
        break;
    case 'l':
        i++;
        switch(tolower(textType[i]))
        {
        case 'b':
            colorID = 1;
            break;
        }
        break;
    case 'a':
        i++;
        switch(tolower(textType[i]))
        {
        case 'd':
            i++;
            switch(tolower(textType[i]))
            {
            case 'h':
                colorID = 1;
                break;
            case 'v':
                colorID = 6;
                break;
            }
            break;
        case 'f':
            i++;
            switch(tolower(textType[i]))
            {
            case 'h':
                colorID = 9;
                break;
            case 'v':
                colorID = 15;
                break;
            }
            break;
        }
    case 'p':
        colorID = 13;
        break;
    }

    gotoxy(column, line);
    SetConsoleTextAttribute(console_color, colorID);

}
