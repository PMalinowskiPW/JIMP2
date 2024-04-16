#include <stdio.h>
#include <stdlib.h>

#include "maze_structure.h"
#include "file_reader.h"
#include "array_structure.h"
#include "maze_solver.h"


int main(int argc, char **argv)
{
    FILE *in = fopen("adjacency_list.txt", "r");

    if (in == NULL)
    {
        fprintf(stderr, "Błąd, nie można otworzyć pliku wejściowego: 'adjacency_list.txt'\n");
        return 0;
    }

    short buffer[2 + 4 * 3];

    int curr_idx = 0;
    int tmp_idx = 0;
    int minimum = 0;
    int k=0;

    Maze maze = read_Maze(in);
    Array A = initialize_Array();

    // start, 'P'
    A.row[curr_idx] = maze.P_r;
    A.col[curr_idx] = maze.P_c;
    A.exists[curr_idx] = 0;

    while (!(abs(A.row[curr_idx]) == maze.K_r && A.col[curr_idx] == maze.K_c))
    {
        // dla oszczędności pamięci nieodwiedzone pola oznaczamy przez zapisanie ich indeksów ze znakiem "-"
        A.row[curr_idx] = abs(A.row[curr_idx]);
        A.col[curr_idx] = abs(A.col[curr_idx]);

        read_file_line (in, A.row[curr_idx], A.col[curr_idx], buffer, maze.lines_n);
        int r=del_blind_node_from_arr(&A,buffer,curr_idx,&maze);
        if(r>0){
            del_node_from_arr(in,&A,&maze,r);
        }

        // dla wszystkich sąsiadów danego węzła
        for (int i = 2; i < 14; i += 3)
        {
            if (buffer[i] == 0 && buffer[i + 1] == 0) // buffer[i] == NULL oznacza, że skończyli się sąsiedzi
                break;
            tmp_idx = find_node_in_arr(&A, buffer[i], buffer[i + 1]);
            //printf("tmp_idx: %i\n", tmp_idx);

            write_node_to_arr(&A, tmp_idx, i, buffer, curr_idx);
        }

        //(ustaw minimum na dowolny nieodwiedzony węzeł)
        for (int i = 0; i < A.size; i++)
                if (A.visited[i] < 0) {
                    minimum = i;
                    break;
                }

        for (int i = 0; i < A.size; i++)
            if (A.visited[i] < 0 && A.len_to_start[minimum] > A.len_to_start[i])
		minimum = i;
               

        curr_idx = minimum;
        k++;
    }

    A.visited[curr_idx] = abs(A.row[curr_idx]);

    find_answer(curr_idx, &maze, &A);
    print_answer(A.path[0], &maze, &A);

    return 0;
}
