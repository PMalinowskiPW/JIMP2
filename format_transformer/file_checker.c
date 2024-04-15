#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "file_checker.h"
#include "maze_structure.h"

//check_buff_errors sprawdza, czy buffer jest poprawny
//zwraca -1 w przypadku wystąpienia błędu pliku i 0 w przypadku braku błędu
//wypisuje na stderr szczegółowe informacje o błędzie
int check_buff_errors (char * buffer, int line, Maze * maze) {

    //strlen uwzględnia znak końca linii, dlatego sprawdzamy strlen -1
    //jednak ostatni wers pliku nie zawiera znaku końca linii
    if (strlen(buffer)-1 != maze->cols) {
        if  (buffer[strlen(buffer)-1] == '\n') {
            fprintf(stderr, "1: Błąd, nieprawidłowa długość linii %i: %li zamiast %i znaków.\n", line, strlen(buffer)-1, maze->cols);
            return -1;
        }
        else if (strlen(buffer) != maze->cols) {
             fprintf(stderr, "2: Błąd, nieprawidłowa długość linii %i: %li zamiast %i znaków.\n", line, strlen(buffer), maze->cols);
             return -1;
        }
    }

    for (int i = 0; i < strlen(buffer)-1; i++) {
        switch (buffer[i])
        {
        case 'X':
            break;
        case ' ':
            break;
        case 'P':
            if (maze->P_r == -1) {
                maze->P_r = line;
                maze->P_c= i;
            } else {
                fprintf(stderr, "Błąd, w pliku dwukrotnie wystąpił symbol początku labiryntu.\n");
                return -1;
            }
            break;
        case 'K':
            if (maze->K_r == -1) {
                maze->K_r = line;
                maze->K_c = i;
            } else {
                fprintf(stderr, "Błąd, w pliku dwukrotnie wystąpił symbol końca labiryntu.\n");
                return -1;
            }
            break;
        default:
            fprintf(stderr, "Błąd, nieprawidłowy symbol '%c' w pliku wejściowym w linii %i.\n", buffer[i], line);
            return -1;
        }
    }

    return 0;
}

//check_file sprawdza, czy w pliku występują błędy i nadpisuje dane w strukturze Maze
//zwraca -1 w przypadku wystąpienia błędu pliku i 0 w przypadku poprawnego formatu
int check_file (FILE *in, Maze * maze) {
    char buffer [BUFFSIZE];
    int line = 0;

    if (fgets (buffer, BUFFSIZE, in) == NULL) {
        fprintf(stderr, "Błąd: plik wejściowy jest pusty.\n");
        return -1;
    }
       
    maze->cols= strlen(buffer)-1;
    printf("liczba kolumn: %i\n\n", maze->cols);

    if ((maze->cols -1) %2 != 0) {
        fprintf(stderr, "Nieprawidłowa liczba kolumn labiryntu\n");
        return -1;
    }

    if (check_buff_errors(buffer, line, maze) != 0)
        return -1;
        
    while (fgets (buffer, BUFFSIZE, in)) {
        line ++;

        if (check_buff_errors(buffer, line, maze) != 0)
            return -1;
    }

    maze->rows = line +1;

    return 0;
 }
