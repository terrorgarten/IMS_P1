# Emission spread model for REZZO1 CO2 sources in Prague

## Description
Model for C02 emission spread based on actual data of REZZO1 static CO2 sources in Prague. Allows input of wind. Uses 2D cellular automata and glut library for visualisation.
Default lattice is 40x40. All input can be changed via editing data/indexes.csv file.
## Dependencies
- ```<GL/glut.h>``` installed
- any linux system

## Compilation 
```make```

## Running
```$./ims [-g] [-p] [-h] [-o <file>] [-s] [-w <wind>] [-i <iterations>] [-m <i1:i2>] ```
- [-g] - runs in gui mode
- [-p] - all factories have 12h workday instead of 24, which is default
- [-h] - every second factory uses the 12h workday. Must be combined with -p
- [-o <file>] - prints -s and -m output to a file
- [-s] - prints sum of all emisions with each iteration
- [-w <wind>] - selects a wind direstion: NONE 0 NORTH 1 SOUTH 2 EAST 3 WEST 4 NORTH_EAST 5 NORTH_WEST 6 SOUTH_EAST 7 SOUTH_WEST 8
- [-i <iterations>] - Runs predefined count of iterations. Does not work in gui mode, because it is indefinite.
- [-m x:y] - Monitors cell and prints its concentration to stdout
## Examples
- ```./model -g``` run in gui mode
- ```./model -i 40``` run 40 iterations - does not work in gui mode
- ```./model -g -m 20:20```monitor cell x = 20, y = 20
- ```./model -p -h``` each factory uses 12h workday instead of 24, which is default and only half of the factories have this attribute.
