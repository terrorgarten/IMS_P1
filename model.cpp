//
// Created by terrorgarten on 30.11.22.
//

#include "model.hpp"

using namespace std;

void propagate_updates();

void print_map_grid();

void do_iteration();

void print_init_factories();

void assign_factories();

void init_grid_map(int wind);

void parse_arguments(int argc, char **argv, int *i, int *wind, int *display_output);

void update_all_cells();

void run_gui_mode(int argc, char **argv);

void iteration_display();

void print_monitored_cell(unsigned int iteration);

void switch_factories();

void print_concentration_sum(int iteration);

void free_resources();

//global var for main cell grid
Cell **map_grid;
//global vars for options
int *monitored_cell;
int factory_pause = OFF;
int print_sum = OFF;
int monitor_radius = OFF;
int factory_half_pause = OFF;
ofstream outfile;

int main(int argc, char **argv) {

    //parse user input/txt file
    int i = 10, wind = NONE, display_output = CMD;
    monitored_cell = new int[2];
    monitored_cell[0] = monitored_cell[1] = -1;
    parse_arguments(argc, argv, &i, &wind, &display_output);
    cout << "Monitoring: " << monitored_cell[0] << ":" << monitored_cell[1] << endl;

    //init main cell grid
    map_grid = new Cell *[SIZE];
    init_grid_map(wind);

    // load CSV/txt file, parse it
    assign_factories();

    //show entered factories and green fields
    print_init_factories();

    //select display mode
    if (display_output == GUI) {
        run_gui_mode(argc, argv);
    } else {
        for (int iteration = 0; iteration < i; iteration++) {
            do_iteration();
            print_monitored_cell(iteration);
            print_concentration_sum(iteration);
            if (iteration % 12 == 0) {
                switch_factories();
            }
        }
        print_map_grid();
    }
    free_resources();
    return 0;
}

void free_resources() {
    if (outfile.is_open()) {
        outfile.close();
    }
    delete monitored_cell;
    //destruct map_grid
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map_grid[i][j].free_resources();
        }
        delete[] map_grid[i];
    }
    delete[] map_grid;
}

void switch_factories() {
    if (factory_pause == ON) {
        //turns off just every second factory
        if (factory_half_pause == ON) {
            int flag = ON;
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (map_grid[i][j].cell_type == FACTORY_T) {
                        if(flag == ON ){
                            map_grid[i][j].switch_status();
                            flag = OFF;
                        }
                        else {
                            flag = ON;
                        }
                    }
                }
            }
        }
        //turns off all factories
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (map_grid[i][j].cell_type == FACTORY_T) {
                    map_grid[i][j].switch_status();
                }
            }
        }
    }
}


void iteration_display() {
    GLfloat minSize = 60.0f / SIZE;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 60, 60, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, SIZE * 20, SIZE * 20);

    static int iteration_counter = 0;
    //run single iteration
    do_iteration();
    iteration_counter++;
    if (iteration_counter % 12 == 0) {
        switch_factories();
    }
    print_monitored_cell(iteration_counter);
    print_concentration_sum(iteration_counter);

    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            auto current_cell = map_grid[i][j];

            //set color
            if (current_cell.concentration == 0) {
                //grey
                glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
            } else if (current_cell.concentration <= 500 && current_cell.concentration > 0) {
                //weak yellow
                glColor4f(0.5f, 0.5f, 0.9f, 0.0f);
            } else if (current_cell.concentration <= 1000 && current_cell.concentration > 500) {
                //weak yellow
                glColor4f(0.5f, 0.5f, 0.0f, 0.0f);
            } else if (current_cell.concentration > 1000 && current_cell.concentration <= 2000) {
                //yellow
                glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
            } else if (current_cell.concentration > 2000 && current_cell.concentration <= 3000) {
                //weak red
                glColor4f(1.0f, 0.3f, 0.2f, 0.0f);
            } else if (current_cell.concentration > 3000 && current_cell.concentration <= 4000) {
                //medium red
                glColor4f(0.8f, 0.1f, 0.0f, 0.0f);
            } else if (current_cell.concentration > 4000 && current_cell.concentration <= 5000) {
                glColor4f(0.9f, 0.2f, 0.0f, 0.0f);
            } else if (current_cell.concentration > 5000 && current_cell.concentration <= 6000) {
                glColor4f(1.0f, 0.2f, 0.0f, 0.0f);
            } else if (current_cell.concentration > 6000 && current_cell.concentration <= 7000) {
                glColor4f(1.0f, 0.2f, 0.1f, 0.0f);
            } else if (current_cell.concentration > 7000) {
                glColor4f(0.5f, 0.0f, 0.0f, 0.0f);
            }

            if (current_cell.cell_type == FACTORY_T) {
                glColor4f(1.0f, 0.0f, 1.0f, 0.5f);
            }
            if (current_cell.cell_type == GREEN_T) {
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
    usleep(200000);
}

void run_gui_mode(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(SIZE * 20, SIZE * 20);
    glutCreateWindow("CO2 particle spread model");
    glutDisplayFunc(iteration_display);
    glutMainLoop();
}

