/*******************************************************************************
 *         File: Advent-of-Code-2022\3\a\main.cpp
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

uint64_t pocket_to_bitmask(string pocket);
int priority_from_bitmask(uint64_t bitmask);


int main(){
    string line;
    fstream input_file;
    input_file.open("input.txt");
    int total_priority = 0;

    while(getline(input_file, line)){
        string pocket_0 = line.substr(0, line.length()/2);
        string pocket_1 = line.substr(line.length()/2, line.length());

        cout << "pocket0: " << pocket_0 << " pocket1: " << pocket_1 << '\n';

        uint64_t pocketmask_0 = pocket_to_bitmask(pocket_0);
        uint64_t pocketmask_1 = pocket_to_bitmask(pocket_1);

        cout << "mask0: " << HEXOUT << pocketmask_0;
        cout << " mask1: " << HEXOUT << pocketmask_1;
        cout << " anded together: " << HEXOUT << (pocketmask_0 & pocketmask_1) << '\n';

        int priority = priority_from_bitmask(pocketmask_0 & pocketmask_1);
        cout << "priority: " << dec << priority << '\n';
        total_priority += priority;
    }

    cout << "total: " << total_priority << '\n';

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
