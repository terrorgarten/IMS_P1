//
// Created by terrorgarten on 30.11.22.
//

#include "model.hpp"

using namespace std;

void propagate_updates(Cell **map_grid);

void print_map_grid(Cell **map_grid);

void run_main_loop(Cell **map_grid, unsigned int iterations);

void print_init_factories(Cell **map_grid);

void assign_factories(Cell **map_grid);

void init_gridmap(Cell **map_grid, int wind);

void parse_arguments(int argc, char **argv, int* i, int* wind);

int main(int argc, char **argv) {
    //parse user input/txt file
    // load CSV/txt file, parse it
    Cell **map_grid = new Cell *[SIZE];
    int i = 10,wind = 0;

    parse_arguments(argc, argv, &i, &wind);

    init_gridmap(map_grid, wind);

    assign_factories(map_grid);

    print_init_factories(map_grid);

    //FIXME z argumentů pocet iterací @ Dano
    run_main_loop(map_grid, i);

    return 0;
}

void parse_arguments(int argc, char **argv, int* i, int* wind) {

    int opt;
    while ((opt = getopt(argc, argv, "i:w:")) != -1)
    {
        switch (opt){
            case 'i' :
                *i = stoi(optarg);
                break;
            case 'w' :
                *wind = stoi(optarg);
                break;

            case '?' :
            case ':' :
            default:
                fprintf(stderr,"Invalid argument, if an option is given, its argument is mandatory\n");
                exit(1);
                break;
        }
    }
}

void init_gridmap(Cell **map_grid, int wind) {
    for (int i = 0; i < SIZE; ++i)
        map_grid[i] = new Cell[SIZE + 1];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {                            //TODO vitr z argumentu
            map_grid[i][j] = *new Cell(i, j, DEFAULT_T, wind, 0);
        }
    }
}

//https://www.geeksforgeeks.org/csv-file-management-using-c/
void assign_factories(Cell **map_grid){
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

void print_init_factories(Cell **map_grid) {
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
