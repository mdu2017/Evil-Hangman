#include "Shapes.h"

Color::Color(int r, int g, int b){
    R = r;
    G = g;
    B = b;
}

Point::Point(int m, int n){
    x = m;
    y = n;
}

double Point::distance(Point p){
    return  sqrt(pow(x-p.x,2.0)+pow(y-p.y,2.0));
}

bool Point::isEqual(Point p){
    bool equality = false;

    if(x == p.x && y == p.y)
        equality = true;

    return equality;
}

Rectangle::Rectangle(Point a, Point b, Color c){
    c1 = a;
    c2 = b;
    color = c;
}

void Rectangle::setCorner(Point a, Point b){
    c1 = a;
    c2 = b;
    return;
}

void Rectangle::collision(Rectangle hb, bool& up, bool& right,
                          bool& down, bool& left){
    if((hb.c1.y > c1.y && hb.c2.y < c2.y)          //hit box in middle
       || (hb.c1.y < c2.y && hb.c2.y > c2.y)       //top hit box collide
       || (hb.c1.y < c1.y && hb.c2.y > c1.y)){     //bottom hit box collide
        //left side of wall : right side of hit box
        if(hb.c2.x == c1.x)
            right = false;
        //right side of wall : left side of hit box
        if(hb.c1.x == c2.x)
            left = false;
    }

    if((hb.c1.x > c1.x && hb.c2.x < c2.x)              //hit box in middle
       || (hb.c1.x < c1.x && hb.c2.x > c1.x)           //right hit box collide
       || (hb.c1.x < c2.x && hb.c2.x > c2.x)){         //left hit box collide
        //top of wall : bottom of hit box
        if(hb.c2.y == c1.y)
            down = false;
        //bottom of wall : top of hit box
        if(hb.c1.y == c2.y)
            up = false;
    }
    return;
}

bool Rectangle::collision(Rectangle hb){
    bool isCollide = false;

    if((hb.c1.y > c1.y && hb.c2.y < c2.y)          //hit box in middle
       || (hb.c1.y < c2.y && hb.c2.y > c2.y)       //top hit box collide
       || (hb.c1.y < c1.y && hb.c2.y > c1.y)){     //bottom hit box collide
        //left & right
        if((hb.c2.x == c1.x) || (hb.c1.x == c2.x))
            {isCollide = true;}
    }

    if((hb.c1.x > c1.x && hb.c2.x < c2.x)              //hit box in middle
       || (hb.c1.x < c1.x && hb.c2.x > c1.x)           //right hit box collide
       || (hb.c1.x < c2.x && hb.c2.x > c2.x)){         //left hit box collide
        //top & bottom
        if((hb.c2.y == c1.y) || (hb.c1.y == c2.y))
            {isCollide = true;}
    }
    return isCollide;
}

void Rectangle::draw(SDL_Plotter& g){
    int deltaX = 1, deltaY = 1;
    int xOffSet = 0;

    if(c1.x > c2.x)
        deltaX = xOffSet = -1;
    if(c1.y > c2.y)
        deltaY = -1;

    for(int y = c1.y; y != c2.y; y += deltaY){
        for(int x = c1.x; x != c2.x; x += deltaX){
            g.plotPixel(x + xOffSet, y, color.R, color.G, color.B);
        }
    }
    return;
}

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
