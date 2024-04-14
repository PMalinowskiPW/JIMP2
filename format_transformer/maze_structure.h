#ifndef _MAZE_STRUCTURE_H
#define _MAZE_STRUCTURE_H

typedef struct {
    int rows, cols;
    int P_r, P_c;
    int K_r, K_c;

} Maze;

Maze initialize_Maze();

Maze read_Maze(FILE *in);

void fprint_Maze (FILE *out, Maze * maze);

#endif