void parse_arguments(int argc, char **argv, int *i, int *wind, int *display_output) {
    int opt;
    char *token;
    while ((opt = getopt(argc, argv, "i:w:gm:pso:rh")) != -1) {
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
            case 'm':
                token = strtok(optarg, ":");
                if (token != nullptr) {
                    monitored_cell[0] = stoi(token);
                    monitored_cell[1] = stoi(strtok(nullptr, ":"));
                }
                if (monitored_cell[0] < 0 || monitored_cell[0] >= SIZE || monitored_cell[1] < 0 ||
                    monitored_cell[1] >= SIZE) {
                    cerr << "Monitored cell is past grid bounds, which is " << 0 << " to " << SIZE - 1 << endl;
                    exit(INVALID_MONITOR_CELL);
                }
                break;
            case 'p':
                factory_pause = ON;
                break;
            case 's':
                print_sum = ON;
                break;
            case 'o':
                try {
                    outfile.open(optarg);
                }
                catch (...) {
                    cerr << "Could not open output file " << optarg << ". Aborting." << endl;
                    exit(BAD_FILE);
                }
                break;
            case 'r':
                if (monitored_cell[0] != -1 && monitored_cell[1] != -1) {
                    monitor_radius = ON;
                } else {
                    cerr << "-r (radius) option does not work without -m, -r must also be entered AFTER -m. -r ignored."
                         << endl;
                }
                break;
            case 'h':
                if (factory_pause == ON) {
                    factory_half_pause = ON;
                } else {
                    cerr
                            << "-h (half factories pause) must be entered with -p, -h must also be entered AFTER -p. -h ignored."
                            << endl;
                }
                break;
            case '?' :
                cerr << "Unknown option \"" << opt << "\" is ignored" << endl;
            case ':' :
            default:
                cerr << "Invalid argument, if an option is given, its argument is mandatory" << endl;
                exit(BAD_ARGS);

        }
    }
}

void init_grid_map(int wind) {
    for (int i = 0; i < SIZE; ++i)
        map_grid[i] = new Cell[SIZE + 1];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map_grid[i][j] = *new Cell(i, j, DEFAULT_T, wind, 0);
        }
    }
}

//https://www.geeksforgeeks.org/csv-file-management-using-c/
void assign_factories() {
    int count = 0;
    // File pointer
    std::fstream file;
    try {
        file.open(SOURCE_FILE, ios::in);
    }
    catch (...) {
        cerr << "Could not open input file " << SOURCE_FILE << ". Aborting." << endl;
        exit(BAD_FILE);
    }
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
            int i = stoi(row[5]);
            int j = stoi(row[4]);

            //if there is a factory on a given index, sum the emissions
            if (map_grid[i][j].cell_type == FACTORY_T) {
                map_grid[i][j].emissions += stoi(row[3]) * TO_KILOS / TICK_SIZE;
            } else {
                map_grid[i][j].emissions = stoi(row[3]) * TO_KILOS / TICK_SIZE;
            }
            if (row[2] == "\"FACTORY\"") {
                cout << "FACTORY added" << endl;
                map_grid[i][j].cell_type = FACTORY_T;
            } else if (row[2] == "\"GREEN\"") {
                cout << "Green added " << endl;
                map_grid[i][j].cell_type = GREEN_T;
            } else {
                cout << "UNKNOWN TYPE: " << row[2] << endl;

            }
        }
    } else {
        cout << "Couldn't open file" << endl;
    }
    file.close();
}

void do_iteration() {
    update_all_cells();
    propagate_updates();
}

void print_concentration_sum(int iteration) {
    if (print_sum == ON) {
        int concentration_ctr = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                concentration_ctr += map_grid[i][j].concentration;
            }
        }
        cout << "ITERATION CONCENTRATION_SUM" << endl << iteration << " " << concentration_ctr << endl;
        if (outfile.is_open()) {
            outfile << iteration << " " << concentration_ctr << endl;
        }
    }
}

void print_monitored_cell(unsigned int iteration) {
    if (monitored_cell[0] != -1 || monitored_cell[1] != -1) {
        int monitor_value;
        if (monitor_radius == ON) {
            monitor_value = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    monitor_value += map_grid[monitored_cell[i]][monitored_cell[j]].concentration;
                }
            }
        } else {
            monitor_value = map_grid[monitored_cell[0]][monitored_cell[1]].concentration;
        }
        cout << "MONITOR (" << monitored_cell[0] << ":" << monitored_cell[1] << ")\titeration "
             << "\tvalue " << endl << iteration << " " << monitor_value
             << endl;
        if (outfile.is_open()) {
            outfile << iteration << "," << map_grid[monitored_cell[0]][monitored_cell[1]].concentration << endl;
        }
    }
}

void update_all_cells() {
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            map_grid[i][j].update_neighbours(map_grid);
        }
    }
}

void propagate_updates() {
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            map_grid[i][j].propagate_concentration();
        }
    }
}

void print_init_factories() {
    int k = 1;
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            if (map_grid[i][j].get_emissions() != 0) {
                printf("%d: %d, %d,%d\n", k, map_grid[i][j].get_emissions(), map_grid[i][j].get_x_loc(),
                       map_grid[i][j].get_y_loc());
                k++;
            }
        }
    }
}

void print_map_grid() {
    for (auto i = 0; i < SIZE; i++) {
        cout << "|";
        for (auto j = 0; j < SIZE; j++) {
            cout << map_grid[i][j].concentration << "|";
        }
        cout << endl;
    }
}
