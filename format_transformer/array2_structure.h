#ifndef _ARRAY2_STRUCTURE_H
#define _ARRAY2_STRUCTURE_H

typedef struct
{
    char **arr;
    short rows, cols, x_p, y_p, x_k, y_k;
    int count;
} Array2;

Array2 initialize_Array( FILE *in);

void read_binary_file( FILE *in , Array2 * A);

#endif
