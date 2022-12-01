//
// Created by terrorgarten on 01.12.22.
//

#ifndef IMS_P1_SPREAD_MATRIX_H
#define IMS_P1_SPREAD_MATRIX_H

#endif //IMS_P1_SPREAD_MATRIX_H

#include "definitions.hpp"
#include <iostream>
#include <tuple>


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


int ***get_diffusion_direction_matrix(int wind, unsigned x, unsigned y) {
    int ***matrix = create_3D_array(SM_HEIGHT, SM_WIDTH);
    switch (wind) {
        case NONE:
            matrix[0][0][0] = x - 1;
            matrix[0][0][1] = y - 1;
            matrix[0][1][0] = x - 1;
            matrix[0][1][1] = y;
            matrix[0][2][0] = x - 1;
            matrix[0][2][1] = y + 1;
            matrix[1][0][0] = x;
            matrix[1][0][1] = y - 1;
            matrix[1][1][0] = x;
            matrix[1][1][1] = y;
            matrix[1][2][0] = x;
            matrix[1][2][1] = y + 1;
            matrix[2][0][0] = x + 1;
            matrix[2][0][1] = y - 1;
            matrix[2][1][0] = x +1;
            matrix[2][1][1] = y;
            matrix[2][2][0] = x + 1;
            matrix[2][2][1] = y + 1;
            break;
    }
    return matrix;
}


float **get_diffusion_strength_matrix(){
    float **matrix = new float*[SM_HEIGHT];
    for(int i = 0; i < SM_HEIGHT; i++){
        matrix[i] = new float[SM_WIDTH];
        for(int j = 0; j < 4; j++){
            matrix[i][j] = 0.0;
        }
    }
    matrix[0][0] = 0.05;
    matrix[0][1] = 0.1;
    matrix[0][2] = 0.05;
    matrix[1][0] = 0.1;
    matrix[1][1] = 0.4;
    matrix[1][2] = 0.1;
    matrix[2][0] = 0.05;
    matrix[2][1] = 0.1;
    matrix[2][2] = 0.05;
    return matrix;
}