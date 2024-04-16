#ifndef _ARRAY_STRUCTURE_H
#define _ARRAY_STRUCTURE_H

#define ARR_SIZE 20

typedef struct
{
    short **arr;

    short *row, *col;
    short *row_pvs, *col_pvs;
    short *len_to_start;
    short *visited;
    short *path;
    short *exists;

    int size;
} Array;

Array initialize_Array();

void resize_array (Array * A, int times);

void write_node_to_arr(Array * A, int tmp_idx, int i, short *buffer, int curr_idx);

int find_node_in_arr(Array * A, int row, int col);

#endif
