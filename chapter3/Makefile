all: mstore

mstore: mstore.c
	gcc -o mstore mstore.c
main: main.c
	gcc -o main main.c
prog:
	gcc -Og -o prog main.c mstore.c
run: mstore
	./mstore
mstore_assembly: mstore.c
	gcc -Og -S mstore.c
clean:
	rm mstore prog