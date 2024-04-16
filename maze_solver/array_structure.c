#include <stdio.h>
#include <stdlib.h>

#include "array_structure.h"

Array initialize_Array()
{
    Array A;

    A.size = ARR_SIZE;

    A.arr = malloc(5 * sizeof(short*));
    for (int i = 0; i < 5; i++)
        A.arr[i] = malloc(ARR_SIZE * sizeof(short));

    for (int i = 0; i < 5; i++) 
        for (int j = 0; j < ARR_SIZE; j++) {
            if (i == 2)
                A.arr[i][j]= -1;
            else 
                A.arr[i][j] = 0;
        }

    A.row = A.arr[0];
    A.visited = A.arr[0];
    A.col = A.arr[1];
    A.row_pvs = A.arr[2];
    A.exists = A.arr[2];
    A.col_pvs = A.arr[3];
    A.len_to_start = A.arr[4];
    A.path = A.arr[4];

    return A;

}

void resize_array (Array * A, int times) {
    for (int i = 0; i < 5; i++){ 
        short *new_arr = realloc (A->arr[i] , times * A->size * sizeof(short));
        A->arr[i] = new_arr;
    }

    for (int i = 0; i < 5; i++){
        for (int j = A->size; j < A->size * times; j++){

            if (i == 2)
                A->arr[i][j] = -1;
            else 
                A->arr[i][j] = 0;

        }
    }
    A->row = A->arr[0];
    A->visited = A->arr[0];
    A->col = A->arr[1];
    A->row_pvs = A->arr[2];
    A->exists = A->arr[2];
    A->col_pvs = A->arr[3];
    A->len_to_start = A->arr[4];
    A->path = A->arr[4];

     A->size *= times;
}


//zwraca indeks wezla lub ujemna (!) wartosc indeksu pierwszego wolnego pola w arr, jesli dany wezeł jeszcze nie zostal zapisany w arr
int find_node_in_arr(Array * A, int row, int col) {

    int idx;
    //czy w arr istnieje wezel o danych row i col
    for (int i = 0; i < A->size; i++) 
        if (A->row[i] == row && A->col[i] == col) {
            idx = i;
            return idx;
        }

    //jesli nie, ujemny indeks pierwszego znalezionego wolnego pola 
    for (int i = 0; i < A->size; i++) 
        if (A->exists[i] == -1) {
            idx = -i;
            return idx;
        }

    //jesli nie znaleziono wolnego pola, nalezy powiekszyc tablice 
    idx = -A->size;
    resize_array (A, 2);

return idx;
}

void write_node_to_arr(Array * A, int tmp_idx, int i, short *buffer, int curr_idx) { 
    if (tmp_idx < 0)
    {   
        A->row[-tmp_idx] = -buffer[i];
        A->col[-tmp_idx] = buffer[i + 1];
        A->row_pvs[-tmp_idx] = buffer[0];
        A->col_pvs[-tmp_idx] = buffer[1];
        A->path[-tmp_idx] = A->len_to_start[curr_idx] + buffer[i + 2];
    }
    else
    {
        if (A->row[tmp_idx] < 0 && A->len_to_start[curr_idx] + buffer[i + 2] < A->len_to_start[tmp_idx])
        {
            A->len_to_start[tmp_idx] = A->len_to_start[curr_idx] + buffer[i + 2];
            A->row_pvs[tmp_idx] = A->row[curr_idx];
            A->col_pvs[tmp_idx] = A->col[curr_idx];
        }
    }
}
