PROGRAM_OBJ=main.o
PROGRAM_OUT=project
PROGRAM_C=main.c bitmap.c

program: $(PROGRAM_OBJ)
	gcc -o project $(PROGRAM_OBJ)

main.o:main.c
	gcc -c -o main.o main.c

clean:
	rm -f $(PROGRAM_OBJ) $(PROGRAM_OUT)
