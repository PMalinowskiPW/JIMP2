CC = gcc
maze_solver.out: main.o maze_solver.o maze_structure.o file_reader.o array_structure.o
	$(CC) $^
main.o: maze_solver.h maze_structure.h file_reader.h array_structure.h
maze_solver.o: maze_solver.h file_reader.h
maze_structure.o: maze_structure.h
file_reader.o: file_reader.h
array_structure.o: array_structure.h
