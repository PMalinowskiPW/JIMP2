#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze_structure.h"
#include "format_transformer.h"
#include "file_checker.h"

int main (int argc, char ** argv) {
    FILE * in = argc > 1 ? fopen(argv[1], "r") : fopen("data/maze.txt", "r");
    FILE * out =  fopen("data/adjacency_list.txt", "w");

    Maze maze = initialize_Maze();
    int result;

    if (in == NULL)
        fprintf(stderr, "Błąd: %s - nie można otworzyć pliku wejściowego.\n", argv[0]);
    else
        result = check_file (in, &maze);

    if (result != 0)
        return -1;

    fclose(in);

    in = argc > 1 ? fopen(argv[1], "r") : fopen("data/maze.txt", "r");

    transform_maze_format(in, out, &maze);

    fclose(in);

    return 0;
}
