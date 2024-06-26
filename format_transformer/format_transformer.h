#ifndef _FORMAT_TRANSFORMER_H
#define _FORMAT_TRANSFORMER_H

char ** load_data(FILE *in, Maze *maze);
int is_crossing (int row, int col, char ** arr);
void find_neighbours(int row, int col, char ** arr, Maze * maze, FILE *out);
void transform_maze_format(FILE *in, FILE *out, Maze *maze);

#endif
