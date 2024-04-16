#include <stdlib.h>
#include <stdio.h>

#include "array2_structure.h"

Array2 initialize_Array( FILE *in)
{
    Array2 A;
    fseek(in, 5, SEEK_CUR);
    fread(&A.rows, sizeof(char), 2, in);
    fread(&A.cols, sizeof(char), 2, in);
    fread(&A.x_p, sizeof(char), 2, in);
    fread(&A.y_p, sizeof(char), 2, in);
    fread(&A.x_k, sizeof(char), 2, in);
    fread(&A.y_k, sizeof(char), 2, in);
    fseek(in, 12, SEEK_CUR);
    fread(&A.count, sizeof(char), 4, in);
    fseek(in, 7, SEEK_CUR);

    A.arr = malloc(A.cols * sizeof(char *));
    for (int i = 0; i < A.cols; i++)
        A.arr[i] = malloc(A.rows * sizeof(char));
    return A;

}

void read_binary_file( FILE *in , Array2 * A) {
    int col=0;
    int row=0;



    for (int j = 0; j < A->count; j++) {
        int n[3] = {0};
        for (int i = 0; i < 3; i++) {
            fread(&n[i], sizeof(char), 1, in);
        }
        for (int k = 0; k <= n[2]; k++) {
            if (row == A->cols) {
                col++;
                row = 0;
            }
            A->arr[col][row] = n[1];
            row++;
        }
    }

    A->arr[A->y_p - 1][A->x_p - 1] = 'P';
    A->arr[A->y_k - 1][A->x_k - 1] = 'K';

    fclose(in);
}
