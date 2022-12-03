/*******************************************************************************
 *         File: Advent-of-code-2022/1/a/main.cpp
 *       Author: Alexander Mills (Scaniox#7130)
 *      License: 
 *         Date: 01/12/22
 *  Description: 
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_FILE_LEN 99999

int main() {
    FILE *input_p = fopen("input.txt", "r");

    char file_str[MAX_FILE_LEN];

    int max_calories = 0;
    int current_elfs_calories = 0;
    int line_start_index = 0;

    int f_str_len = fread(file_str, sizeof(unsigned char), MAX_FILE_LEN, input_p);

    for(int i=0; i<f_str_len; i++) {
        if(file_str[i] == '\n') {
            if(i+1 < f_str_len) {

                int n = atoi(file_str + line_start_index);

                line_start_index = i + 1;

                if(file_str[i-1] == '\n') {
                    printf("current elf's calories: %i\n", current_elfs_calories);
                    if(current_elfs_calories > max_calories)
                        max_calories = current_elfs_calories;
                    current_elfs_calories = 0;
                }
                else {
                    printf("%i ", n);
                    current_elfs_calories += n;
                }
            }
        }
    }


    printf("max: %i\n", max_calories);
    

}