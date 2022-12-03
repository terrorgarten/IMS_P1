//
// Created by terrorgarten on 30.11.22.
//

#include "model.hpp"

using namespace std;

void propagate_updates(Cell **map_grid);

void print_map_grid(Cell **map_grid);

void run_main_loop(Cell **map_grid, unsigned int iterations);

void print_init_factories(Cell **map_grid);

void assign_factories(Cell **map_grid);

void init_gridmap(Cell **map_grid, int wind);

void parse_arguments(int argc, char **argv, int *i, int *wind, int *display_output);

void update_all_cells(Cell **map_grid);

void run_gui_mode(Cell **map_grid, int argc, char **argv);

void iteration_display();

Cell **map_grid;



int main(int argc, char **argv) {
    //parse user input/txt file
    // load CSV/txt file, parse it
    map_grid = new Cell *[SIZE];
    int i = 10, wind = NONE, display_output = CMD;

    parse_arguments(argc, argv, &i, &wind, &display_output);

    init_gridmap(map_grid, wind);

    assign_factories(map_grid);

    print_init_factories(map_grid);

    if(display_output == GUI){
        run_gui_mode(map_grid, argc, argv);
    }
    else{
        run_main_loop(map_grid, i);
        print_map_grid(map_grid);
    }

    return 0;
}


void iteration_display() {
    GLfloat minSize = 60.0f/SIZE;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 60, 60, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, SIZE * 20, SIZE * 20);

    run_main_loop(map_grid, 1);

    for(auto i = 0; i < SIZE; i++){
        for(auto j = 0; j < SIZE; j++){
            auto current_cell = map_grid[i][j];

            //set color
            if(current_cell.concentration == 0){
                //grey
                glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
            }
            else if(current_cell.concentration <= 1000 && current_cell.concentration > 0){
                //weak yellow
                glColor4f(0.5f, 0.5f, 0.0f, 0.0f);
            }
            else if(current_cell.concentration > 1000 && current_cell.concentration <= 2000){
                //yellow
                glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
            }
            else if(current_cell.concentration > 2000 && current_cell.concentration <= 3000){
                //weak red
                glColor4f(0.5f, 0.0f, 0.0f, 0.0f);
            }
            else if(current_cell.concentration > 3000 && current_cell.concentration <=4000){
                //medium red
                glColor4f(0.8f, 0.1f, 0.0f, 0.0f);
            }
            else if(current_cell.concentration > 4000 && current_cell.concentration <= 5000){
                glColor4f(0.9f, 0.2f, 0.0f, 0.0f);
            }
            else if(current_cell.concentration > 5000 && current_cell.concentration <= 6000){
                glColor4f(1.0f, 0.2f, 0.0f, 0.0f);
            }
            else if(current_cell.concentration > 6000 && current_cell.concentration <= 7000){
                glColor4f(1.0f, 0.2f, 0.1f, 0.0f);
            }
            else if(current_cell.concentration > 7000){
                glColor4f(1.0f, 0.3f, 0.2f, 0.0f);
            }
            else if(current_cell.concentration < 0){
                glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
            }

            if(current_cell.cell_type == FACTORY_T){
                glColor4f(1.0f, 0.0f, 1.0f, 0.5f);
            }
            if(current_cell.cell_type == GREEN_T){
                glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
            }

            glBegin(GL_QUADS); // 2x2 pixels
            glVertex2f(0.0f + minSize * j, 0.0f + minSize * i);
            glVertex2f(0.0f + minSize * (j + 1), 0.0f + minSize * i);
            glVertex2f(0.0f + minSize * (j + 1), 0.0f + minSize * (i + 1));
            glVertex2f(0.0f + minSize * j, 0.0f + minSize * (i + 1));
            glEnd();

        }
    }
    glutSwapBuffers();
    glutPostRedisplay();
    sleep(1);
}

void run_gui_mode(Cell **map_grid, int argc, char **argv){
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(SIZE*20, SIZE*20);
    glutCreateWindow("IMS - Wildfire simulation - xmlkvy00, xmudry01");
    glutDisplayFunc(iteration_display);
    glutMainLoop();
}


void parse_arguments(int argc, char **argv, int *i, int *wind, int *display_output) {

    int opt;
    while ((opt = getopt(argc, argv, "i:w:g")) != -1) {
        switch (opt) {
            case 'i' :
                *i = stoi(optarg);
                break;
            case 'w' :
                *wind = stoi(optarg);
                break;
            case 'g':
                *display_output = GUI;
                break;
            case '?' :
            case ':' :
            default:
                fprintf(stderr, "Invalid argument, if an option is given, its argument is mandatory\n");
                exit(BAD_ARGS);

        }
    }
}

void init_gridmap(Cell **map_grid, int wind) {
    for (int i = 0; i < SIZE; ++i)
        map_grid[i] = new Cell[SIZE + 1];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {                            //TODO vitr z argumentu
            map_grid[i][j] = *new Cell(i, j, DEFAULT_T, wind, 0);
        }
    }
}

//https://www.geeksforgeeks.org/csv-file-management-using-c/
void assign_factories(Cell **map_grid) {
    int count = 0;
    // File pointer
    std::fstream file;
    file.open("data/indexes.csv", ios::in);

    vector<string> row;
    string line, word, temp;
    if (file.is_open()) {
        while (getline(file, line)) {
            //skip header
            count++;
            if (count == 1) {
                continue;
            }

            row.clear();
            stringstream str(line);

            while (getline(str, word, ',')) {
                row.push_back(word);
            }

            //init the factories/parks in map
            int i = stoi(row[4]);
            int j = stoi(row[5]);

            if (map_grid[i][j].emissions != 0) {
                map_grid[i][j].emissions += stoi(row[3]) * TO_KILOS / TICK_SIZE;
            } else {
                map_grid[i][j].emissions = stoi(row[3]) * TO_KILOS / TICK_SIZE;
            }
            if(row[2] == "\"FACTORY\""){
                cout << "FACTORY added" << endl;
                map_grid[i][j].cell_type = FACTORY_T;
            }
            else if(row[2] ==  "\"GREEN\""){
                cout << "Green added " << endl;
                map_grid[i][j].cell_type = GREEN_T;
            }
            else{
                cout << "UNKNOWN TYPE: " << row[2] << endl;

            }
        }
    } else {
        fprintf(stderr, "Couldn't open file\n");
    }
}

void run_main_loop(Cell **map_grid, unsigned int iterations) {
    for (auto iteration = 0; iteration < iterations; iteration++) {
        update_all_cells(map_grid);
        propagate_updates(map_grid);
    }
}

void update_all_cells(Cell **map_grid){
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            map_grid[i][j].update_neighbours(map_grid);
        }
    }
}

void propagate_updates(Cell **map_grid) {
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            map_grid[i][j].propagate_concentration();
        }
    }
}

void print_init_factories(Cell **map_grid) {
    int k = 1;
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            if (map_grid[i][j].get_emissions() != 0) {
                printf("%d: %d, %d,%d\n", k, map_grid[i][j].get_emissions(), map_grid[i][j].get_x_loc(),
                       map_grid[i][j].get_y_loc());
                k++;
            }
        }
    }
}

void print_map_grid(Cell **map_grid) {
    for (auto i = 0; i < SIZE; i++) {
        cout << "|";
        for (auto j = 0; j < SIZE; j++) {
            cout << map_grid[i][j].concentration << "|";
        }
        cout << endl;
    }
}

//TODO - User input - velikost pole, cas iterace, lokace zdroju
