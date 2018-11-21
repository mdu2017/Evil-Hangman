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
void drawLines(SDL_Plotter& g, Line line, int size);
void drawLetters(SDL_Plotter &g, char ch, int LetterPos);

//Rectangle for hanger
const Rectangle BASE(Point(150, 450), Point(350, 500), BLACK);
const Rectangle BASE2(Point(235, 100), Point(255, 450), BLACK);
const Rectangle BASE3(Point(235, 80), Point(500, 100), BLACK);
const Rectangle ROPE(Point(497, 100), Point(500, 150), RED);

const int MAX_BINS = 1000;

vector<string> getGreatest(int, char, vector<string>);

int main(int argc, char **argv) {
    ifstream input;
    string filename = "dictionary.txt";
    input.open(filename);

    assert(input);

    SDL_Plotter g(1066,1600);
    bool stopped = false;
    int R,G,B;
    int headRadius = 10;
    int count = 0;
    int x, y, size;
    char key;
    char wordSize[2];

    do{
        if(g.kbhit()) {
            key = g.getKey();
            if(key != SDL_SCANCODE_RETURN ){
                if ( key < 58 && key > 47){
                    wordSize[count++] = key;
                    cout << key <<endl;
                }
            }
        }
    }while(key != SDL_SCANCODE_RETURN);

    count = 0;
    size = atoi(wordSize);

    if(!size){
        size = 7;
    }
    if(size > 21){
        size = 7;
    }

    cout << size << endl;

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

    while (!g.getQuit() && !dead)
    {
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
                                drawLetters(g, guess, i);
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

                if (count >= 10) {
                    dead = true;
                }
            }
        }
        if(dead){
            cout<<"YOU DIED HAHAHAHAH"<<endl;
            for(auto n: wordList){
                cout <<n << endl;
            }
        }
        if(correct) {
            cout << "YOU GOT IT RIGHT.... THIS TIME" << endl;
            dead = true;
        }

        //Click with mouse to pause
        if(g.getMouseClick(x,y)){
            stopped = !stopped;
        }

        g.update();
    }

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

    if (size > 15)
    {
        for(int i = 0; i < 15; i++){
            Point p1(150 + 75    * i, 800);
            Point p2(200 + 75 * i, 800);
            line.setP1(p1);
            line.setP2(p2);

            line.draw(g);
        }

        size -= 15;

        Point p1(1300, 750);
        Point p2(1325, 750);
        line.setP1(p1);
        line.setP2(p2);

        line.draw(g);

        for(int i = 0; i < size; i++){
            Point p1(150 + 75    * i, 950);
            Point p2(200 + 75 * i, 950);
            line.setP1(p1);
            line.setP2(p2);

            line.draw(g);
        }
    }
    else {
        for(int i = 0; i < size; i++){
            Point p1(150 + 75 * i, 800);
            Point p2(200 + 75 * i, 800);
            line.setP1(p1);
            line.setP2(p2);

            line.draw(g);
        }
    }
}

void drawLetters(SDL_Plotter &g, char ch, int letterPos){
    if (letterPos <= 15){
        Point p1(160 + 75 * letterPos, 750);

        Letter let(ch, BLACK, 2, p1);
        let.draw(g);
    }
    else {
        letterPos -= 15;
        Point p1(160 + 75 * letterPos, 900);

        Letter let(ch, BLACK, 2, p1);
        let.draw(g);
    }

 }