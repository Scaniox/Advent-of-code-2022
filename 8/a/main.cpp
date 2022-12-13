/*******************************************************************************
 *         File: Advent-of-Code-2022\8\a\main.cpp 
 *       Author: Alexander Mills (Scaniox#7130)
 *      License: 
 *         Date: 
 *  Description: 
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

// colours
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define RESET "\x1B[0m"

typedef std::vector<std::vector<std::tuple<int, bool>>> tree_arr_t;

void print_trees(tree_arr_t trees) {
    std::cout << '\n';
    for (auto row : trees) {
        for (std::tuple<int, bool> col : row)
            if (std::get<1>(col))
                std::cout << RED << std::get<0>(col);
            else 
                std::cout << RESET << std::get<0>(col);

        std::cout << '\n';
    }
}

int count_ones(tree_arr_t trees) {
    int c = 0;

    for(auto row : trees) {
        for(auto col : row) {
            if(std::get<1>(col))
                c++;
        }
    }
    
    return c;
}

int main() {
    std::string line;
    int line_no = 0;
    std::fstream input_file;
    input_file.open("input.txt");

    tree_arr_t trees;
    int size_x;
    int size_y;

    // read input and do top to bottom scan
    std::vector<int> tallest = std::vector<int>();
    int x;
    while(getline(input_file, line)) {
        std::vector<std::tuple<int, bool>> row{};
        for(x = 0; x < line.length(); x++) {
            int v = line[x] - '0';

            if(line_no == 0) 
                tallest.push_back(-1);

            bool taller;
            if(taller = (v > tallest[x]))
                tallest[x] = v;
            row.push_back(std::tuple<int, bool>(v, taller));
        }
        trees.push_back(row);
        line_no++;
    }
    size_x = x;
    size_y = line_no;

    // bottom up scan
    std::fill(tallest.begin(), tallest.end(), -1);
    for(int y = trees.size()-1; y >= 0; y--) {
        for (int x = 0; x < trees[y].size(); x++) {
            int v = std::get<0>(trees[y][x]);

            if (v > tallest[x]) {
                tallest[x] = v;
                trees[y][x] = std::tuple<int, bool>(v, true);
            }
        }
    }

    // left to right scan
    std::fill(tallest.begin(), tallest.end(), -1);
    for (int x = 0; x < trees[0].size(); x++) {
        for (int y = 0; y < trees.size(); y++) {
            int v = std::get<0>(trees[y][x]);

            if (v > tallest[y]) {
                tallest[y] = v;
                trees[y][x] = std::tuple<int, bool>(v, true);
            }
        }
    }

    // right to left scan
    std::fill(tallest.begin(), tallest.end(), -1);
    for (int x = trees[0].size() - 1; x >= 0; x--) {
        for (int y = 0; y < trees.size(); y++) {
            int v = std::get<0>(trees[y][x]);

            if (v > tallest[y]) {
                tallest[y] = v;
                trees[y][x] = std::tuple<int, bool>(v, true);
            }
        }
    }

    print_trees(trees);
    std::cout << "visible: " << count_ones(trees) << "\n";

}
