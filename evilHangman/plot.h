/*
* Authors: Grant Gasser, Mark Du, David Beggs, Tate Smalligan, Garrett Yero
* Assignment Title: Group Project: Evil Hangman
* File Description: This header file houses the draw and plot functions used by the game.
* Due Date: 11/29/2018
 */

#ifndef EVILHANGMAN_PLOT_H
#define EVILHANGMAN_PLOT_H


#include "SDL_Plotter.h"
#include "line.h"
#include "rectangle.h"
#include "letters.h"
#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <cassert>

//Screen size & default word size
const int SCREEN_X = 1200;
const int SCREEN_Y = 720;
const int DEFAULT_SIZE = 7;

//Drawing lines at bottom
const int SPACE_BTWN_LINES = 30;
const int INIT_X = 100;
const int LINES_Y = 625;

//Colors
const Color BLUE = Color(0, 0, 200);
const Color RED  = Color(200, 17, 12);
const Color GREEN = Color(0, 200, 0);
const Color BROWN = Color(101, 67, 33);
const Color BLACK = Color(0, 0, 0);
const Color GOLD = Color(255,165,0);

//Head location
const int HEAD_CENTER_X = 500, HEAD_CENTER_Y = 175;
const int HEAD_RADIUS = 25;

//Line for body parts
const Line BODY(Point(500, 175), Point(501, 325), RED);
const Line LEFT_ARM(Point(500, 225), Point(425, 300), RED);
const Line RIGHT_ARM(Point(500, 225), Point(575, 300), RED);
const Line LEFT_LEG(Point(501,325), Point(450, 425), RED);
const Line RIGHT_LEG(Point(501, 325), Point(550, 425), RED);
const Line LETTER_LINES(Point(150, 600), Point(250, 600), RED);

//Rectangle for hanger
const Rectangle BASE(Point(150, 450), Point(350, 500), RED);
const Rectangle BASE2(Point(235, 100), Point(255, 450), RED);
const Rectangle BASE3(Point(235, 80), Point(500, 100), RED);
const Rectangle ROPE(Point(497, 100), Point(500, 150), RED);

const int MAX_BINS = 1000;

// Description: Function draws the head
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The head is drawn
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

// Description: Function draws the body
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The body is drawn
void drawBody(SDL_Plotter& g, Line body){
    body.draw(g);
}

// Description: Function draws the left arm
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The right left arm is drawn
void drawLeftArm(SDL_Plotter& g, Line lArm){
    lArm.draw(g);
}

// Description: Function draws the right arm
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The right arm is drawn
void drawRightArm(SDL_Plotter& g, Line rArm){
    rArm.draw(g);
}

// Description: Function draws the left leg
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The right left leg is drawn
void drawLeftLeg(SDL_Plotter& g, Line lLeg){
    lLeg.draw(g);
}

// Description: Function draws the right leg
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The right leg is drawn
void drawRightLeg(SDL_Plotter& g, Line rLeg){
    rLeg.draw(g);
}

// Description: Function draws the lines with dynamic sizing at bottom of screen
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The lines are plotted to the screen
void drawLines(SDL_Plotter& g, Line line, int size){

    int newX;
    int lineLength = (480/size);

    //Adjust line size
    Line newLines[size];

    //draw lines and letters
    for(int i = 0; i < size; i++){
        newX = INIT_X + (i*SPACE_BTWN_LINES) + (i*lineLength);

        newLines[i] = Line(Point(newX, LINES_Y), Point(newX+lineLength,LINES_Y), RED);
        //Line *newLine = new Line(Point(newX, LINES_Y), Point(newX+lineLength,LINES_Y), BLACK);
        newLines[i].draw(g);
    }


}

// Description: Function draws the letters of the word on the lines
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The letters are plotted to the screen
void drawLetters(SDL_Plotter &g, char ch, int letterPos, int size){

    int letterScale;
    int letterOffsetY;
    int lineLength = (480/size);
    int letterOffsetX = lineLength/2;
    int newX = 0;


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

    newX = (INIT_X + (letterPos*SPACE_BTWN_LINES) + (letterPos*lineLength)) + letterOffsetX;
    Letter let(ch, RED, letterScale, Point(newX, LINES_Y + letterOffsetY));
    let.draw(g);
}

