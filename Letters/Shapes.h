#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include <cmath>
#include "SDL_Plotter.h"

using namespace std;

enum Direction {RIGHT, LEFT, UP, DOWN, STOP};
const double PI = 3.14159;

struct Color{
    int R, G, B;

    //
    // description: Constructor for color object
    // return: color in RGB
    // precondition: none
    // postcondition: color now exists in RGB format
    //
    Color(int r = 0, int g = 0, int b = 0);
};

struct Point{
    int x, y;


    //
    // description: makes a point
    // return: none
    // precondition: none
    // postcondition: a point is now initialized
    //
    Point(int m = 0, int n = 0);



    //
    // description: finds the distance between points
    // return: a double
    // precondition: two points must exist
    // postcondition: distance
    //
    double distance(Point p);



    //
    // description: checks if a point is equal
    // return: true or false for equivalence
    // precondition: two points must exist
    // postcondition: the positions are checked
    //
    bool isEqual(Point p);
};

struct Rectangle{
    Point c1, c2;
    Color color;


    //
    // description: constructor for rectangle
    // return: none
    // precondition: points must exists
    // postcondition: rectangle is initialized
    //
    Rectangle(Point a = Point(), Point b = Point(), Color c = Color());



    //
    // description: determines if a collision is made
    // return: none
    // precondition: rectangle must exist
    // postcondition: directions become true or false
    //
    void collision(Rectangle hb, bool& up, bool& right, bool& down, bool& left);


    //
    // description: rectangle hit box for if a collision happens
    // return: true or false
    // precondition: rectangle must exist
    // postcondition: if the rectangle is hit returns true or false
    //
    bool collision(Rectangle hb);



    //
    // description: sets the top left and bottom right corner
    // return: none
    // precondition: two points must exist
    // postcondition: the rectangles corners are set
    //
    void setCorner(Point a, Point b);


    //
    // description: draws the rectangle
    // return: none
    // precondition: rectangle must exist
    // postcondition: the rectangle is drawn
    //
    void draw(SDL_Plotter& g);
};

struct Circle{
    Point center;
    double radius;
    Color color;

    //
    // description: circle constructor
    // return: none
    // precondition: point must exist
    // postcondition: circle is initialized
    //
    Circle(Point p = Point(), double r = 0, Color c = Color());



    //
    // description: draws the circle to the screen
    // return: none
    // precondition: circle must exist and be initialized
    // postcondition: circle is drawn
    //
    void draw(SDL_Plotter& g);
};

struct Triangle{
    Point tip;
    double sideLength;
    Direction dir;
    Color color;



    //
    // description:Triangle constructor initializes the triangle
    // return: none
    // precondition: point must exists
    // postcondition: triangle is initialized
    //
    Triangle(Point p = Point(), double sL = 0,
             Direction d = DOWN, Color c = Color());



    //
    // description: draws the triangle
    // return: none
    // precondition: triangle must exist
    // postcondition: triangle is drawn
    //
    void draw(SDL_Plotter& g);
};

#endif // SHAPES_H_INCLUDED
