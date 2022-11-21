all: item.o AVL.o set.o main.o
	gcc -g item.o AVL.o set.o main.o -o exec -std=c99 -Wall -g; make clean

item.o:
	gcc -g -c item.c -o item.o -g

AVL.o:
	gcc -g -c AVL.c -o AVL.o -g
	 
set.o:
	gcc -g -c set.c -o set.o -g

main.o:
	gcc -g -c main.c -o main.o -g
	 
clean:
	rm *.o

run:
	valgrind ./exec < ../TestCases/2.in