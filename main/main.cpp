/*
* Edited by Grant on 11/19.
* Added First line to UI. Need to make drawing of lines dynamic.
*/

#include "SDL_Plotter.h"
#include "line.h"
#include "rectangle.h"
#include "Letter.h"
#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

//Variables for drawing lines at bottom
const int SPACE_BTWN_LINES = 30;
const int INIT_X = 100;
const int LINES_Y = 625;

//Colors
const Color BLUE = Color(0, 0, 200);
const Color RED  = Color(200, 0, 0);
const Color GREEN = Color(0, 200, 0);
const Color BROWN = Color(101, 67, 33);
const Color BLACK = Color(0, 0, 0);

//Head location
const int HEAD_CENTER_X = 500, HEAD_CENTER_Y = 175;
const int HEAD_RADIUS = 25;

//Line for body parts
const Line BODY(Point(500, 175), Point(501, 325), BLUE);
const Line LEFT_ARM(Point(500, 225), Point(425, 300), BLUE);
const Line RIGHT_ARM(Point(500, 225), Point(575, 300), BLUE);
const Line LEFT_LEG(Point(501,325), Point(450, 425), BLUE);
const Line RIGHT_LEG(Point(501, 325), Point(550, 425), BLUE);
const Line LETTER_LINES(Point(150, 600), Point(250, 600), BLACK);

//Functions for drawing body parts
void drawHead(SDL_Plotter& g, int radius, int centerX, int centerY);
void drawBody(SDL_Plotter& g, Line body);
void drawLeftArm(SDL_Plotter& g, Line lArm);
void drawRightArm(SDL_Plotter& g, Line rArm);
void drawLeftLeg(SDL_Plotter& g, Line lLeg);
void drawRightLeg(SDL_Plotter& g, Line rLeg);
void drawLines(SDL_Plotter& g, Line line);

//Rectangle for hanger
const Rectangle BASE(Point(150, 450), Point(350, 500), BLACK);
const Rectangle BASE2(Point(235, 100), Point(255, 450), BLACK);
const Rectangle BASE3(Point(235, 80), Point(500, 100), BLACK);
const Rectangle ROPE(Point(497, 100), Point(500, 150), RED);

int main(int argc, char **argv) {

    SDL_Plotter g(720,1080);
    bool stopped = false;
    int x, y, size;
    int newX;
    int letterScale;
    int letterOffsetX;
    int letterOffsetY;

    cout << "Enter the size of the word you want to play." << endl;
    cin >> size;

    //Set line length based on size
    int lineLength = (480/size);
    letterOffsetX = lineLength/2;

    //Create letter array and scale based on size
    Letter letters[size];
    if(size >= 14){
        letterScale = 1;
        letterOffsetX -= 5;
        letterOffsetY = -20;
    }
    else if(size >= 10){
        letterScale = 2;
        letterOffsetX -= 10;
        letterOffsetY = -30;
    }
    else{
        letterScale = 3;
        letterOffsetX -= 15;
        letterOffsetY = -40;
    }


    while (!g.getQuit())
    {
        //draw first line
        Line FIRST_LINE(Point(INIT_X, LINES_Y), Point(INIT_X + lineLength, LINES_Y), BLACK);
        drawLines(g, FIRST_LINE);

        //draw lines and letters
        for(int i = 0; i < size; i++){
            newX = INIT_X + (i*SPACE_BTWN_LINES) + (i*lineLength);

            Line *newLine = new Line(Point(newX, LINES_Y), Point(newX+lineLength,LINES_Y), BLACK);
            drawLines(g, *newLine);

            //Set the letter's coordinates
            letters[i] = Letter('P', GREEN, letterScale,
                    Point(newX + letterOffsetX, LINES_Y + letterOffsetY));
        }

        //Draw the letters (we can set each letter depending on kbhit later)
        for(int i = 0; i < size; i++){
            letters[i].draw(g);
        }

        //Draw stick figure
        drawBody(g, BODY);
        drawHead(g, HEAD_RADIUS, HEAD_CENTER_X, HEAD_CENTER_Y);
        drawLeftArm(g, LEFT_ARM);
        drawRightArm(g, RIGHT_ARM);
        drawLeftLeg(g, LEFT_LEG);
        drawRightLeg(g, RIGHT_LEG);

        //Draw base
        BASE.draw(g);
        BASE2.draw(g);
        BASE3.draw(g);
        ROPE.draw(g);

        if(g.kbhit()){
            switch(g.getKey()){


                default: break;
            }
        }

        //Click with mouse to pause
        if(g.getMouseClick(x,y)){
            stopped = !stopped;
        }

        g.update();
    }

    return 0;

}

void drawHead(SDL_Plotter& g, int radius, int centerX, int centerY){

    for(int x = -radius; x <= radius; x++)
    {
        for(int y = -radius; y <= radius; y++)
        {
            if(sqrt(x*x + y*y) <= radius)
            {
                g.plotPixel(centerX + x, centerY + y, 20, 20, 220);
            }
        }
    }
    g.update();
}

void drawBody(SDL_Plotter& g, Line body){
    body.draw(g);
}

void drawLeftArm(SDL_Plotter& g, Line lArm){
    lArm.draw(g);
}

void drawRightArm(SDL_Plotter& g, Line rArm){
    rArm.draw(g);
}

void drawLeftLeg(SDL_Plotter& g, Line lLeg){
    lLeg.draw(g);
}

void drawRightLeg(SDL_Plotter& g, Line rLeg){
    rLeg.draw(g);
}

void drawLines(SDL_Plotter& g, Line line){
    line.draw(g);
}

//    //Prints gg
//    Letter test('G', RED, 5, Point(600, 300));
//    Letter test2('G', RED, 5, Point(700, 300));
//    test.draw(g);
//    test2.draw(g);