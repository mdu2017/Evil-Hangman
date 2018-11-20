//
// Created by Mark on 11/16/2018.
//

#ifndef EVILHANGMAN_POINT_H
#define EVILHANGMAN_POINT_H

#include <cmath>

struct Point
{
    double x;
    double y;

    Point() //default constructor
    {
        x = y = 0;
    }

    Point(double a, double b) //custom constructor
    {
        x = a;
        y = b;
    }


    /*
    * description: perform subtraction operation on two point values
    * return: Point
    * precondition: a Point other exists
    * postcondition: difference of points is returned
    */
    Point subtract(Point other)
    {
        return Point(x-other.x, y-other.y);
    }

    /*
    * description: overrides subtract operator
    * return: Point
    * precondition: a Point other exists
    * postcondition: subtracts two points by x & y coordinates
    */
    Point operator-(Point other)
    {
        return subtract(other);
    }

    /*
    * description: calculates distance between 2 points
    * return: double
    * precondition: a Point other exists
    * postcondition: distance between two points is returned
    */
    double distance(Point other)
    {
        return sqrt(pow(x - other.x, 2.0) + pow(y - other.y, 2.0));
    }
};

#endif //EVILHANGMAN_POINT_H
