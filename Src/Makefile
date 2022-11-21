all: item.o AVL.o set.o main.o
	gcc item.o AVL.o set.o main.o -o teste -std=c99 -Wall -g

item.o:
	gcc -c item.c -o item.o -g

AVL.o:
	gcc -c AVL.c -o AVL.o -g
	 
set.o:
	gcc -c set.c -o set.o -g

main.o:
	gcc -c main.c -o main.o -g
	 
clean:
	rm *.o teste

run:
	./teste