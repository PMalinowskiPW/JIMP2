#include <stdio.h>
#include <stdlib.h>

#include "file_reader.h"

short * read_file_line(FILE *in,int x,int y,short * numbers,int n_col){
    //printf ("szukam x: %i, y: %i", x, y);

    int n;
    int i = 0;
    int j =0;
    while (j < n_col)
    {
        while (i < MAX_LENGTH && fscanf(in, "%d", &n) == 1) {
                numbers[i] = n;
                i++;
        }
        if(numbers[0]==x && numbers[1]==y){
            fseek( in,0, SEEK_SET );
            /*printf ("buff:");
            for (int a = 0; a < MAX_LENGTH; a++)
                printf("%i", numbers[a]);
             printf ("\n");*/
            return numbers;
        } 
        i=0;
        j++;       

    }

    fprintf(stderr, "funkcja szukająca nie znalazła wiersza\n");
     fseek( in,0, SEEK_SET );
     exit(EXIT_FAILURE);
    return numbers;
}
