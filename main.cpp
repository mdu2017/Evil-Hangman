#include <iostream>

using namespace std;

#include <fstream>
#include <cmath>

#include "SDL_Plotter.h"
#include "Shapes.h"
#include "Words.h"
#include "Letter.h"


const int RES = 999, //resolution
          S = 1, //scale


struct Color{
    int R, G, B;

    Color(int r = 33, int g = 33, int b = 222){
        R = r;
        G = g;
        B = b;
    }
};


class Words{
    private:
        Color color;
        Point pos;
        int letSize;

    public:
        /*
         *DESCRIPTION: constructor for a word that assigns color,
                       start point, and scale
         *RETURN: N/A
         *PRECONDITION: Words.h is included in the file
         *POSTCONDITION: a word object is created with specified values
        */
        Words(Color, Point, int );

        /*
         *DESCRIPTION: writes "EVILHANGMAN" to the SDL_Plotter
         *RETURN: void
         *PRECONDITION: word object and SDL_Plotter exist
         *POSTCONDITION: "EVILHANGMAN" is written to the SDL_Plotter and the word
                         object is unchanged
        */
        void writeEVILHANGMAN(SDL_Plotter& g);

        /*
         *DESCRIPTION: writes "READY" to the SDL_Plotter
         *RETURN: void
         *PRECONDITION: word object and SDL_Plotter exist
         *POSTCONDITION: "READY" is written to the SDL_Plotter and the word
                         object is unchanged
        */
        void writeReady(SDL_Plotter& g);

        /*
         *DESCRIPTION: writes "PLAY" to the SDL_Plotter
         *RETURN: void
         *PRECONDITION: word object and SDL_Plotter exist
         *POSTCONDITION: "PLAY" is written to the SDL_Plotter and the word
                         object is unchanged
        */
        void writePlay(SDL_Plotter& g);

	/*
         *DESCRIPTION: writes "'P'" to the SDL_Plotter
         *RETURN: void
         *PRECONDITION: word object and SDL_Plotter exist
         *POSTCONDITION: "'P'" is written to the SDL_Plotter and the word
                         object is unchanged
        */
        void writeP(SDL_Plotter& g);

	/*
         *DESCRIPTION: writes "QUIT" to the SDL_Plotter
         *RETURN: void
         *PRECONDITION: word object and SDL_Plotter exist
         *POSTCONDITION: "QUIT" is written to the SDL_Plotter and the word
                         object is unchanged
        */
        void writeQuit(SDL_Plotter& g);
        

	/*
         *DESCRIPTION: Sets the color for Words
         *RETURN: void
         *PRECONDITION: word object and SDL_Plotter exist
         *POSTCONDITION: Color is now changed
        */
        void setColor(Color c);

        /*
         *DESCRIPTION: sets the initial Point of the word object
         *RETURN: void
         *PRECONDITION: a word object exists
         *POSTCONDITION: starting point of word object is changed to p
        */
        void setPoint(Point p);

        /*
         *DESCRIPTION: sets the letSize of the word object
         *RETURN: void
         *PRECONDITION: a word object exists
         *POSTCONDITION: scalable letSize of word is changed to s
        */
        void setSize(int s);

        /*
         *DESCRIPTION: returns the color of the word object
         *RETURN: Color
         *PRECONDITION: a word object w/color exists
         *POSTCONDITION: the word object is unchanged
        */
        Color getColor() const;

        /*
         *DESCRIPTION: returns the initial point of the word object
         *RETURN: Point
         *PRECONDITION: a word object w/an initial point exists
         *POSTCONDITION: the word object is unchanged
        */
        Point getPoint() const;

        /*
         *DESCRIPTION: returns the scale of the word object
         *RETURN: int
         *PRECONDITION: a word object w/letSize exists
         *POSTCONDITION: the word object is unchanged
        */
        int getSize()  const;
};

struct MenuScreen{
    /*
     *DESCRIPTION: draws the black background for menu screen
     *RETURN: void
     *PRECONDITION: an SDL_Plotter is instantiated
     *POSTCONDITION: a black rectangle with the dimensions of the resolution is drawn
    */
    void drawBackground(SDL_Plotter& g);

    /*
     *DESCRIPTION: draws the menu screen graphics border
     *RETURN: void
     *PRECONDITION: SDL_Plotter is instantiated
     *POSTCONDITION: menu screen is drawn with border
    */
    void drawBorderRectanle(SDL_Plotter& g);

};

