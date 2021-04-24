# Assignment 10: Multi-threaded Searching

name: Wilbur Liu

Makefile is created for compile and run the program. With following command:

```makefile
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
```

If you type ```make run``` in command line it will run default file ```./input/input1.txt``` as file to read and generate results

```run_valgrind``` command will run default input1.txt file and check for leaks.

my program will print detail information about thread creation process and which index is being searched currently

it will print our target number and number of threads and total length of our file. It will also print our section size(how many index we will look at in each thread) and input array after we read the file

Whenever we entering a thread, we will print ```start thread ``` and the index in data array it starts with to search for target

if target is found, we will print thread id and index number, and our target, otherwise print target not found at index 

below is an example output from the program. 

```shell
./mt_search inputs/input1.txt 5 2 10
our target is 5
number of threads is: 2
length is 10
input array:
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
section size is: 5
Start creating threads...
start thread 0
start thread 1
entered in starting idx with 0...
target not found at idx: 0
target not found at idx: 1
target not found at idx: 2
target not found at idx: 3
target not found at idx: 4
entered in starting idx with 5...
target found at thread id: 1868083200 at index: 5, target is : 5
target not found at idx: 6
target not found at idx: 7
target not found at idx: 8
target not found at idx: 9
Threads have joined
line number 5 has our target: 5
```



if given input size cannot evenly devide by number of threads we have (for example, we have size 10 and 3 threads). We will print this info and the last thread will read less index

```shell
./mt_search inputs/input2.txt 100 4 26
our target is 100
number of threads is: 4
length is 26
input array:
[100, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 100, 100, 100]
given number of thread cannot evenly divide the input array, sections size is: 7
section size is: 7
Start creating threads...
start thread 0
start thread 1
start thread 2
start thread 3
entered in starting idx with 0...
entered in starting idx with 7...
target not found at idx: 7
target not found at idx: 8
entered in starting idx with 21...
entered in starting idx with 14...
target not found at idx: 14
target not found at idx: 21
target not found at idx: 22
target found at thread id: 1840410624 at index: 23, target is : 100
target not found at idx: 15
target not found at idx: 16
target not found at idx: 17
target found at thread id: 1840410624 at index: 24, target is : 100
target found at thread id: 1840410624 at index: 25, target is : 100
target found at thread id: 1838690304 at index: 0, target is : 100
target not found at idx: 1
target not found at idx: 2
target not found at idx: 3
target not found at idx: 4
target not found at idx: 5
target not found at idx: 6
target not found at idx: 9
target not found at idx: 10
target not found at idx: 11
target not found at idx: 12
target not found at idx: 13
target not found at idx: 18
target not found at idx: 19
target not found at idx: 20
Threads have joined
line number 23 has our target: 100
line number 24 has our target: 100
line number 25 has our target: 100
line number 0 has our target: 100
```

