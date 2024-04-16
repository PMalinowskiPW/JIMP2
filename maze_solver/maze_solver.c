#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze_solver.h"
#include "file_reader.h"

int del_blind_node_from_arr(Array *A, short *buffer, int curr_idx,Maze *maze)
{
    if (buffer[5] == 0 && buffer[6] == 0 && buffer[0]!=maze->P_r && buffer[1]!=maze->P_c)
    {
        int p = find_node_in_arr(A, A->row_pvs[curr_idx], A->col_pvs[curr_idx]);
        A->exists[curr_idx] = -1;
        return p;
    }
    return -1;
}

void del_node_from_arr(FILE *in, Array *A, Maze *maze, int p)
{   
    short buf[2 + 4 * 3];

    read_file_line(in, A->row[p], A->col[p], buf, maze->lines_n);


    int num_n_del=0; 
    int check=0;
    for (int i = 2; i < 14; i += 3){
        if (buf[i] == 0 && buf[i + 1] == 0)
            break;
        check++; 
    }
    if(check==2){

        int d = find_node_in_arr(A, A->row_pvs[p], A->col_pvs[p]);
        A->exists[p] = -1;
        p=d;
        del_node_from_arr(in,A,maze,p);
    }
}


void find_answer(short end_idx, Maze * maze, Array * A) {
    //dla oszczędności pamięci ścieżkę zapisujemy w arr[4] (len_to_start), które już nie jest potrzebne
    short path_counter = -1;
    short next_idx, curr_idx = end_idx; 

    A->path[end_idx] = path_counter;

    while (curr_idx != 0) {
        path_counter--;
        next_idx = find_node_in_arr(A, A->row_pvs[curr_idx], A->col_pvs[curr_idx]);

        A->path[next_idx] = path_counter;

        curr_idx = next_idx;
    }
}

void print_answer(int start_idx, Maze * maze, Array * A) {
    short curr_idx = 0;
    int wage, side = -1;
    int row_a, row_b, col_a, col_b;
    int path_counter = start_idx;
    int first=0;

    printf("START\n");

    while (path_counter < -1) {
        path_counter++;

        for (int i = 0; i < A->size; i++)
            if (A->path[i] == path_counter) {
                row_a = A->row[curr_idx];
                col_a = A->col[curr_idx];
                row_b = A->row[i];
                col_b = A->col[i];

                if (side == -1) {
                    if (row_a == row_b) {
                        if (col_a - col_b == -1)
                            side = 1;
                        else
                            side = 3;
                    } else {
                        if (row_a - row_b == -1)
                            side = 2;
                        else 
                            side = 0;
                    }
                    curr_idx = i;
                    break;
                }

                wage = row_a - row_b + col_a - col_b;
                if(first==0){
                    printf("FORWARD %i\n", abs(wage)+1);
                    first=1;
                }else
                printf("FORWARD %i\n", abs(wage));
                switch (side)
                {
                case 0:
                    if  (wage < 0) {
                        printf("TURNRIGHT\n");
                        side = 1;
                    } else {
                        printf("TURNLEFT\n");
                        side = 3;
                    }
                    break;
                case 1:
                    if  (wage < 0) {
                        printf("TURNRIGHT\n");
                        side = 2;
                    } else {
                        printf("TURNLEFT\n");
                        side = 0;
                    }
                    break;
                case 2:
                    if  (wage > 0) {
                        printf("TURNRIGHT\n");
                        side = 3;
                    } else {
                        printf("TURNLEFT\n");
                        side = 1;
                    }
                    break;
                case 3:
                    if  (wage > 0) {
                        printf("TURNRIGHT\n");
                        side = 0;
                    } else {
                        printf("TURNLEFT\n");
                        side = 2;
                    }
                    break;
                }


                
                curr_idx = i;
                break;
            }           
    }

    printf("STOP\n");  
}


