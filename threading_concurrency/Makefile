all: mt_search

example: example.c
	gcc -pthread -o example example.c

run_example: example
	./example

mt_search: mt_search.c
	gcc -pthread -o mt_search mt_search.c

run:
	./mt_search inputs/input1.txt 5 2 10

run_valgrind: mt_search
	valgrind --leak-check=full ./mt_search inputs/input1.txt 5 2 10

clean:
	rm example
