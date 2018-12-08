PROGRAM_OBJ=xar.o
PROGRAM_OUT=xar
PROGRAM_C=xar.c

program: $(PROGRAM_OBJ)
	gcc -o $(PROGRAM_OUT) $(PROGRAM_OBJ)

xar.o:xar.c
	gcc -c -Wall -Wextra --std=gnu99 -pedantic -o xar.o xar.c

clean:
	rm -f $(PROGRAM_OBJ)
