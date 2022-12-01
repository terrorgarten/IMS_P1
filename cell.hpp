//
// Created by terrorgarten on 01.12.22.
//
#include "spread_matrix.hpp"
#include "definitions.hpp"

#ifndef IMS_P1_CELL_H
#define IMS_P1_CELL_H

#endif //IMS_P1_CELL_H

#define FACTORY_T 1
#define DEFAULT_T 0
#define FORREST_T 2

using namespace std;

class Cell {
private:
    unsigned int cell_type;
    int ***spread_matrix;
public:
    unsigned int emissions;
    unsigned x_loc;
    unsigned y_loc;

    Cell(unsigned x, unsigned y, unsigned type, int wind) {
        x_loc = x;
        y_loc = y;
        cell_type = type;
        spread_matrix = get_spread_matrix(wind);
    }

    int get_x_loc(){
        return x_loc;
    }

    int get_y_loc(){
        return y_loc;
    }

    void print_spread_matrix(){
        for(int i = 0; i < SM_HEIGHT; i ++) {
            for (int j = 0; j < SM_HEIGHT; j++){
                cout << "\t" << spread_matrix[i][j][0] << " " << spread_matrix[i][j][1] << "\t|";
            }
            cout << endl;
        }
    }
};
