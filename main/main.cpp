/*
* Author: Grant Gasser
* Assignment Title: Project 3 Sorting Visualization
* Assignment Description: This program helps visualize different sorting algorithms
* Due Date: 11/11/2018
* Date Created: 11/5/2018
* Date Last Modified: 11/11/2018
 */

#include "SDL_Plotter.h"
#include <cstdlib>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

SDL_Plotter *g;
int *data;
const int SPEED = 0;
bool TRACE = false;

int main(int argc, char **argv) {

    SDL_Plotter g(1000,1000);
    bool stopped = false;
    bool colored = false;
    int x,y, xd, yd;
    int R,G,B;

    while (!g.getQuit())
    {
        if(!stopped){
            x = rand()%g.getCol();
            y = rand()%g.getRow();
            R = rand()%256;
            G = rand()%256;
            B = rand()%256;
            for(xd = 0; xd < 10 && x + xd < g.getCol(); xd++ ){
                for(yd = 0; yd < 10 && y + yd < g.getRow(); yd++ ){
                    if(colored){
                        g.plotPixel( x + xd, y + yd, R, G, B);
                    }
                    else{
                        g.plotPixel( x + xd, y + yd, 0, G, 0);
                    }

                }
            }
        }

        if(g.kbhit()){
            g.getKey();
        }

        if(g.getMouseClick(x,y)){
            stopped = !stopped;
        }

        g.update();
    }


    //=========================
    // Test section
    //=========================
    string line;
    vector<string> words;
    ifstream inFile("dictionary.txt");
    int wordSize;
    char guess;

    cout << "Enter word size: ";
    cin >> wordSize;

    //Read in words with length of the wordSize
    while(inFile){
        getline(inFile, line);

        if(line.size() == wordSize){
            words.push_back(line);
        }
    }
    inFile.close();

    //Printing words before guess
    for(int i = 0; i < words.size(); i++){
        cout << words[i] << " - " << words[i].size() << endl;
    }

    cout << "Enter guess: ";
    cin >> guess;


    for(int i = 0; i < words.size(); i++){

        if(words[i].find(guess) != -1){
            words.erase(words.begin() + i);
            i--;
        }
    }

    //Printing words after removing words with letter
    for(int i = 0; i < words.size(); i++){
        cout << words[i] << " - " << words[i].size() << endl;
    }

    return 0;

}