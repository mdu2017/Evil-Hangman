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

using namespace std;

//Screen size & default size
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

//Functions for drawing body parts
void drawHead(SDL_Plotter& g, int radius, int centerX, int centerY);
void drawBody(SDL_Plotter& g, Line body);
void drawLeftArm(SDL_Plotter& g, Line lArm);
void drawRightArm(SDL_Plotter& g, Line rArm);
void drawLeftLeg(SDL_Plotter& g, Line lLeg);
void drawRightLeg(SDL_Plotter& g, Line rLeg);
void drawLines(SDL_Plotter& g, Line line, int size);
void drawLetters(SDL_Plotter &g, char ch, int LetterPos, int size);

//Rectangle for hanger
const Rectangle BASE(Point(150, 450), Point(350, 500), RED);
const Rectangle BASE2(Point(235, 100), Point(255, 450), RED);
const Rectangle BASE3(Point(235, 80), Point(500, 100), RED);
const Rectangle ROPE(Point(497, 100), Point(500, 150), RED);

const int MAX_BINS = 1000;

//Data structure
vector<string> getGreatest(int, char, vector<string>);

void plotWinScreen(SDL_Plotter &g);

void plotBlackScreen(SDL_Plotter &g);

void plotDeadScreen(SDL_Plotter &g, string word);

void plotStartScreen(SDL_Plotter &g);

void plotString(SDL_Plotter &g, string word, int scale, Color color, Point p1, int space=50);

void plotInputScreen(SDL_Plotter &g, int &size);

void mainGame(SDL_Plotter &g);

int main(int argc, char **argv) {
    char key = 0;
    bool quit = false, play = false;
    //Creating SDL plotter
    SDL_Plotter g(SCREEN_Y,SCREEN_X);

    do {
        quit = false;
        play = false;
        plotBlackScreen(g);
        plotStartScreen(g);
        do {
            if(g.kbhit()) {
                key = g.getKey();
                if(key == 81){
                    quit = true;
                } else {
                    play = true;
                }
            }
        }while(!quit && !play);
        if (play){
            mainGame(g);
        }
    }while(!quit);

    return 0;
}


vector<string> getGreatest(int size, char guess, vector<string> wordList){
    vector<string> bins[MAX_BINS];

    int letterHash = 0;
    int maxWords = 0;
    int maxWordsIndex = 1;
    int num[MAX_BINS];

    for(int i = 0; i < MAX_BINS; i++){
        num[i] = 0;
    }
    for(auto n : wordList){
        if(n.find(guess) == -1){
            bins[0].push_back(n);
            num[0]++;
            if (maxWords < num[0]) {
                maxWords = num[0];
                maxWordsIndex = 0;
            }
        }
        else{
            for(int i = 0; i < size; i ++){
                if(n.at(i) == guess){
                    letterHash += n[i] + static_cast<int>(pow(2,i))%123;
                }
            }
            bins[letterHash].push_back(n);
            num[letterHash]++;
            if(maxWords < num[letterHash]){
                maxWords = num[letterHash];
                maxWordsIndex = letterHash;
            }
        }
        letterHash = 0;
    }
    return bins[maxWordsIndex];
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
}

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

void plotWinScreen(SDL_Plotter &g){
    string word = "you win!";
    Point p1(600, 300);
    plotString(g, word, 4, GOLD, p1, 50);

    g.update();
}

void plotBlackScreen(SDL_Plotter &g){
    g.clear();
    g.update();
}

void plotStartScreen(SDL_Plotter &g){
    string welcome = "welcome to";
    string evil = "evil hangman";
    string play = "press p to play";
    string quit = "press q to quit";
    Point p1(300, 200);
    Point p2(300, 250);
    Point p3(300, 450);
    Point p4(300, 500);
    plotString(g, welcome, 2, RED, p1, 50);
    plotString(g, evil, 2, RED, p2, 50);
    plotString(g, play, 1, RED, p3, 25);
    plotString(g, quit, 1, RED, p4, 25);

    g.update();
}

void plotInputScreen(SDL_Plotter &g, int &size){
    char key;
    char wordSize[2] = {0, 0};
    string ws;
    int count = 0;
    size = 0;

    string choose = "choose your punishment";
    string num = "enter a number";
    string range = "between three and twenty one";
    string enter = "then press enter";
    Point p1(200, 300);
    Point p2(200, 350);
    Point p3(200, 400);
    Point p4(200, 450);
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
                    cout << key << endl;
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

    Point p(400, 500);
    plotString(g, ws, 2, GOLD, p);
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

void mainGame(SDL_Plotter &g){
    bool stopped = false, quit = false, play = false;
    int count = 0;
    int x, y, size;
    ifstream input;
    string filename = "dictionary.txt";
    input.open(filename);

    assert(input);

    plotBlackScreen(g);
    plotInputScreen(g, size);

    count = 0;

    char status[size];

    for(int i =0; i < size; i ++){
        status[i] = '0';
    }

    bool dead = false;
    bool correct = false;
    bool guessed = false;

    vector<string> wordList;
    string word;
    char guess;

    while(input >> word){
        if(word.length() == size){
            wordList.push_back(word);
        }
    }

    g.setQuit(false); 
    while (!g.getQuit() && !dead)
    {
        plotBlackScreen(g);
        BASE.draw(g);
        BASE2.draw(g);
        BASE3.draw(g);
        ROPE.draw(g);
        drawLines(g, LETTER_LINES, size);

        while(!dead && !correct){
            if(g.kbhit()) {
                guess = g.getKey();
                guess += 32;
                wordList = getGreatest(size, guess, wordList);

                for (int i = 0; i< size; i++){
                    if(guess == status[i]){
                        guessed = true;
                    }
                }

                if(!guessed){
                    for (int i = 0; i < size; i++) {
                        if (wordList[0].at(i) == guess) {
                            status[i] = guess;
                        }
                    }
                }

                for (int i = 0; i < size; i++) {
                    cout << status[i];
                }
                cout << endl;

                if (wordList[0].find(guess) == -1) {
                    count++;
                    switch (count) {
                        case 6:
                            drawRightLeg(g, RIGHT_LEG);
                            dead = true;
                        case 5:
                            drawLeftLeg(g, LEFT_LEG);
                        case 4:
                            drawRightArm(g, RIGHT_ARM);
                        case 3:
                            drawLeftArm(g, LEFT_ARM);
                        case 2:
                            drawBody(g, BODY);
                        case 1:
                            drawHead(g, HEAD_RADIUS, HEAD_CENTER_X, HEAD_CENTER_Y);
                    }
                }
                else {
                    if (!guessed){
                        for (int i = 0; i < size; i++){
                            if (status[i] == guess){
                                drawLetters(g, guess, i, size);
                            }
                        }
                    }else {
                        count++;
                    }
                    g.update();
                }

                guessed = false;
                correct = true;

                for (int i = 0; i < size && correct; i++) {
                    if (wordList[0].at(i) != status[i]) {
                        correct = false;
                    }
                }
            }
        }
        if(dead){
            plotDeadScreen(g, wordList.front());
            g.Sleep(3000);
            g.setQuit(true);
        }
        if(correct) {
            plotWinScreen(g);
            g.Sleep(3000);
            g.setQuit(true);
        }

        //Click with mouse to pause
        if(g.getMouseClick(x,y)){
            stopped = !stopped;
        }

        g.update();
    }

    input.close();
    g.clear();
}