// Description: Function plots the string that is entered into the function
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The string is plotted to the screen
void plotString(SDL_Plotter &g, string word, int scale, Color color, Point p1, int space){
    Letter wordLets[word.length()];
    for(int i = 0; i < word.length(); i++){
        wordLets[i].color = color;
        wordLets[i].scale = scale;
        wordLets[i].topLeftCorner = p1;
        p1.x += space;
        wordLets[i].letter = word[i];
        wordLets[i].draw(g);
    }
    g.update();
}

// Description: Function plots "YOU LOSE!" and completes the
// word on the screen
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The phrase "YOU LOSE!" and the correct word is plotted to the screen
void plotDeadScreen(SDL_Plotter &g, string word){
    string phrase = "you lose!";
    string yourWord = "your word was";
    Point p2;
    p2.x = 550;
    p2.y = 100;
    plotString(g, phrase, 4, RED, p2, 75);
    p2.x = 450;
    p2.y = 475;
    plotString(g, yourWord, 2, RED, p2, 50);
    for(int i = 0; i < word.length(); i++){
        drawLetters(g, word[i], i, word.length());
    }
    g.update();

    //Play scream when die
    g.playSound("scream.wav");
}

// Description: Function plots "YOU WIN!" to the screen
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The phrase "YOU WIN!" has been plotted to the screen
void plotWinScreen(SDL_Plotter &g){
    string word = "you win!";
    Point p1(600, 300);
    plotString(g, word, 4, GOLD, p1, 50);

    g.update();

    //Play ta da when die
    g.playSound("win.wav");
}

// Description: Function plots a black screen using the SDL_Plotter
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The screen is black
void plotBlackScreen(SDL_Plotter &g){
    Rectangle black(Point(1, 1), Point(SCREEN_X-1, SCREEN_Y-1), BLACK);
    black.draw(g);
    g.update();
}

// Description: Function plots the starting screen
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The starting screen has been plotted to the screen
void plotStartScreen(SDL_Plotter &g){
    string welcome = "welcome to";
    string evil = "evil hangman";
    string play = "press p to play";
    string quit = "press q to quit";
    Point p1(350, 200);
    Point p2(300, 250);
    Point p3(400, 450);
    Point p4(400, 500);
    plotString(g, welcome, 2, RED, p1, 50);
    plotString(g, evil, 2, RED, p2, 50);
    plotString(g, play, 1, RED, p3, 25);
    plotString(g, quit, 1, RED, p4, 25);

    g.update();
}

// Description: Function plots the input screen and receives input from user
// Return: void
// Precondition: SDL_Plotter exists
// Postcondition: The input screen is plotted
void plotInputScreen(SDL_Plotter &g, int &size){
    char key;
    char wordSize[2] = {0, 0};
    string ws;
    int count = 0;
    size = 0;

    string choose = "choose your punishment !";
    string num = "enter a number";
    string range = "between 3 - 21";
    string enter = "then press enter";
    Point p1(300, 300);
    Point p2(400, 350);
    Point p3(400, 400);
    Point p4(380, 450);
    plotString(g, choose, 1, RED, p1, 25);
    plotString(g, num, 1, RED, p2, 25);
    plotString(g, range, 1, RED, p3, 25);
    plotString(g, enter, 1, GOLD, p4, 25);

    //Get word size (must enter 0-9)
    do{
        if(g.kbhit()) {
            key = g.getKey();
            if(key != SDL_SCANCODE_RETURN ){
                if ( key < 58 && key > 47){
                    wordSize[count++] = key;
                    //cout << key << endl;
                }
            }
        }
    }while(key != SDL_SCANCODE_RETURN);

    size = atoi(wordSize);

    if (wordSize[0] == 0){
        ws += '7';
    }
    else {
        for (int i = 0; wordSize[i] != 0 && i < 2; i++){
            ws += wordSize[i];
        }

    }

    Point p(550, 500);
    plotString(g, ws, 2, GOLD, p, 20);
    g.update();
    g.Sleep(500);

    //INPUT VERIFICATION
    if(!size){
        size = DEFAULT_SIZE;
    }
    if(size > 21){
        size = DEFAULT_SIZE;
    }
    if(size < 3){
        size = DEFAULT_SIZE;
    }

    char status[size];

    for(int i =0; i < size; i ++){
        status[i] = '0';
    }

    g.update();
}

#endif //EVILHANGMAN_PLOT_H
