/*******************************************************************************
 *         File: Advent-of-Code-2022\8\b\main.cpp 
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

// gets scenic_score for a tree that is visible
int get_scenic_score(tree_arr_t trees, int tree_y, int tree_x) {
    int sc = 1;
    int tree_height = std::get<0>(trees[tree_y][tree_x]);

    // down
    int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    for (int dir_no = 0; dir_no < 4; dir_no++){
        int dist = 0;
        int y = tree_y;
        int x = tree_x;
        while (1) {
            y += dirs[dir_no][0];
            x += dirs[dir_no][1];
            if (y < 0 || y >= trees.size()) break;
            if (x < 0 || x >= trees.size()) break;
            dist++;
            if (std::get<0>(trees[y][x]) >= tree_height) break;
        }
        sc *= dist;
    }

    return sc;
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

    int max_scenic = 0;
    for(int y = 1; y < trees.size()-1; y++) {
        for(int x = 1; x < trees[0].size()-1; x++) {
            if(std::get<1>(trees[y][x]))
                max_scenic = std::max(max_scenic, get_scenic_score(trees, y, x));
        }
    }
    std::cout << "max scenic score: " << max_scenic << '\n';
}
