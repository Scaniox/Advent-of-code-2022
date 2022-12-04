/*******************************************************************************
 *         File: Advent-of-code-2022/2/a/main.cpp
 *       Author: Alexander Mills (Scaniox#7130)
 *      License: 
 *         Date: 03/12/22 :(
 *  Description: 
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum {ROCK = 1, PAPER = 2, SCISSORS = 3};

int main() {
    string line;
    ifstream input_file;
    input_file.open("input.txt");

    int score = 0;

    if(input_file.is_open()) {   
        while(getline (input_file, line)) {
            // cout << '\n';
            char them = line[0] - 'A' + 1;
            char me = line[2] - 'X' + 1;
            score += me;
            
            // cout << "me:" << int(me) << " them:" << int(them) << '\n';

            if(me == them){
                // cout << "draw" << '\n';
                score += 3;
            }
            if(me == ROCK && them == SCISSORS){
                // cout << "win" << '\n';
                score += 6;
            }
            else if (me == SCISSORS && them == ROCK); // lose
            else if(me > them){
                // cout << "win" << '\n';
                score += 6;
            }
        }
    }

    cout << "total score: " << score << '\n';
    
    input_file.close();

}

