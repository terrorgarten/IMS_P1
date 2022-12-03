//
// Created by terrorgarten on 01.12.22.
//

#ifndef IMS_P1_DEFINITIONS_H
#define IMS_P1_DEFINITIONS_H

#endif //IMS_P1_DEFINITIONS_H

/* CELL TYPES */
#define DEFAULT_T 0
#define FACTORY_T 1
#define GREEN_T 2
#define BORDER_T 3

/* WIND TYPES */

#define NONE 0
#define SIZE 40 //40*40 grid
#define NORTH 1
#define SOUTH 2
#define EAST 3
#define WEST 4
#define NORTH_EAST 5
#define NORTH_WEST 6
#define SOUTH_EAST 7
#define SOUTH_WEST 8

/* Spread matrix */
#define SM_SIZE 3
#define SM_HEIGHT SM_SIZE
#define SM_WIDTH SM_SIZE
#define DIMENSION 2
#define INVALID_INDEX (-1)
/* ERRORS */
#define INVALID_WIND_DIR 2

/* EMISSION COUNTING */
#define TICK_SIZE 8760 //hours in year
#define TO_KILOS 1000