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

    g = new SDL_Plotter(1000,1000);
    data = new int[g->getCol()];


    for(int i =0; i < g->getCol(); i++){
        data[i] = rand()%g->getCol();
    }

    while(!g->getQuit()){

        if(g->kbhit()){
            switch(g->getKey()){
                case 'B': ;
                    break;
                case 'R': ;
                    break;
                case 'S': ;
                    break;
                case 'I': ;
                    break;
                case 'H': ;
                    break;
                case 'Q': ;
                    break;
                case 'M': ;
                    break;
                case 'T': TRACE = !TRACE;
                    break;
                case 'C': g->clear();
                    break;
                case 'X': g->setQuit(true);
                    break;
            }
        }
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