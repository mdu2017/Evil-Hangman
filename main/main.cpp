/*
* Author: Grant Gasser
* Assignment Title: Project 3 Sorting Visualization
* Assignment Description: This program helps visualize different sorting algorithms
* Due Date: 11/11/2018
* Date Created: 11/5/2018
* Date Last Modified: 11/11/2018
 */

#include "SDL_Plotter.h"
#include "line.h"
#include "rectangle.h"
#include <cstdlib>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

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

//Functions for drawing body parts
void drawHead(SDL_Plotter& g, int radius, int centerX, int centerY);
void drawBody(SDL_Plotter& g, Line body);
void drawLeftArm(SDL_Plotter& g, Line lArm);
void drawRightArm(SDL_Plotter& g, Line rArm);
void drawLeftLeg(SDL_Plotter& g, Line lLeg);
void drawRightLeg(SDL_Plotter& g, Line rLeg);

//Rectangle for hanger
const Rectangle BASE(Point(150, 450), Point(350, 500), BLACK);
const Rectangle BASE2(Point(235, 100), Point(255, 450), BLACK);
const Rectangle BASE3(Point(235, 80), Point(500, 100), BLACK);
const Rectangle ROPE(Point(497, 100), Point(500, 150), RED);

int main(int argc, char **argv) {

    SDL_Plotter g(720,1080);
    bool stopped = false;
    int R,G,B;
    int headRadius = 10;
    int x, y;


    while (!g.getQuit())
    {
        drawBody(g, BODY);
        drawHead(g, HEAD_RADIUS, HEAD_CENTER_X, HEAD_CENTER_Y);
        drawLeftArm(g, LEFT_ARM);
        drawRightArm(g, RIGHT_ARM);
        drawLeftLeg(g, LEFT_LEG);
        drawRightLeg(g, RIGHT_LEG);

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

////=========================
//// Test section
////=========================
//string line;
//vector<string> words;
//ifstream inFile("dictionary.txt");
//int wordSize;
//char guess;
//
//cout << "Enter word size: ";
//cin >> wordSize;
//
////Read in words with length of the wordSize
//while(inFile){
//getline(inFile, line);
//
//if(line.size() == wordSize){
//words.push_back(line);
//}
//}
//inFile.close();
//
////Printing words before guess
//for(int i = 0; i < words.size(); i++){
//cout << words[i] << " - " << words[i].size() << endl;
//}
//
//cout << "Enter guess: ";
//cin >> guess;
//
//
//for(int i = 0; i < words.size(); i++){
//
//if(words[i].find(guess) != -1){
//words.erase(words.begin() + i);
//i--;
//}
//}
//
////Printing words after removing words with letter
//for(int i = 0; i < words.size(); i++){
//cout << words[i] << " - " << words[i].size() << endl;
//}