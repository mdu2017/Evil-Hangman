/*
* Authors: Grant Gasser, Mark Du, David Beggs, Tate Smalligan, Garrett Yero
* Assignment Title: Group Project: Evil Hangman
* File Description: This header file houses the Line object and methods used by the game.
* Due Date: 11/29/2018
 */

#ifndef EVILHANGMAN_LINE_H
#define EVILHANGMAN_LINE_H

#include <cmath>
#include <ostream>
#include "color.h"
#include "point.h"
#include "SDL_Plotter.h"

class Line
{
private:
    Point p1, p2;
    Color color;

public:
    Line(){
        p1 = Point(0, 0);
        p2 = Point(1, 1);
        color = Color(0, 0, 0); //black
    }

    Line(Point one, Point two){
        p1 = one;
        p2 = two;
        color = Color(0, 0, 0);
    }

    Line(Point one, Point two, Color c){
        p1 = one;
        p2 = two;
        color = c;
    }

    /*
    * description: get the point p1 of the line
    * return: point
    * precondition: the number of point p1 is valid
    * postcondition: returns the point of the line
    */
    Point getP1() const{
        return p1;
    }

    /*
    * description: get the point p2 of the line
    * return: point
    * precondition: the number of point p2 is valid
    * postcondition: returns the point of the line
    */
    Point getP2() const{
        return p2;
    }

    /*
    * description: get the color of the line
    * return: color
    * precondition: the string of color is valid
    * postcondition: returns the color of the line
    */
    Color getColor() const{
        return color;
    }

    /*
    * description: set the point p1 of the line
    * return: void
    * precondition: the number of point p1 is valid
    * postcondition: returns nothing
    */
    void setP1(const Point& p){
        p1 = p;
    }

    /*
    * description: set the point p2 of the line
    * return: void
    * precondition: the number of point p2 is valid
    * postcondition: returns nothing
    */
    void setP2(const Point& p){
        p2 = p;
    }

    /*
    * description: set the color of the line
    * return: void
    * precondition: the string of color is valid
    * postcondition: returns nothing
    */
    void setColor(const Color& c){
        color = c;
    }

    /*
    * description: calculate the slope of the line
    * return: bool
    * precondition: the number of slope is valid
    * postcondition: returns the true value if there is a slope,
    *                false otherwise
    */
    bool slope(double& m) const{
        bool hasSlope = false;

        hasSlope = (p1.x != p2.x);

        if(hasSlope)
        {
            m = (p1.y - p2.y) / (p1.x - p2.x);
        }

        return hasSlope;
    }

    /*
    * description: calculate the intercept of the line
    * return: bool
    * precondition: the number of the intercept is valid
    * postcondition: returns the true value if there is a intercept,
    *                false otherwise
    */
    bool intercept(double& b) const{
        bool hasIntercept = false;
        double m;

        hasIntercept = slope(m);

        if(hasIntercept)
        {
            b = p1.y - (m * p1.x);
        }

        return hasIntercept;
    }

    /*
    * description: draw the line
    * return: void
    * precondition: there exists a line
    * postcondition: returns nothing
    */
    void draw(SDL_Plotter& g) const{
        double m, b;
        int y;
        double delta = 0.001; //for very small increments

        if(slope(m))
        {
            intercept(b);
            if(p1.x < p2.x)
            {
                for(double x = p1.x; x <= p2.x; x += delta)
                {
                    y = m * x + b + 0.5; //0.5 for rounding
                    g.plotPixel(x, y, color.R, color.G, color.B);
                }
            }
            else
            {
                for(double x = p1.x; x >= p2.x; x -= delta)
                {
                    y = m * x + b + 0.5; //0.5 for rounding
                    g.plotPixel(x, y, color.R, color.G, color.B);
                }
            }
        }
        else
        {
            if(p1.y > p2.y)
            {
                delta = -1;
            }
            for(int y = p1.y; p1.y != p2.y; y += delta) //if no slope, draws from y1 to y2
            {
                g.plotPixel(p1.x, y, color.R, color.G, color.B);
            }
        }

        g.update();
    }
};

#endif //EVILHANGMAN_LINE_H