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

using namespace std;

SDL_Plotter *g;
int *data;
const int SPEED = 0;
bool TRACE = false;

//function for printing the elements in a list
void showlist(list <int> g)
{
    list <int> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        cout << '\t' << *it;
    cout << '\n';
}

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

    list <int> list;


    for (int i = 0; i < 10; ++i){
        list.push_back(i);
    }
    cout << "\nList  is : ";
    showlist(list);


    list<int>::iterator itr = list.begin();

    list.erase(itr);
    cout << "\nList  is : ";
    showlist(list);

    return 0;

}
