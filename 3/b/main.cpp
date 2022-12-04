/*******************************************************************************
 *         File: Advent-of-Code-2022\3\b\main.cpp
 *       Author: Alexander Mills (Scaniox#7130)
 *      License: 
 *         Date: 04/12/22 :(
 *  Description: 
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <inttypes.h>
using namespace std;

#define HEXOUT setw(16) << setfill('0') << hex

uint64_t bag_to_bitmask(string bag);
uint64_t pocket_to_bitmask(string pocket);
int priority_from_bitmask(uint64_t bitmask);


int main(){
    string line0, line1, line2;
    fstream input_file;
    input_file.open("input.txt");
    int total_priority = 0;

    while(getline(input_file, line0)){
        getline(input_file, line1);
        getline(input_file, line2);

        uint64_t group_bagmasks = bag_to_bitmask(line0);
        group_bagmasks &= bag_to_bitmask(line1);
        group_bagmasks &= bag_to_bitmask(line2);

        total_priority += priority_from_bitmask(group_bagmasks);
    }

    cout << "total: " << total_priority << '\n';

}

// converts a two pocket bag to a set of bitmasks
uint64_t bag_to_bitmask(string bag){
    string pocket_0 = bag.substr(0, bag.length() / 2);
    string pocket_1 = bag.substr(bag.length() / 2, bag.length());

    return pocket_to_bitmask(pocket_0) | pocket_to_bitmask(pocket_1);
}

/* converts a pocket inventory to a 64 bit bitmask
*   XX XF FF FF F 0000 FF FF FF
        ^----------^^---------^
        Z          Az         a
       uppercase       lowercase
*/
uint64_t pocket_to_bitmask(string pocket) {
    uint64_t bitmask = 0;
    for(int i=0; i<pocket.length(); i++){
        char item = pocket[i];
        if(islower(item))
            bitmask |= (uint64_t)1 << (item - 'a');
        else if(isupper(item))
            bitmask |= (uint64_t)1 << (item - 'A' + 26);
    }
    return bitmask;
}

/* converts a bitmask with only one bit set to a priority*/
int priority_from_bitmask(uint64_t bitmask){
    int i;
    for(i=1; bitmask >>= 1;i++);
    return i;
}
