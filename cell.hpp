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
    int emissions; //tons per year/TICK_size = tons/hour
    int concentration;
    int next_tick_concentration;
    unsigned x_loc;
    unsigned y_loc;
    int status;

    Cell (){
        this->emissions = 0;
        this->concentration = 0;
        this->next_tick_concentration = 0;
        this->x_loc = 0;
        this->y_loc = 0;
        this->cell_type = DEFAULT_T;
        this->status = ON;
    }

    Cell(unsigned x, unsigned y, unsigned type, int wind, int _emissions, int tick_size = 365*24) {
        concentration = 50;
        next_tick_concentration = 0;
        x_loc = x;
        y_loc = y;
        cell_type = type;
        diffusion_direction_matrix = get_diffusion_direction_matrix(wind, x_loc, y_loc);
        diffusion_strength_matrix = get_diffusion_strength_matrix();
        emissions = _emissions / tick_size;
        status = ON;
    }

    void free_resources(){
        //deallocate resources
        for(auto i = 0; i < SM_HEIGHT; i++){
            for(auto j = 0; j < SM_WIDTH; j++){
                delete diffusion_direction_matrix[i][j];
            }
            delete diffusion_direction_matrix[i];
        }
        delete diffusion_direction_matrix;

        for(int i = 0; i < SM_WIDTH; i++){
            delete diffusion_strength_matrix[i];
        }
        delete diffusion_strength_matrix;
    }

    void switch_status(){
        if(status == ON){
            status = OFF;
        }
        else if(status == OFF){
            status = ON;
        }
    }

    void update_neighbours (Cell **main_grid){
        emit();
        //performance optimalization
        if(concentration != 0) {
            auto initial_concentration = concentration;
            for (auto i = 0; i < SM_HEIGHT; i++) {
                for (auto j = 0; j < SM_WIDTH; j++) {
                    //calculate the diffusion via matrix
                    auto target_diffusion = concentration * diffusion_strength_matrix[i][j];
                    float spread;
                    //if the diffusion is negative - i.e. trees take-in, do not apply the natural diffusion to spread amount
                    if(concentration < 0){
                        spread = target_diffusion;
                    }
                    //if it is the factory diffusion, lower it by 5% as the natural diffusion
                    else{
                        spread = target_diffusion * NATURAL_FALLOUT;
                    }

                    //get diffusion target
                    auto x_coord = diffusion_direction_matrix[i][j][0];
                    auto y_coord = diffusion_direction_matrix[i][j][1];

                    //diffusion out of the system is invalid
                    if (x_coord == -1 || y_coord == -1) {
                        continue;
                    }
                    //apply diffusion to other cells
                    else {
                        main_grid[x_coord][y_coord].next_tick_concentration += spread;
                    }
                }
            }
            //sub the diffused CO2
            concentration -= initial_concentration;
        }
    }

    void propagate_concentration(){
        concentration += next_tick_concentration;
        next_tick_concentration = 0;
        //diffusion cant go to negative in this model
        if(concentration < 50){
            concentration = 50;
        }
    }

    void emit(){
        //emit only if the factory is running
        if(status == ON){
            concentration += emissions;
        }
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
