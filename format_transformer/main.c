#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze_structure.h"
#include "array2_structure.h"
#include "format_transformer.h"
#include "file_checker.h"
#include "bin_format_transformer.h"


int main (int argc, char ** argv) {
    FILE * in = argc > 1 ? fopen(argv[1], "rb") : fopen("maze.txt", "rb");
    FILE * out =  fopen("adjacency_list.txt", "w");
    Maze maze = initialize_Maze();
    
    int result=0;


    if (in == NULL)
        fprintf(stderr, "Błąd: %s - nie można otworzyć pliku wejściowego.\n", argv[0]);
    int bin = is_binary(in);
    if(bin==0)
        result = check_file (in, &maze);

    if (result != 0)
        return -1;

    fseek(in, 0, SEEK_SET);

    
    
    if(bin){
        Array2 A=initialize_Array(in);
        maze.cols=A.rows;
        maze.rows=A.cols;
        maze.P_r=A.y_p-1;
        maze.P_c=A.x_p-1;
        maze.K_r=A.y_k-1;
        maze.K_c=A.x_k-1;
        read_binary_file(in,&A);
        transform_maze_format_bin(&A,out,&maze);
    }else{

    transform_maze_format(in, out, &maze);
    fclose(in);
    }



    return 0;
}
