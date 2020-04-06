main:main.o add.o
	gcc -o main main.o add.o
add.o:add.c
	gcc -c add.c -o add.o
main.o:main.c
	gcc -c main.c -o main.o
.PHONY:clean rebuild
rebuild:clean main
clean:
	rm -rf main.o add.o main
