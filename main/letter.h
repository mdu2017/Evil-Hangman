#ifndef LETTER_H_INCLUDED
#define LETTER_H_INCLUDED

#include <fstream>
#include <string>
#include "SDL_Plotter.h"
#include "point.h"
#include "color.h"

using namespace std;

const int ROW = 11,
        COL = 13,
        MAXS = 20;

struct Letter{
    char letter;
    int scale;
    Point topLeftCorner;
    Color color;
    char pixel[ROW][COL], scaled[ROW*MAXS][COL*MAXS];

    /*
     *DESCRIPTION: constructor for the letter object
     *RETURN: N/A
     *PRECONDITION: Letter.h is included in the implementation file
     *POSTCONDITION: letter object is created with specified parameters
    */
    Letter(char let = 'A', Color c = Color(), int s = 1, Point p = Point()){
        letter = let;
        scale = s;
        topLeftCorner = p;
        color = c;
    }

    void setLetter(char let){
        letter = let;
    }

    char getLetter(){
        return letter;
    }

    /*
     *DESCRIPTION: searches for specified character in Alphabet.txt file
     *RETURN: void
     *PRECONDITION: Alphabet.txt is the in the project path and a letter
                    object exists
     *POSTCONDITION: the letter is located in the file, and the pixelated version
                     of the letter is loaded into the pixed array
    */
    void findLetter(char let){
        ifstream alphabet;
        char input;
        string skip;

        //Open file and skip first 3 lines
        alphabet.open("letters.txt");
        getline(alphabet, skip);
        getline(alphabet, skip);
        getline(alphabet, skip);

        do{
            alphabet >> input;
        }while(input != let);

        for(int i = 0; i < ROW; i++){
            for(int j = 0; j < COL; j++){
                alphabet >> pixel[i][j];
            }
        }

        alphabet.close();

        return;
    }

    /*
     *DESCRIPTION: scales the letter array based on the scale variable
     *RETURN: void
     *PRECONDITION: letter object with pixel array of letter exists
                    and scale is known
     *POSTCONDITION: the scaled version of the pixel array is loaded into scaled array
    */
    void scaleLetter(){
        for(int i = 0; i < ROW*scale; i++){
            for(int j = 0; j < COL*scale; j++){
                scaled[i][j] = pixel[i/scale][j/scale];
            }
        }
        return;
    }

    /*
     *DESCRIPTION: draws the scaled array letter to an SDL_Plotter
     *RETURN: void
     *PRECONDITION: letter object exists
     *POSTCONDITION: letter is printed to the SDL_Plotter according to scale,
                     point, and color
    */
    void draw(SDL_Plotter& g){
        int dx = 0, dy = 0;

        findLetter(letter);
        scaleLetter();

        for(int i = 0; i < ROW*scale; i++){
            for(int j = 0; j < COL*scale; j++){
                if(scaled[i][j] == '1'){
                    g.plotPixel(topLeftCorner.x+dx, topLeftCorner.y+dy, color.R, color.G, color.B);
                }
                dx++;
            }
            dy++;
            dx -= 13*scale;
        }

        return;
    }
};

#endif // LETTER_H_INCLUDED
