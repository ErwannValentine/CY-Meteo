all: exec
main.o: head.h main.c
	gcc -c main.c -o main.o

AVL.o: head.h AVL.c
	gcc -c AVL.c -o AVL.o

creation.o: head.h creation.c
	gcc -c creation.c -o creation.o

pression1.o: head.h pression1.c
	gcc -c pression1.c -o pression1.o

techniqueAVL.o: head.h techniqueAVL.c
	gcc -c techniqueAVL.c -o techniqueAVL.o

temperature1.o: head.h temperature1.c
	gcc -c temperature1.c -o temperature1.o

exec: AVL.o main.o creation.o pression1.o techniqueAVL.o temperature1.o
	gcc *.o -o exec

clean:
	rm -f *.o
	rm exec
