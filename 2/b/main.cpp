/*******************************************************************************
 *         File: Advent-of-code-2022/2/b/main.cpp
 *       Author: Alexander Mills (Scaniox#7130)
 *      License: 
 *         Date: 03/12/22 :(
 *  Description: 
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef enum {ROCK, PAPER, SCISSORS} shape_t;
typedef enum {LOSE, DRAW, WIN} result_t;

shape_t play_table[3][3] = {//lose      draw     win
                              SCISSORS, ROCK,    PAPER,    // they play ROCK
                              ROCK,     PAPER,   SCISSORS, // they play PAPER
                              PAPER,    SCISSORS,ROCK      // they play SCISSORS
                            };

int main() {
    string line;
    ifstream input_file;
    input_file.open("input.txt");

    int score = 0;

    if(input_file.is_open()) {   
        while(getline (input_file, line)) {
            // cout << '\n';
            shape_t them = static_cast<shape_t>(line[0] - 'A');
            result_t game_result = static_cast<result_t>(line[2] - 'X');
            shape_t me = play_table[them][game_result];
            score += me + 1;
            
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

