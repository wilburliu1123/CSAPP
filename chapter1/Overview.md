Chapter 1 is definitely the chapter that needs to be read. If entire book is throw away, this is the chapter people should remember
## What is this chapter about? 
A overview of Computer System

## What is being said in detail? 
- Lifecycle of a hello world program 
- How does program get compiled
- How processor read instructions from memory
- Storage hierarchy
- Operating System manages hardware resources
- System communicate with other systems through network

## How does Author represent those details?

Through tracing the lifecycle of hello world program, author present different parts of a computer system that need to act together (perform in concert) to achieve the result of this program (i.e. from compilation to running it and print `Hello world` on screen)

1. Source code is written in plain text (ASCII or Unicode) and translated into bytes (just numbers). Wether it is plain text or bytes, it is all numbers that is stored on disk, memory or network.
2. Program gets compiled from plain text into machine code (bytes) where machine can execute it (section 1.2)
	1. compilation phase - translate from text to assembly language (from `hello.c` to `hello.s`)
	2. Assembly phase - translate assembly language to machine instructions `hello.o` file. (hello.o will be gibberish if you open it in a text editor)
	3. Linking phase - load precompiled object file (`printf.o` in this hello.o example) into our `hello.o` program. The result is `hello` file which is an *executable object file*, (or simply *executable*). This executable is ready to load into memory and executed by the system. 
3. Compiler is a system. It produce correct and efficient machine code. There are important reason why programmer need to understand how compilation system work:
	1. Optimization of program performance. 
	2. Understand link-time errors
	3. Avoiding security holes
4. How processor read and interpret instructions stored in memory
	1. Hardware architecture is presented in this section 
		- CPU (PC, Register file, ALU)
		- Main Memory
		- I/O Bus 


### Hardware architecture
This is still a brief introduction. There is a dedicated book about this. (Hennessy and Patterson’s computer architecture textbook)

Some key term to understand
#### Buses
Buses carry bytes of information back and forth between components (mouse, keyboard, CPU, memory). Buses typically designed to transfer chunks of bytes known as *words*. The number of bytes in a word (*word size*) is the fundamental system parameter that varies across systems. Most machines either have 4 bytes (32 bits) or 8 bytes (64 bits). 

#### I/O Devices
I/O devices such as mouse, keyboard, monitor(display), disk (storage) are how system interact with external world. 

Just like human have I/O device (eyes, ear for input, hands for output. Some can be both input and output such as mouth) 

#### Main memory
Main memory is a temporary storage device that holds both program and data it manipulates while processor is running the program. It is nothing more than a big linear array of bytes. each with its own unique address (array index) starting at 0. 

#### Processor
Central Processing Unit (CPU), or processor, is the machine (engine) that executes instructions stored in main memory. At its core is a storage device called *program counter* (PC). At any given time, PC points at some machine-language instructions in main memory. 

The processor repeatedly executes the instruction pointed at by the program counter and updates the program counter to point to the next instruction. 

The processor operate according to a model defined by *instruction set architecture*. In this model, instruction are executed in strict sequence. 
The processor perform the following:
1. Reads instruction from memory pointed by PC
2. interprets the bits in the instruction and perform some operation dictated by the instruction 
3. Update the PC to point to the next instruction 

### Operating System
This section basically tells the summary of Operating System. This is really good for review and introduction to anyone who doesn't understand what does operating system do.

An operating system is basically resource manager of hardware. It provides API for application program to call. Those API provide a protection from malfunction (or malicious) software to harm the hardware. 

There are 3 major abstraction provided by OS: `process`, `virtual memory`, and `files`. 
![[OS_obstraction.png]]
Files are abstraction of I/O devices. Virtual memory are abstraction of both main memory *and* I/O devices. Processes are abstraction of `processor`, `main memory` and `I/O devices`

This is something I didn't understand clearly before (I didn't understand that processes abstract both CPU, memory and I/O devices). But now looking back, this is true because each process will open default file descriptor of 0 for stdin, 1 for stdout, and 2 for stderr. Look at how dumb I am... Realized this after 4 years? (2024-07-13)



