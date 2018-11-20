//
// Created by Mark on 11/16/2018.
//

#ifndef EVILHANGMAN_COLOR_H
#define EVILHANGMAN_COLOR_H

struct Color
{
    int R, G, B;

    Color() //default constructor (sets to black color)
    {
        R = G = B = 0;
    }

    Color(int a, int b, int c) //custom constructor
    {
        R = a;
        G = b;
        B = c;
    }
};

#endif //EVILHANGMAN_COLOR_H
