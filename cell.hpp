//
// Created by terrorgarten on 01.12.22.
//
#include "spread_matrix.hpp"
#include "definitions.hpp"

#ifndef IMS_P1_CELL_H
#define IMS_P1_CELL_H

#endif //IMS_P1_CELL_H

using namespace std;

class Cell {
private:
    unsigned int cell_type;
    int ***diffusion_direction_matrix;
    float **diffusion_strength_matrix;
public:
    unsigned int emissions;
    unsigned x_loc;
    unsigned y_loc;

    Cell(unsigned x, unsigned y, unsigned type, int wind) {
        x_loc = x;
        y_loc = y;
        cell_type = type;
        diffusion_direction_matrix = get_diffusion_direction_matrix(wind, x_loc, y_loc);
        diffusion_strength_matrix = get_diffusion_strength_matrix();
    }

    void update_neighbours (Cell **main_grid){
        //FIXME cyklus - @Matej
        main_grid[diffusion_direction_matrix[0][0][0]][diffusion_direction_matrix[0][0][1]].emissions += emissions * diffusion_strength_matrix[0][0];
    }



    int get_x_loc() {
        return x_loc;
    }

    int get_y_loc() {
        return y_loc;
    }

    void print_diffusion_direction_matrix() {
        cout << "Wind diffusion direction" << endl;
        for (int i = 0; i < SM_HEIGHT; i++) {
            for (int j = 0; j < SM_HEIGHT; j++) {
                cout << "\t" << diffusion_direction_matrix[i][j][0] << " " << diffusion_direction_matrix[i][j][1] << "\t|";
            }
            cout << endl;
        }
    }

    void print_diffusion_strength_matrix(){
        cout << "Diffusion strength" << endl;
        for (int i = 0; i < SM_HEIGHT; i++) {
            for (int j = 0; j < SM_HEIGHT; j++) {
                cout << "\t" << diffusion_strength_matrix[i][j] << "\t|";
            }
            cout << endl;
        }
    }
};
