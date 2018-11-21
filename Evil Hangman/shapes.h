#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include "color.h"
#include "point.h"
#include <cmath>
#include "SDL_Plotter.h"

using namespace std;

enum Direction {RIGHT, LEFT, UP, DOWN, STOP};
const double PI = 3.14159;


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


Circle::Circle(Point p, double r, Color c){
    center = p;
    radius = r;
    color = c;
}

void Circle::draw(SDL_Plotter& g){
    for(int x = center.x-radius; x < center.x+radius; x++){
        for(int y = center.y-radius; y < center.y+radius; y++){
            if(abs(y-center.y) < sqrt(radius*radius-(x-center.x)*(x-center.x))){
                g.plotPixel(x, y, color.R, color.G, color.B);
            }
        }
    }
    return;
}

Triangle::Triangle(Point p, double sL, Direction d, Color c){
    tip = p;
    sideLength = sL;
    dir = d;
    color = c;
}

void Triangle::draw(SDL_Plotter& g){
    double m = tan(PI/6), heigth = sideLength*cos(PI/6);
    int delta = 1;

    if(dir == RIGHT || dir == LEFT){
        if(dir == LEFT)
        {delta = -1;}
        heigth *= delta;
        for(int dx = 0; abs(dx-heigth) > 1; dx += delta){
            for(int dy = -sideLength/2; dy < sideLength/2; dy++){
                if(dy < m*dx*delta && dy > -m*dx*delta)
                {g.plotPixel(tip.x+dx, tip.y+dy, color.R, color.G, color.B);}
            }
        }
    }

    else if(dir == UP || dir == DOWN){
        if(dir == UP)
        {delta = -1;}
        m = 1/m;
        heigth *= delta;
        for(int dy = 0; abs(dy-heigth) > 1; dy += delta){
            for(int dx = -sideLength/2; dx < sideLength/2; dx++){
                if(dx < dy/m*delta && dx > -dy/m*delta)
                {g.plotPixel(tip.x+dx, tip.y+dy, color.R, color.G, color.B);}
            }
        }
    }
}


#endif // SHAPES_H_INCLUDED