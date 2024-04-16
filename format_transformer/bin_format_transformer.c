#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "maze_structure.h"
#include "array2_structure.h"
#include "format_transformer.h"
#include "bin_format_transformer.h"

void transform_maze_format_bin(Array2 *A, FILE *out, Maze *maze) {
    int line_counter = 2; 
    int row, col;
    row = col = 1;

    while (row < maze->rows) {
        if (is_crossing(row, col, A->arr)){
            line_counter++;
        }    
        
        if (col == maze->cols -2){
            col = 1;
            row += 2; 
        } else 
            col += 2;
    }

    fprint_maze_data (out, maze, line_counter);

    row = col = 1;
    while (row < maze->rows) {
        //dla 'P' w górnej i lewej ścianie
        if ((row -1 == maze->P_r && col == maze->P_c) || (row == maze->P_r && col -1 == maze->P_c))
            fprintf(out, "%i %i %i %i 1 0 0 0 0 0 0 0 0 0\n", maze->P_r, maze->P_c, row, col);

        //dla skrzyżowań 
        find_neighbours(row, col, A->arr, maze, out);

        //dla 'P' w prawej i dolnej ścianie
        if ((row +1 == maze->P_r && col == maze->P_c) || (row == maze->P_r && col +1 == maze->P_c))
            fprintf(out, "%i %i %i %i 1 0 0 0 0 0 0 0 0 0\n", maze->P_r, maze->P_c, row, col);
        
        if (col == maze->cols -2){
            col = 1;
            row += 2; 
        } else 
            col += 2;
    }
}



int is_binary(FILE *in) {

    int bin = 0;
    int c;
    while ((c = fgetc(in)) != EOF) {
        if ((c < 7 || c > 13) && (c < 32 || c > 126)) {
            bin = 1;
            break;
        }
    }
    fseek(in, 0, SEEK_SET);
    return bin;
}
