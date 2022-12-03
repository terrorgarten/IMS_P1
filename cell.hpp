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
    int ***diffusion_direction_matrix{};
    float **diffusion_strength_matrix{};


public:
    unsigned int cell_type;
    unsigned int emissions; //tons per year/TICK_size = tons/hour
    unsigned int concentration;
    unsigned int next_tick_concentration;
    unsigned x_loc;
    unsigned y_loc;

    Cell (){
        this->emissions = 0;
        this->concentration = 0;
        this->next_tick_concentration = 0;
        this->x_loc = 0;
        this->y_loc = 0;
        this->cell_type = DEFAULT_T;
    }

    Cell(unsigned x, unsigned y, unsigned type, int wind, unsigned int _emissions, int tick_size = 365*24) {
        concentration = 0;
        next_tick_concentration = 0;
        x_loc = x;
        y_loc = y;
        cell_type = type;
        diffusion_direction_matrix = get_diffusion_direction_matrix(wind, x_loc, y_loc);
        diffusion_strength_matrix = get_diffusion_strength_matrix();
        emissions = _emissions / tick_size;
    }

    void update_neighbours (Cell **main_grid){
        //TODO pridat prirozeny ubytek - nasobit 0,9 napr
        emit();
        //performance optimalization
        if(concentration != 0) {
            auto initial_concentration = concentration;
            for (auto i = 0; i < SM_HEIGHT; i++) {
                for (auto j = 0; j < SM_WIDTH; j++) {
                    auto spread = static_cast<float>(concentration) * diffusion_strength_matrix[i][j];  //TODO tady
                    auto x_coord = diffusion_direction_matrix[i][j][0];
                    auto y_coord = diffusion_direction_matrix[i][j][1];

                    //diffusion out of the system
                    if (x_coord == -1 || y_coord == -1) {
                        cout << x_loc << ":" << y_loc << " --- Cant emmit to " << x_coord << ":" << y_coord << endl;
                        continue;
                    }
                        //diffusion to other cells
                    else {
                        main_grid[x_coord][y_coord].next_tick_concentration += static_cast<int>(spread);
                        cout << x_loc << ":" << y_loc << " --- Emmiting " << spread << " to " << x_coord << ":"
                             << y_coord << endl;
                    }
                }
            }
            concentration -= initial_concentration;
        }
    }

    void propagate_concentration(){
        concentration += next_tick_concentration;
        next_tick_concentration = 0;
    }

    void emit(){
        concentration += emissions;
    }

    unsigned int get_x_loc() const {
        return x_loc;
    }

    unsigned int get_emissions() const {
        return emissions;
    }

    unsigned int get_y_loc() const {
        return y_loc;
    }

    void print_info() const{
        printf("Type:%d Emissions: %d\n", this->cell_type, this->emissions);
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
