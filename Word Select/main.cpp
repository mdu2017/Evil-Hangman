#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

const int MAX_BINS = 3989;

vector<string> getGreatest(int size, char guess, vector<string> wordList){
    vector<string> bins[MAX_BINS];
    int count = 0, currentBin = size;
    int letterMap[size] = {0};
    int letterHash = 0;
    bool already = false;
    int maxWords = 0;
    int maxWordsIndex = 1;
    int num[MAX_BINS];
    for(int i = 0; i < MAX_BINS; i++){
        num[i] = 0;
    }
    for(auto n : wordList){
            /*
        for(int i = -1; i < size; i++){
            for(int j = -1; j < size; j++) {
                if(n.find(guess) == j && j==i) {
                    if (n.find(guess) == i) {
                        bins[i + 1].push_back(n);
                        num[i + 1]++;
                        if (maxWords < num[i + 1]) {
                            maxWords = num[i + 1];
                            maxWordsIndex = i + 1;
                        }
                    }
                }
                else{}
            }
        }
        */
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
                    letterMap[i] = 1;
                    letterHash += n[i] + i;
                    count++;
                }
            }
            bins[letterHash].push_back(n);
            num[letterHash]++;
            if(maxWords < num[letterHash]){
                maxWords = num[letterHash];
                maxWordsIndex = letterHash;
            }
            /*
            for(int i = 0; i < size; i ++){
                if(n.at(i) == guess){
                    if(!already){
                        bins[i+1].push_back(n);
                        num[i+1]++;
                        already = true;
                        if (maxWords < num[i + 1]) {
                            maxWords = num[i + 1];
                            maxWordsIndex = i + 1;
                        }
                    }
                    else{

                    }
                }
            }
            */
        }
        for(int j = 0; j < size; j++){
            //cout<<letterMap[j];
            letterMap[j] = 0;
        }
        //cout<<letterHash<<endl;
        //cout<<endl;
        letterHash = 0;
        count = 0;
        already = false;
    }
    return bins[maxWordsIndex];
}

int main() {
    ifstream input;
    string filename = "dictionary.txt";
    input.open(filename.c_str());
    int size, count = 0;
    cin>>size;
    vector<string> wordList;
    string word;
    char status[size];

    while(input>>word){
        if(word.length() == size){
            wordList.push_back(word);
        }
    }
    char guess;
    bool dead = false;
    bool correct = false;

    while(!dead & !correct){
        cin>>guess;
        switch(guess){
            case 'a':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'b':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'c':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'd':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'e':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'f':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'g':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'h':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'i':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'j':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'k':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'l':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'm':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'n':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'o':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'p':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'q':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'r':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 's':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 't':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'u':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'v':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'w':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'x':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'y':
                wordList = getGreatest(size, guess, wordList);
                break;
            case 'z':
                wordList = getGreatest(size, guess, wordList);
                break;
        }
        for(int i = 0; i < size; i++){

        }
        for(auto n : wordList){
            cout<<n<<endl;
        }
        if(count>=10){
            dead = true;
        }
        count++;
    }
    if(dead){
        cout<<"YOU DIED"<<endl;
    }
    if(correct){
        cout<<"YOU GOT IT RIGHT"<<endl;
    }


    return 0;
}
