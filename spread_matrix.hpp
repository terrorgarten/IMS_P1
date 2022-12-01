//
// Created by terrorgarten on 01.12.22.
//

#ifndef IMS_P1_SPREAD_MATRIX_H
#define IMS_P1_SPREAD_MATRIX_H

#endif //IMS_P1_SPREAD_MATRIX_H

#include "definitions.hpp"
#include <iostream>
#include <tuple>


namespace std {

//typedef tuple<int, int> offset_t;

    int ***create2DArray(unsigned height, unsigned width) {
       int ***array2D = NULL;
        array2D = new int **[height];

        for (unsigned h = 0; h < height; h++) {
            array2D[h] = new int *[width];

            for (unsigned w = 0; w < width; w++) {
                    array2D[h][w] = new int[DIMENSION];
                    array2D[h][w][0] = 0;
                    array2D[h][w][1] = 0;
            }
        }
        return array2D;
    }


    int ***get_spread_matrix(int wind) {
        int ***matrix = create2DArray(SM_HEIGHT, SM_WIDTH);
        switch (wind) {
            case NONE:
                matrix[0][0][0] = -1;
                matrix[0][0][1] = -1;
        }
        return matrix;
    }
}