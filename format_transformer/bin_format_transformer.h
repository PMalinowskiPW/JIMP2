#ifndef _BIN_FORMAT_TRANSFORMER_H
#define _BIN_FORMAT_TRANSFORMER_H

void transform_maze_format_bin(Array2 *A, FILE *out, Maze *maze);
int is_binary(FILE *in);

#endif
