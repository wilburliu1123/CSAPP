all: mstore

mstore: mstore.c
	gcc -o mstore mstore.c
run: mstore
	./mstore
mstore_assembly: mstore.c
	gcc -Og -S mstore.c
clean:
	rm mstore