int main()
{
    SDL_Plotter g(RES, RES);
    MenuScreen menu;

while(!g.getQuit()){
        
	menu.drawBackground(g);
        g.update();
        g.Sleep(100);

        //MENU SCREEN
        while(!g.getQuit() && !play){
            if(g.kbhit()){
                switch(g.getKey()){
                    case 'P':
			      // Go to game screen.
                              break;
		    case 'Q':
			      // return zero.
                }
            }
            //g.update();
        }
    return 0;
}


//Words
Words::Words(Color c, Point p, int s){
    pos = p;
    letSize = s*S;
    color = c;
}

// Drawing the background.
void MenuScreen::drawBackground(SDL_Plotter& g){
    for(int i = 0; i < RES; i++){
        for(int n = 0; n < RES; n++){
            g.plotPixel(i, n, 0, 0, 0);
        }
    }

    return;
}

void Words::writeEVILHANGMAN(SDL_Plotter& g){
	Letter E = Letter('E', color, letSize, pos);
	       V = Letter('V', color, letSize, Point(pos.x+(ROW+4)*letSize, pos.y);
	       I = Letter('I', color, letSize, Point(pos.x+(ROW+4)*letSize*2, pos.y);
	       L = Letter('L', color, letSize, Point(pos.x+(ROW+4)*letSize*3, pos.y);
	       H = Letter('H', color, letSize, Point(pos.x+(ROW+4)*letSize*4, pos.y);
	       A = Letter('A', color, letSize, Point(pos.x+(ROW+4)*letSize*5, pos.y);
	       N = Letter('N', color, letSize, Point(pos.x+(ROW+4)*letSize*6, pos.y);
	       G = Letter('G', color, letSize, Point(pos.x+(ROW+4)*letSize*7, pos.y);
	       M = Letter('M', color, letSize, Point(pos.x+(ROW+4)*letSize*8, pos.y);
	       A1 = Letter('A', color, letSize, Point(pos.x+(ROW+4)*letSize*9, pos.y);
	       N1 = Letter('N', color, letSize, Point(pos.x+(ROW+4)*letSize*10, pos.y);


    E.draw(g);
    V.draw(g);
    I.draw(g);
    L.draw(g);
    H.draw(g);
    A.draw(g);
    N.draw(g);
    G.draw(g);
    M.draw(g);
    A1.draw(g);
    N1.draw(g);	
}


void Words::writeQuit(SDL_Plotter& g){
    Letter Q = Letter('Q', color, letSize, pos),
           U = Letter('U', color, letSize, Point(pos.x+(ROW+2)*letSize, pos.y)),
           I = Letter('I', color, letSize, Point(pos.x+(ROW+2)*letSize*2, pos.y)),
           T = Letter('T', color, letSize, Point(pos.x+(ROW+2)*letSize*3, pos.y));

    Q.draw(g);
    U.draw(g);
    I.draw(g);
    T.draw(g);
}

void Words::writePlay(SDL_Plotter& g){
    Letter P = Letter('P', color, letSize, pos),
           L = Letter('L', color, letSize, Point(pos.x+(ROW+2)*letSize, pos.y)),
           A = Letter('A', color, letSize, Point(pos.x+(ROW+2)*letSize*2, pos.y)),
           Y = Letter('Y', color, letSize, Point(pos.x+(ROW+2)*letSize*3, pos.y));

    P.draw(g);
    L.draw(g);
    A.draw(g);
    Y.draw(g);
}

void Words::writeP(SDL_Plotter& g){

    Letter fparen = Letter('(',color, letSize, pos);
	   P      = Letter('P', color, letSize, Point(pos.x+(ROW+1)*letSize, pos.y);
	   lparen = Letter(')', color, letSize, Point(pos.x+(ROW+1)*letSize, pos.y);

	fparen.draw(g);
	P.draw(g);
	lparen.draw(g)

}

void MenuScreen::drawBorderRectanle(SDL_Plotter& g){
	Rectangle Tborder = Rectangle(pos, Point(pos.x+RES,pos.y+RES/10),Color(240,40,0));
	Tborder.draw(g);
}
//
//
//
//
//
//
//	This is where we can add more borders or moving objects etc.
//
//
//
//
//
//

void Words::setColor(Color c){
    color = c;
}

void Words::setPoint(Point p){
    pos = p;
}

void Words::setSize(int s){
    letSize = s;
}

Color Words::getColor() const{
    return color;
}

Point Words::getPoint() const{
    return pos;
}

int Words::getSize() const{
    return letSize;
}

