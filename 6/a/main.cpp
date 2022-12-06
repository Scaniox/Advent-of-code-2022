/*******************************************************************************
 *         File: Advent-of-Code-2022\6\a\main.cpp
 *       Author: Alexander Mills (Scaniox#7130)
 *      License: 
 *         Date: 06/12/22 :)
 *  Description: 
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <inttypes.h>
#include <deque>
#include <vector>
using namespace std;

#define HEXOUT setw(16) << setfill('0') << hex

uint64_t char_2_bitmask(char c);
int count_mask_bits(uint64_t mask);

int main() {
    fstream input_file;
    string line;
    input_file.open("input.txt");
    

    while(getline(input_file, line)) {
        deque<char> msg_q = deque<char>();
        int i;
        for(i=0; i<line.length(); i++) {

            // cout << "current msg_q: ";
            // for(auto it = msg_q.begin(); it != msg_q.end(); ++it)
            //     cout << ' ' << *it;

            // change letters in q
            msg_q.push_front(line[i]);
            if(msg_q.size() > 4){
                msg_q.pop_back();
            }


            // check if they are all different
            uint64_t mask = 0;
            for(int j=0; j<msg_q.size(); j++) {
                mask |= char_2_bitmask(msg_q[j]);
            }
            // cout << "mask: " << HEXOUT << mask << '\n';

            if(count_mask_bits(mask) == 4)
                break;
        }

        cout << dec << "lock on this line at index: " << i + 1 << '\n';
    }
}



/* converts a letter to a 64 bit bitmask
*   XX XF FF FF F 0000 FF FF FF
        ^----------^^---------^
        Z          Az         a
       uppercase       lowercase
*/
uint64_t char_2_bitmask(char c) {
    uint64_t bitmask = 0;
    if (islower(c))
        bitmask |= (uint64_t)1 << (c - 'a');
    else if (isupper(c))
        bitmask |= (uint64_t)1 << (c - 'A' + 26);
    return bitmask;
}

/* returns how many bits are set in a 64 bit mask */
int count_mask_bits(uint64_t mask) {
    int count = 0;
    do {
        if(mask & 1)
            count++;
    } while(mask >>= 1);

    return count;
}