#ifndef _FILE_CHECKER_H
#define _FILE_CHECKEKR_H

#include "maze_structure.h"

#define BUFFSIZE 1024*2+2

int check_buff_errors (char * buffer, int line, Maze * maze);
int check_file (FILE *in, Maze * maze);

#endif
