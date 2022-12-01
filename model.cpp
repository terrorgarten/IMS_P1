//
// Created by terrorgarten on 30.11.22.
//
#include "model.hpp"

using namespace std;

int main(int argc, char **argv) {
    Cell sample_cell(4, 4, 0, 0);
    sample_cell.print_diffusion_direction_matrix();
    sample_cell.print_diffusion_strength_matrix();
    return 0;
}
