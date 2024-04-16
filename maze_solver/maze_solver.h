#ifndef _MAZE_SOLVER_H
#define _MAZE_SOLVER_H

#include "array_structure.h"
#include "maze_structure.h"

int del_blind_node_from_arr(Array *A, short *buffer, int curr_idx,Maze *maze);

void del_node_from_arr(FILE *in, Array *A, Maze *maze, int p);

void find_answer(short end_idx, Maze * maze, Array * A);

void print_answer(int start_idx, Maze * maze, Array * A);

#endif
