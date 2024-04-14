#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "maze_structure.h"
#include "format_transformer.h"

char ** load_data(FILE *in, Maze *maze) {
    char ** arr = malloc((maze->rows +1) * sizeof(char *));
    for (int i = 0; i < maze->rows; i++)
        arr[i] = malloc((maze->cols + 2) * sizeof(char));

    int line = 0;
    while (fgets(arr[line], maze->cols + 2, in)) {
        line++;
        if (line == maze->rows)
            break;
    }

    for (int i = 0; i < maze->rows; i++) {
        printf("%s", arr[i]);
    }

    return arr;
}

int is_crossing (int row, int col, char ** arr) {
    if (arr[row -1][col] == ' ' && arr[row+1][col] == ' ')
        if (arr[row][col -1] == 'X' && arr[row][col +1] == 'X')
            return 0;

    if (arr[row -1][col] == 'X' && arr[row+1][col] == 'X')
        if (arr[row][col -1] == ' ' && arr[row][col +1] == ' ')
            return 0;

    return 1;
}

void transform_maze_format(FILE *in, FILE *out, Maze *maze) {
     int line_counter;

    int counter = 1;
    int row, col;
    row = col = 1;

    char ** arr = load_data(in, maze);
    fprint_Maze (out, maze);
 
    //jeśli początek znajduje się "w ścianie", to trzeba nadpisać go z użyciem innych zasad! todo

    while (row < maze->rows) {
        line_counter = 2;
        if (is_crossing(row, col, arr)) {
            fprintf(out, "%i %i ", row, col);
        
            //up
            while ( row - counter >= 0 ) {
                //wyjątek -> zamiast ściany jest 'K', czyli wyjście z labiryntu, przyjmujemy wagę "w ścianę" = 1
                if (arr[row - counter][col] == 'K') {
                    fprintf(out, "%i %i %i", row - counter, col, 1);
                    line_counter += 3;
                    break;
                }
                
                if (counter == 1) {
                    if (arr[row - counter][col] == 'X') 
                        break;
                } else if (is_crossing(row - counter +1, col, arr)) {
                        fprintf(out, "%i %i %i ", row - counter +1, col, (counter -1)/2);
                        line_counter += 3;
                        break;
                }
                //jeśli nie ma ściany ani nie jest skrzyżowaniem, to szukamy wyżej 
                counter += 2; 
            }
            //reset 
            counter = 1;

            //right
            while ( col + counter <= maze->cols ) {
                    if (arr[row][col + counter] == 'K') {
                        fprintf(out, "%i %i %i ", row, col + counter, 1);
                        line_counter += 3;
                        break;
                    }
                    
                    if (counter == 1) {
                        if (arr[row][col + counter] == 'X') 
                            break;
                    } else if (is_crossing(row, col + counter -1, arr)) {
                            fprintf(out, "%i %i %i ", row, col + counter -1, (counter-1)/2);
                            line_counter += 3;
                            break;
                    }
                counter += 2; 
            }
            counter = 1;
    
            //down
            while ( row + counter <= maze->rows ) {
                if (arr[row + counter][col] == 'K') {
                    fprintf(out, "%i %i %i ", row + counter, col, 1);
                    line_counter += 3;
                    break;
                }

                if (counter == 1) {
                    if (arr[row + counter][col] == 'X') 
                        break;
                } else if (is_crossing(row + counter -1, col, arr)) {
                        fprintf(out, "%i %i %i ", row + counter -1, col, (counter -1)/2);
                        line_counter += 3;
                        break;
                }
                counter += 2; 
            }
            counter = 1;
    
    
            //left
            while ( col - counter >= 0) {
                if (arr[row][col - counter] == 'K') {
                    fprintf(out, "%i %i %i ", row, col - counter, 1);
                    line_counter += 3;
                    break;
                }
                if (counter == 1) {
                    if (arr[row][col - counter] == 'X') 
                        break;
                } else if (is_crossing(row, col - counter +1, arr)) {
                        fprintf(out, "%i %i %i ", row, col - counter +1, (counter -1)/2);
                        line_counter += 3;
                        break;
                }
                counter += 2; 
            }
            counter = 1;
            
            for (int i = line_counter; i < 14; i++)
                fprintf(out, "0 ");

            fprintf(out, "\n");
        }
        
        if (col == maze->cols -2){
            col = 1;
            row += 2; 
        } else 
            col += 2;

    }
}
