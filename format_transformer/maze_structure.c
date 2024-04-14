#include <stdlib.h>
#include <stdio.h>

#include "maze_structure.h"

Maze initialize_Maze() {
    Maze maze;

    maze.rows = maze.cols = -1;
    maze.P_r = maze.P_c = -1;
    maze.K_r = maze.K_c = -1;

    return maze;
}

Maze read_Maze(FILE *in) {
    Maze maze;

    fscanf(in, "%i", &(maze.rows));
    fscanf(in, "%i", &(maze.cols));
    fscanf(in, "%i", &(maze.P_r));
    fscanf(in, "%i", &(maze.P_c));
    fscanf(in, "%i", &(maze.K_r));
    fscanf(in, "%i", &(maze.K_c));
}

void fprint_Maze (FILE *out, Maze * maze) {
    fprintf(out, "%i %i %i %i %i %i\n", maze->rows, maze->cols, maze->P_r, maze->P_c, maze->K_r, maze->K_c);
}
