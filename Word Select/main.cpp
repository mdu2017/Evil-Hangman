#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

const int MAX_BINS = 3989;

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

int main() {
    ifstream input;
    string filename = "dictionary.txt";
    input.open(filename.c_str());
    int size, count = 0;
    cin>>size;
    vector<string> wordList;
    string word;
    char status[size];
    for(int i =0; i < size; i ++){
        status[i] = '0';
    }

    while(input>>word){
        if(word.length() == size){
            wordList.push_back(word);
        }
    }
    char guess;
    bool dead = false;
    bool correct = false;

    while(!dead && !correct){
        cin>>guess;
        wordList = getGreatest(size, guess, wordList);
        for(int i = 0; i < size; i++){
            if(wordList[0].at(i) == guess){
                status[i] = guess;
            }
        }
        cout<<endl;
        for(int i = 0; i < size; i++){
            cout<<status[i];
        }
        cout<<endl;
        //for(auto n : wordList){
        //    cout<<n<<endl;
        //}
        if(wordList[0].find(guess) == -1){
            count++;
        }
        cout<<10 - count<<endl;
        correct = true;
        for(int i = 0; i < size && correct; i++){
            if(!(wordList[0].at(i) == status[i])){
                correct = false;
            }
        }
        if(count>=10){
            dead = true;
        }
    }
    if(dead){
        cout<<"YOU DIED"<<endl;
        for(auto n: wordList){
            cout<<n<<endl;
        }
    }
    if(correct){
        cout<<"YOU GOT IT RIGHT"<<endl;
    }


    return 0;
}

