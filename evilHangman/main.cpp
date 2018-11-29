/*
* Authors: Grant Gasser, Mark Du, David Beggs, Tate Smalligan, Garrett Yero
* Assignment Title: Group Project: Evil Hangman
* File Description: Main calls the mainGame and getGreatest functions. Also controls
 * the flow of the game.
* Due Date: 11/29/2018
 */

#include "SDL_Plotter.h"
#include "line.h"
#include "rectangle.h"
#include "letters.h"
#include "plot.h"
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

//Data structure
// Description: Function returns the largest group of words based on the character guessed
// Return: Vector of the largest group of words
// Precondition: The current vector of words exists
// Postcondition: The largest group of words is returned
vector<string> getGreatest(int, char, vector<string>);

// Description: Function renders the game, using the plotter and controlling the UX
// Return:
// Precondition: SDL_Plotter object exists
// Postcondition: The game is running
void mainGame(SDL_Plotter &g);

int main(int argc, char **argv) {
    char key = 0;
    bool quit = false, play = false;
    //Creating SDL plotter
    SDL_Plotter g(SCREEN_Y,SCREEN_X);

    g.initSound("scream.wav");
    g.initSound("win.wav");


    //start the game
    do {
        quit = false;
        play = false;

        //plot start screen
        plotBlackScreen(g);
        plotStartScreen(g);

        //get user input: p for play, q for quit
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
            //quadratic probing
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

void mainGame(SDL_Plotter &g){
    bool stopped = false, quit = false, play = false;
    int count = 0;
    int x, y, size;
    ifstream input;
    string filename = "dictionary.txt";
    input.open(filename);

    assert(input);

    //plot input screen
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

    //read in words that are the user-specified size
    while(input >> word){
        if(word.length() == size){
            wordList.push_back(word);
        }
    }

    g.setQuit(false);

    //begin the game
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

                /*
                for (int i = 0; i < size; i++) {
                    cout << status[i];
                }
                cout << endl;
                 */
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