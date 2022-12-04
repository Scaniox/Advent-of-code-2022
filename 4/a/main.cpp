/*******************************************************************************
 *         File: Advent-of-Code-2022\4\a\main.cpp
 *       Author: Alexander Mills (Scaniox#7130)
 *      License: 
 *         Date: 04/12/22 :)
 *  Description: AOC 22 day 4 part a - clearing space
 ******************************************************************************/
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(){
    string line;
    fstream input_file;
    input_file.open("input.txt");

    int total_overlaps = 0;
    while(getline(input_file, line)){
        char *next_no_index = 0;
        int n1 = strtol(line.data(), &next_no_index, 10);
        int n2 = strtol(next_no_index + 1, &next_no_index, 10);
        int n3 = strtol(next_no_index + 1, &next_no_index, 10);
        int n4 = strtol(next_no_index + 1, &next_no_index, 10);

        if( n1 <= n3 && n4 <= n2 ||
            n3 <= n1 && n2 <= n4 )
            total_overlaps += 1;
    }
    
    cout << total_overlaps << '\n';

}