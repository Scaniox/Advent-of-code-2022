/*******************************************************************************
 *         File: Advent-of-Code-2022\5\a\main.cpp
 *       Author: Alexander Mills (Scaniox#7130)
 *      License: 
 *         Date: 05/12/22 :)
 *  Description: 
 ******************************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

#define STACK_SIZE 30

int main() {
    // read stack lines into array
    int current_line = 0;
    string stack_in_lines[STACK_SIZE + 2];
    string line;
    fstream input_file;
    input_file.open("input.txt");

    while(getline(input_file, line) && line.length())
        stack_in_lines[current_line++] = line;
        
    cout << "file opened\n";
    // create stacks
    int stack_count = stack_in_lines[--current_line].length() / 4 + 1;
    cout << "we need " << stack_count << " stacks\n";

    std::vector<stack<char>> stacks;

    cout << "stack array created\n";
    for(int i=0; i<stack_count; i++)
        stacks.push_back(stack<char>());
    cout << "stacks allocated\n";

    // iterate backwards through the lines to push to the stacks
    while(current_line--) {
        for(int i=0; i<stack_count; i++) {
            char c;
            if ((c = stack_in_lines[current_line][1 + 4 * i]) != ' ') {
                cout << "pushing " << c << " to stack " << i << '\n';
                stacks[i].push(stack_in_lines[current_line][1+4*i]);
            }
        }
    }

    // execute instructions
    while(getline(input_file, line)) {
        int count = atoi(&line[5]);
        int source = atoi(&line[12]) - 1;
        int dest = atoi(&line[17]) - 1;

        for(int i=0; i<count; i++) {
            char c = stacks[source].top();
            // cout << "taking " << c << " from " << source << " to " << dest << '\n';
            stacks[dest].push(c);
            stacks[source].pop();
        }
    }

    // print final state of stacks
    cout << "final result : ";
    for(int i=0; i<stack_count; i++)
        cout << stacks[i].top();
    cout << '\n';
  
}