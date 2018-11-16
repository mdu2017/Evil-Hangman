#include "Letter.h"

Letter::Letter(char let, Color c, int s, Point p){
    letter = let;
    scale = s;
    topLeftCorner = p;
    color = c;
}

void Letter::findLetter(char let){
    ifstream alphabet;
    char input;

    alphabet.open("Alphabet.txt");

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

void Letter::scaleLetter(){
    for(int i = 0; i < ROW*scale; i++){
        for(int j = 0; j < COL*scale; j++){
            scaled[i][j] = pixel[i/scale][j/scale];
        }
    }
    return;
}

void Letter::draw(SDL_Plotter& g){
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
