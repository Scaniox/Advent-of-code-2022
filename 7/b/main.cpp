/*******************************************************************************
 *         File: Advent-of-Code-2022\7\b\main.cpp
 *       Author: Alexander Mills (Scaniox#7130)
 *      License: 
 *         Date: 
 *  Description: 
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

class Node {
public:
    string name;
    Node* parent;
    map<string, Node> children;
    int size;

    Node(string n = " ", int s = 0, Node *p = nullptr) {
        children = map<string, Node>();
        size = s;
        name = n;
        parent = p;
    }

    void print_tree(int indent_level = 0) {
        for (int i = 0; i < indent_level; i++)
            cout << "--->";
        cout << name << " (" << size << ") " << "\n";

        for (auto c = children.begin(); c != children.end(); c++) {
            c->second.print_tree(indent_level + 1);
        }
    }

    int calc_total_size(int *total) {
        if(children.size() == 0)
            return size;

        int total_size = 0;
        for(auto c=children.begin(); c != children.end(); c++) {
            // cout << "size of " << c->first << c->second.calc_total_size(total) << "\n";
            total_size += c->second.calc_total_size(total);
        }

        size = total_size;

        if(total_size < 100000)
            *total += total_size; 

        return total_size;
    }

    int find_smallest_removable(int *sf, int size_needed) {
        if (children.size() == 0)
            return size;

        int total_size = 0;
        for (auto c = children.begin(); c != children.end(); c++) {
            // cout << "size of " << c->first << c->second.calc_total_size(total) << "\n";
            total_size += c->second.find_smallest_removable(sf, size_needed);
        }

        size = total_size;

        if(total_size > size_needed && total_size < *sf){
            *sf = total_size;
        }

        return total_size;
    }
};

int main() {
    string line;
    fstream input_file;
    input_file.open("input.txt");

    // set up file tree
    Node root = Node("root", 0);
    Node *current_dir = &root;

    // read into a tree
    while(getline(input_file, line)) {
        cout << "parsing command: " << line <<'\n';
        cout << "tree currently looks like this:\n";
        root.print_tree();
        cout << "\n\n";

        if (line[0] == '$') {
            if(line.substr(2, 2) == "cd") {
                string dest = line.substr(5,80);

                if (dest == "/") {
                    current_dir = &root;
                }
                else if (dest == "..") {
                    current_dir = current_dir->parent; 
                }
                else {
                    
                    current_dir = &current_dir->children[dest];
                }      
            }
            else if (line.substr(2, 2) == "ls") {
                while(getline(input_file, line)) {
                    cout << "parsing ls: got to line " << line << '\n';

                    int size = 0;
                    string name;

                    if (line.substr(0,3) == "dir")
                        name = line.substr(4, 80);
                    else {
                        size = stoi(line.substr(0, line.find(' ')));
                        name = line.substr(line.find(' ')+1, 80);
                    }

                    current_dir->children[name] = Node(name, size, current_dir);

                    if (input_file.peek() == '$')
                        break;
                }
            }
        }
    }

    // sum up
    int total = 0;
    root.calc_total_size(&total);

    int size_needed = 30000000 -  (70000000 - root.size);
    int smallest_found = 99999999;
    root.find_smallest_removable(&smallest_found, size_needed);

    root.print_tree();
    cout << "smallest removable: " << smallest_found << '\n';
}


