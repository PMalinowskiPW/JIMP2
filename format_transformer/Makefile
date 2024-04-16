format_transformer.out: main.o file_checker.o format_transformer.o maze_structure.o bin_format_transformer.o array2_structure.o
	$(CC) $^
main.o: format_transformer.h file_checker.h maze_structure.h bin_format_transformer.h array2_structure.h
file_checker.o: file_checker.h maze_structure.h
format_transformer.o: format_transformer.h maze_structure.h
bin_format_transformer.o: bin_format_transformer.h maze_structure.h array2_structure.h format_transformer.h
maze_structure.o: maze_structure.h
array2_structure.o: array2_structure.h
