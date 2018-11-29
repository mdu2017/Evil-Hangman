/*
* Authors: Grant Gasser, Mark Du, David Beggs, Tate Smalligan, Garrett Yero
* Assignment Title: Group Project: Evil Hangman
* File Description: This header file houses the Rectangle object and methods used by the game.
* Due Date: 11/29/2018
 */

#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "point.h"
#include "color.h"
#include "SDL_Plotter.h"
#include <cmath>

using namespace std;

class Rectangle
{
private:
    Point upperLeft;
    Point lowerRight;
    Color color;

public:
    Rectangle(Point upperL = Point(0, 0), Point lowerR = Point(1, 1), Color c = Color(0, 0, 0)){
        upperLeft = upperL;
        lowerRight = lowerR;
        color = c;
    }

    /*
    * description: set the upper left point of the rectangle
    * return: void
    * precondition: the number of the upper left point of the rectangle is valid
    * postcondition: returns nothing
    */
    void setUpperLeft(Point p){
        upperLeft = p;
    }

    /*
    * description: set the lower right point of the rectangle
    * return: void
    * precondition: the number of the lower right point of the rectangle is valid
    * postcondition: returns nothing
    */
    void setLowerRight(Point p){
        lowerRight = p;
    }

    /*
    * description: set the color of rectangle
    * return: void
    * precondition: there exists a string of color
    * postcondition: returns nothing
    */
    void setColor(Color c){
        color = c;
    }

    /*
    * description: get the upper left point of the rectangle
    * return: point
    * precondition: the number of the upper left point of the rectangle is valid
    * postcondition: returns the upper left point of the rectangle
    */
    Point getUpperLeft() const{
        return upperLeft;
    }

    /*
    * description: get the lower right point of the rectangle
    * return: point
    * precondition: the number of lower right point of the rectangle is valid
    * postcondition: returns the lower right point of the rectangle
    */
    Point getlowerRight() const{
        return lowerRight;
    }

    /*
    * description: get the color of the rectangle
    * return: color
    * precondition: there exists a string of color
    * postcondition: returns the color of the rectangle
    */
    Color getColor() const{
        return color;
    }

    /*
    * description: draw the rectangle
    * return: void
    * precondition: the variable g is valid
    * postcondition: returns nothing
    */
    void draw(SDL_Plotter& g) const{
        for(int y = upperLeft.y; y <= lowerRight.y; y++)
        {
            for(int x = upperLeft.x; x <= lowerRight.x; x++)
            {
                g.plotPixel(x, y, color.R, color.G, color.B);
            }
        }
    }
};
#endif // RECTANGLE_H_INCLUDED