PROGRAM_OBJ=main.o copier.o
PROGRAM_OUT=mcp
PROGRAM_C=main.c copier.c

program: $(PROGRAM_OBJ)
	gcc -o $(PROGRAM_OUT) $(PROGRAM_OBJ)

main.o:main.c
	gcc -c -Wall -Wextra --std=gnu99 -pedantic -Werror -o main.o main.c

copier.o:copier.c
	gcc -c -Wall -Wextra --std=gnu99 -pedantic -Werror -o copier.o copier.c
clean:
	rm -f $(PROGRAM_OBJ)
