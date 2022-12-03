//
// Created by terrorgarten on 30.11.22.
//
#include <vector>
#include <fstream>
#include <sstream>
#include "model.hpp"

using namespace std;

void propagate_updates(Cell **map_grid);

void print_map_grid(Cell **map_grid);

void run_main_loop(Cell **map_grid, unsigned int iterations);


//https://www.geeksforgeeks.org/csv-file-management-using-c/
int main(int argc, char **argv) {
    //parse user input/txt file
    // load CSV/txt file, parse it
    Cell **map_grid = new Cell *[SIZE];
    for (int i = 0; i < SIZE; ++i)
        map_grid[i] = new Cell[SIZE + 1];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {                            //TODO vitr z argumentu
            map_grid[i][j] = *new Cell(i, j, DEFAULT_T, 6, 0);
        }
    }

    //assign_factories(&map_grid);
    int count = 0;
    // File pointer
    std::fstream file;
    file.open("data/indexes.csv", ios::in);

    vector<string> row;
    string line, word, temp;
    if (file.is_open()) {
        while (getline(file, line)) {
            //skip header
            count++;
            if (count == 1) {
                continue;
            }

            row.clear();
            stringstream str(line);

            while (getline(str, word, ',')) {
                row.push_back(word);
            }

            //init the factories/parks in map
            int i = stoi(row[4]);
            int j = stoi(row[5]);
            if (map_grid[i][j].emissions != 0) {
                map_grid[i][j].emissions += stoi(row[3]) * TO_KILOS / TICK_SIZE;
            } else {
                map_grid[i][j].emissions = stoi(row[3]) * TO_KILOS / TICK_SIZE;
            }
            map_grid[i][j].cell_type = FACTORY_T;
        }
    } else {
        fprintf(stderr, "Couldnt open file\n");
    }

    int k = 1;
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            if (map_grid[i][j].get_emissions() != 0) {
                printf("%d: %d, %d,%d\n", k, map_grid[i][j].get_emissions(), map_grid[i][j].get_x_loc(),
                       map_grid[i][j].get_y_loc());
                k++;
            }
        }
    }
                            //FIXME z argumentů pocet iterací @ Dano
    run_main_loop(map_grid, 10);


    return 0;
}

void run_main_loop(Cell **map_grid, unsigned int iterations) {
    for (auto iteration = 0; iteration < iterations; iteration++) {
        for (auto i = 0; i < SIZE; i++) {
            for (auto j = 0; j < SIZE; j++) {
                map_grid[i][j].update_neighbours(map_grid);
            }
        }
        propagate_updates(map_grid);
        print_map_grid(map_grid);
        cout << "----------------------------------" << endl;
    }
}

void propagate_updates(Cell **map_grid) {
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            map_grid[i][j].propagate_concentration();
        }
    }
}

void print_map_grid(Cell **map_grid) {
    for (auto i = 0; i < SIZE; i++) {
        cout << "|";
        for (auto j = 0; j < SIZE; j++) {
            cout << map_grid[i][j].concentration << "|";
        }
        cout << endl;
    }
}

//TODO - User input - velikost pole, cas iterace, lokace zdroju
