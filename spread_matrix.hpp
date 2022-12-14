//
// Created by terrorgarten on 01.12.22.
//

#ifndef IMS_P1_SPREAD_MATRIX_H
#define IMS_P1_SPREAD_MATRIX_H

#endif //IMS_P1_SPREAD_MATRIX_H

#include "definitions.hpp"

using namespace std;
//typedef tuple<int, int> offset_t;

int ***create_3D_array(unsigned height, unsigned width) {
    int ***array3D = NULL;
    array3D = new int **[height];

    for (unsigned h = 0; h < height; h++) {
        array3D[h] = new int *[width];

        for (unsigned w = 0; w < width; w++) {
            array3D[h][w] = new int[DIMENSION];
            array3D[h][w][0] = 0;
            array3D[h][w][1] = 0;
        }
    }
    return array3D;
}

void fill_diffusion_direction_matrix(int ***matrix, unsigned int x_loc, unsigned int y_loc, int x_shift, int y_shift) {
    for (unsigned int i = 0; i < SM_WIDTH; i++) {
        for (unsigned int j = 0; j < SM_HEIGHT; j++) {
            matrix[i][j][0] = i + x_loc + x_shift;
            matrix[i][j][1] = j + y_loc + y_shift;
            //if the index is out of the grid, set INVALID_INDEX
            if (matrix[i][j][0] >= SIZE || matrix[i][j][0] < 0 || matrix[i][j][1] >= SIZE || matrix[i][j][1] < 0) {
                matrix[i][j][0] = INVALID_INDEX;
                matrix[i][j][1] = INVALID_INDEX;
            }
        }
    }
}


int ***get_diffusion_direction_matrix(int wind, unsigned int x, unsigned int y) {
    int ***matrix = create_3D_array(SM_HEIGHT, SM_WIDTH);
    int x_shift, y_shift = 0;
    switch (wind) {
        case NONE:
            x_shift = -1;
            y_shift = -1;
            break;

        case WEST:
            x_shift = -1;
            y_shift = 0;
            break;

        case EAST:
            x_shift = -1;
            y_shift = -2;
            break;

        case NORTH:
            x_shift = 0;
            y_shift = -1;
            break;

        case SOUTH:
            x_shift = -2;
            y_shift = -1;
            break;

        case NORTH_WEST:
            x_shift = 0;
            y_shift = 0;
            break;

        case NORTH_EAST:
            x_shift = 0;
            y_shift = -2;
            break;

        case SOUTH_WEST:
            x_shift = -2;
            y_shift = -0;
            break;

        case SOUTH_EAST:
            x_shift = -2;
            y_shift = -2;
            break;
        default:
            cerr
                    << "Wrong wind type entered: please use only numbers ranging from 0 to 8. See help for definitions. Aborting."
                    << endl;
            exit(INVALID_WIND_DIR);
    }
    fill_diffusion_direction_matrix(matrix, x, y, x_shift, y_shift);
    return matrix;
}


float **get_diffusion_strength_matrix() {
    auto **matrix = new float *[SM_HEIGHT];
    for (int i = 0; i < SM_HEIGHT; i++) {
        matrix[i] = new float[SM_WIDTH];
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = 0.0;
        }
    }
    matrix[0][0] = 0.075;
    matrix[0][1] = 0.125;
    matrix[0][2] = 0.075;

    matrix[1][0] = 0.125;
    matrix[1][1] = 0.2;
    matrix[1][2] = 0.125;

    matrix[2][0] = 0.075;
    matrix[2][1] = 0.125;
    matrix[2][2] = 0.075;
    return matrix;
}