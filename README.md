这里主要记录CSAPP这本书每个章节自己的读书笔记，按章分开。

### It pays to understand how compilation systems work

就像原话说的，我们理解了汇编系统如何运作之后能带来巨大的好处。书中提了很多问题，全都是我之前没想过的问题。

> *Optimizing program performance.* 
>
> * Is a switch statement always more efficient than a sequence of **if-else** statements?
> * How much overhead is incurred by a function call? 
> * Is a **while** loop more efficitent than array indexs?
> * Why does our loop run so much faster if we sum into a local cariable instead of an argument that is passed by reference?
> * How can a function run faster when we simply rearrange the parentheses in an arithmetic expression?
>
> *Understanding link-time errors.* 
>
> * What is the difference between a static variable and a global variable? 
> * What happens if you define two global variables in different C files with same name?
> * What is the difference between a static library and a dynamic library?
> * Why does it matter what order we list libraries on the command line?
> * Why do some linker-related errors not appear until run time?
>
> *Avoiding security holes.* 

这些问题我几乎每一个能回答上来的，但有问题就代表有学习和进步的空间，学问学问，就是边学边问。那么就带着问题继续读呗！
#### 硬件组织结构
![figure1.4](https://upload-images.jianshu.io/upload_images/6543506-335db5adb3ea47d9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
这张图给了硬件的组织结构
##### Buses
就是用来传输字节的电极管组成的结构。Buses are typically designed to transfer fixed-size chunks of bytes known as words.
##### I/O
输入输出
##### Main memory
*main memory* is a temporary storage device that holds both a program and the data it manipulates while the processor is executing the program. Physically, main memory consists of a collection of *dynamic random access memory* (DRAM) chips. Logically, memory is organized as linear array of bytes, each with its own unique address(array index) starting at zero. In general, each of the machine instructions that constitute a program can consist of a variable number of bytes. The sizes of data items that correspond to C program variables vary according to type. For example, short require 2 bytes, type **int** and **float** 4 bytes, **long** and **double** requires 8 bytes.
##### Processor
The central processing unit (CPU), or simply processor, is the engine that interprets (or executes) instructions stored in main memory. At its core is a word-size storage device (or register) called the program counter (PC). 
> At any point in time, the PC points at (contains the address of) some machine-language instruction in main memory
* Load. 读 从main memory 读到register
Copy a byte or a word from main memory into a register, overwriting the previous contents of the register
* Store. 写进main memory
Copy a byte or a word from a register to a location in main memory, overwriting the previous contents of that location.
* Operate
* Jump 
Extract a word from the instruction itself and copy that word into the program counter, overwriting the previous value of the PC

![shell vs terminal](https://upload-images.jianshu.io/upload_images/6543506-ba546c4c250f7560.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
> By concurrently, we mean that the instructions of one process are interleaved with the instructions of another process.
##### Caches Matter
An important lesson from this simple example is that a system spends a lot of time moving information from one place to another. The machine instructions in the **hello** program are originally stored on disk. When the program is loaded, they are copied to main memory. As the processor runs the program, instructions are copied from main memory into the processor. Similarly, the data string "Hello, world\n", originally on disk, is copied to main memory and then copied from main memory to the display device. From a programmer's perspective, much of this copying is overhead that slows down the "real work" of the program. Thus, a major goal for system designers is to make these copy operations run as fast as possible.
所以为了解决这种需要反复从main memory里面读取数据的问题，硬件通常会用cache（缓存）来减少读取数据的时间，缓存也有很多层级，如下图所示
![memory hierarchy](https://upload-images.jianshu.io/upload_images/6543506-ab80cdc3943cb18e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### 1.7.2 Threads
Although we normally think of a process as having a single control flow, in modern systems a process can actually consist of multiple execution units, called threads, each running in the context of the process and sharing the same code and global data. Threads are an increasingly important programming model because of the requirement for concurrency in network servers, because it is easier to share data between multiple threads than between multiple processes, and because threads are typically more efficient than processes. Multi-threading is also one way to make programs run faster when multiple processors are available

程序一般是按照这张图来进行运作的：


![figure 1.13](https://upload-images.jianshu.io/upload_images/6543506-b2e9082a2dad2155.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
> * Program code and data. code begins at the same fixed address for all processes, followed by data locations taht correpond to global C variables. The code and data areas are initialized directly from the contents of an executable object file -- int our case, the **hello** executable. 
> * Heap. hte code and data areas are folowed immediately by the run time head. heap expands and contracts dynamically at run time as a result of calls to C standard library routines such as malloc and free
> * Shared libraries. Near the middle of the address space is an area that holds the code and data for shared libraries such as the C standard library and the math library. the notion of a shared library is a powerful but somewhat difficult concept.
> * Stack. At the top of the user's virtual address space is the user stack that the compiler uses to implement function calls. Like the heap, the user stack expands and contracts dynamically during the execution of the program.
> * Kernel virtual memory. The top region of the address space is reserved for the kernel. 

##### 1.7.4 Files

A file is a sequence of bytes, nothing more and nothing less. Every I/O device is modeled as a file. ?!第一次知道

All input and output in the system is performed by reading and writing files,using a small set of system calls known as Unix I/O.

哦，这样你就不用管硬件是如何读写的了，只要知道他也是一个I/O device, 通过Unix I/O来实现数据的传输就可以了

##### Concurrency
> With threads, we can even have multiple control flows executing within a single process. 











### Why need to understand machine code? 
> So why should we spend our time learning machine code? Even though com- pilers do most of the work in generating assembly code, being able to read and understand it is an important skill for serious programmers. By invoking the compiler with appropriate command-line parameters, the compiler will generate a file showing its output in assembly-code form. By reading this code, we can under- stand the optimization capabilities of the compiler and analyze the underlying inefficiencies in the code.

Programmers seeking to maximize the performance of a critical section of code often try different variations of the source code, each time compiling and examining the generated assembly code to get a sense of how efficiently the program will run. Furthermore, there are times when the layer of abstraction provided by a high-level language hides information about the run-time behavior of a program that we need to understand. For example, when writing concurrent programs using a thread package, as covered in Chapter12, **it is important to understand how program data are shared or kept private by the different threads and precisely how and where shared data are accessed.** Such information is visible at the machine-code level. **As another example, many of the ways programs can be attacked, allowing malware to infest a system, involve nuances of the way programs store their run-time control information.** Many attacks involve exploiting weaknesses in system programs to overwrite information and thereby take control of the system. Understanding how these vulnerabilities arise and how to guard against them requires a knowledge of machine-level representation of programs. The need for programmers to learn machine code has shifted over the years from one of being able to write programs directly in assembly code to one of being able to read and understand the code generated by compilers.

x86 is intel product line
![x86](https://upload-images.jianshu.io/upload_images/6543506-c6b344ed958fcb71.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![x86 product line](https://upload-images.jianshu.io/upload_images/6543506-8d538373180ddd18.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### Instruction set architecture
The format and behavior of a machine-level program is defined by the *instruction set architecture* or **ISA**. Most ISA describe the behavior of a program as if each instruction is executed in sequence, with one instructino completing before the next one begins. 
![ISA definition](https://upload-images.jianshu.io/upload_images/6543506-bfb12b1a4cf5e48a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### Assembly code
Assembly-code representation is very close to machine code. Its main feature is that it is a more readable textual format.
> Whereas C provides a model in which objects of different data types can be declared and allocated in memory, machine code views the memory as simply a large byte-addressable array. Aggregate data types in C such as arrays and structures are represented in machine code as contiguous collections of bytes.

### running code on linux
![Snip20210325_15.png](https://upload-images.jianshu.io/upload_images/6543506-0726fdc4841ee895.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
#### rax rbp 名字由来
> An x86-64 central processing unit (CPU) contains a set of 16 general-purpose registers storing 64-bit values. These registers are used to store integer data as well as pointers. Figure 3.2 diagrams the 16 registers. Their names all begin with %r, but otherwise follow multiple different naming conventions, owing to the historical evolution of the instruction set.
> The original 8086 had eight 16-bit registers, shown in Figure 3.2 as registers %ax through %bp. Each had a specific purpose, and hence they were given names that reflected how they were to be used. With the extension to IA32, these registers were expanded to 32-bit registers, labeled %eax through %ebp. 
> In the extension to x86-64, the original eight registers were expanded to 64 bits, labeled %rax through %rbp. In addition, eight new registers were added, and these were given labels according to a new naming convention: %r8 through %r15.

下面这张图很好表达了register 不同名字以及他们对应的大小
![figure3.2](https://upload-images.jianshu.io/upload_images/6543506-69bc0859534a16f7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![legacy](https://upload-images.jianshu.io/upload_images/6543506-d96c8473b2209e29.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### Data movement instructions
Among the most heavily used instructions are those that copy data from one location to another. The generality of the operand notation allows a simple data movement instruction to express a range of possibilities that in many machines would require a number of different instructions. 
> Figure 3.4 lists the simplest form of data movement instructions—mov class. These instructions copy data from a source location to a destination location, without any transformation. The class consists of four instructions: movb, movw, movl, and movq. All four of these instructions have similar effects; they differ primarily in that they operate on data of different sizes: 1, 2, 4, and 8 bytes, respectively.

![figure3.4](https://upload-images.jianshu.io/upload_images/6543506-60b503efaa9766da.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![slides](https://upload-images.jianshu.io/upload_images/6543506-5f750ef5a419a91a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

The source operand designates a value that is immediate, stored in a register, or stored in memory. The destination operand designates a location that is either a register or a memory operand designates a location that is either a register or memory address. 

x86-64 imposes the restriction that a move instruction cannot have both operands refer to memory locations. Copying a value from one memory location to another requires two instructions -- the first to load the source value into a register, and the second to write this register value to the destination. 

### Data movement example
![figure3.7](https://upload-images.jianshu.io/upload_images/6543506-b66f8d11ccaa0b9a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![1:02:45](https://upload-images.jianshu.io/upload_images/6543506-2319cdd8b713d36d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

> When the procedure begins execution, procedure parameters xp and y are stored in registers %rdi and %rsi, respectively. Instruction 2 then reads x from memory and stores the value in register %rax, a direct implementation of the operation x = *xp in the C program. Later, register %rax will be used to return a value from the function, and so the return value will be x. Instruction 3 writes y to the memory location designated by xp in register %rdi, a direct implementation of the operation *xp = y. This example illustrates how the mov instructions can be used to read from memory to a register (line 2), and to write from a register to memory (line 3).

pointer dereferencing. 如果*是在assignment 右边，那就是读取。如果在左边，那就是写入
![image.png](https://upload-images.jianshu.io/upload_images/6543506-0b4d115f87e3ccf2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![image.png](https://upload-images.jianshu.io/upload_images/6543506-50ffbfe04d2e4cc1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### practice problem 3.5
反馈还是挺重要的。根据这道题给的assembly code 写出c source code。
![image.png](https://upload-images.jianshu.io/upload_images/6543506-e376f44015e29e6c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
下面是我的c code， 用gcc -Og -S compile之后的assembly code 也是对应上了，可以加深对于how register works 的理解
![image.png](https://upload-images.jianshu.io/upload_images/6543506-c6c2fdd05093c55b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![image.png](https://upload-images.jianshu.io/upload_images/6543506-5f315192f49ca35f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### Pushing and poping stack data
![figure3.9](https://upload-images.jianshu.io/upload_images/6543506-d44f63283c680ffb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
The pushq instruction provides the ability to push data onto the stack, while the popq instruction pops it. Each of these instructions takes a single operand --the data source for pushing and the data destination for popping. 
Pushing a quad word value onto the stack involves first decrementing the stack pointer by 8 and then writing the value at the new top-of-stack address. Therefore, the behavior of the instruction pushq %rbp is equivalent to that of the pair of instructions 
```
subq $8, %rsp //Decrement stack pointer
movq %rbp, (%rsp)  //store %rbp on stack
```
except that the pushq instruction is encoded in the machine code as a single byte, whereas the pair of instructions shown above requires a total of 8 bytes. The first two columns in Figure 3.9 illustrate the effect of executing the instruction pushq %rax when %rsp is 0x108 and %rax is 0x123. 

The third column of Figure 3.9 illustrates the effect of executing the instruction opoq %edx immediately after executing the **pushq**. Value 0x123 is read from memory and written to register %rdx. Register %rsp is incremented back to 0x108. As shown in the figure, the value 0x123 remains at memory location 0x104 until it is overwritten (e.g. by another push operation). However, the stack popo is always considered to be the address indicated by %rsp.

Since the stack is contained in the same memory as the program code and other forms of program data, programs can access arbitrary positions within the stack using the standard memory addressing methods. For example, assuming the topmost element of the stack is quad word, the instruction **movq 8(%rsp), %rdx will copy the second quad word from the stack to register %rdx

### 3.5 Arithmetic and logical operations
Most of the operations are given as instructions classes, as they can have different variants with different operand sizes. (same as ```movb, movw, movl, movq```) b stands for byte, w stands for word, l stands for double word, q stands for quad word
For example, the instruction class ADD consists of four addition instructions: ```addb, addw, addl, and addq```
(same as move class with different sizes)
The operations are divided into four groups: load effective address, unary, binary, and shifts. *Binary* operations have two operands, while *unary* operations have one operand. These operands are specified using the same notation as described in Section 3.4

#### 3.5.1 Load effective address
The *load effective address* instruction **leaq** is actully a variant of the **moveq** instruction. It has the form of an instruction that reads from memory to a register, but it does not reference memory at all. Its first operand appears to be a memory reference, but instead of reading from the designated location, the instruction copies the effective address to the destination. 
这里就更加清楚为什么C语言里会有&这个这个operator了，因为他能从cpu instruction里面调用effective address 然后进行后面的操作。
We indicate this computation in Figure 3.10 using the C address operator &S. This instruction can be used to generate pointers for later memory references. In addition, it can be used to compactly describe common arithmetic operations. For example, if register %rdx contains value x, then the instruction
```
leaq 7(%rdx, %rdx, 4), %rax
```
will set register %rax to 5x + 7. Compilers often find clever uses of leaq that have nothing to do with effective address computations. The destination operand must be a register. 


![image.png](https://upload-images.jianshu.io/upload_images/6543506-43a65942def21322.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![1:11:10](https://upload-images.jianshu.io/upload_images/6543506-c5b8ec4a4cd45b59.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

Operations in the second group are unary operations (位运算）, with the single operand serving as both source and destination. This operand can be either a register or a memory location. For example, the instruction incq(%rsp) causes the 8-byte element on the top of the stack to be incremented. This syntax is reminiscnet of the C increment(++) and decrement(--) operators.

The third group consists of binary operations, where the second operand is used as both a source and a destination. This syntax is reminiscent of the C assignment operators, such as x -= y. Observe, however, that the source operand is given first and the destination second. This looks peculiar for noncommutative operations. For example, the instruction subq %rax, %rdx decrements register %rdx by the value %rax The first operand can be either an immediate value, a register, or a memory location. The second can be either a register or a memory location. As with the MOV instructions, the two operands cannot both be memory locations. Note that when the second operand is a memory location, the processor must read the value from memory, perform the operation, and then write the result back to memory.

#### 3.5.3 shift operations
The final group consists of shift operations, where the shift amount is given first and the value to shift is given second. Both arithmetic and logical right shifts are possible. the different shift instructions can specify the shift amount either as an immediate value or with the single-byte register %cl. In principle, having a 1-byte shift amount would make it possible to encode shift amounts ranging up to 2^8-1 = 255. With x86-64, a shift instruction operating on data values that are w bits long determines the shift amount from the low-order m bits of register %cl, where 2^m = w. The higher-order bits are ignored. So, for example, when register %cl has hexadecimal value 0xFF, then instruction salb would shift by 7 (one byte), while salw would shift by 15(2byte). sall would shift by 31, and salq would shift by 63.

#### 3.5.4 discussion
We see that most of the instructions shown in figure 3.10 can be used for either unsigned or two's complement arithmetic. Only right shifting requires instructions that differentiate between signed versus unsigned data. This is one of the features that makes two's-complement arithmetic the preferred way to implement signed integer arithmetic. 

Figure 3.11 shows an example of a function that performs arithmetic operations and its translation into assembly code. Arguments x, y, and z are initially stored in registers %rdi, %rsi, and %rdx, respectively. the assembly-code instructions correspond closely with the lines of C source code. 

#### 3.5.5 Special arithmetic operations
As we saw in Section 2.3, multiplying two 64-bit signed or unsigned integers can yield a product that requires 128 bits to represent. The x86-63 instruction set provides limited suport for operations involving 128-bit numbers. Continueing with the naming convention of word, double word, and quad word, Intel refers to a 16 byte quantity as an oct word. 

### 3.6 Control
Machine code provides two basic low-level mechanisms for implementing conditional behavior: it tests data values and then alters either the control flow or the data flow based on the results of these tests.
Data-dependent control flow is the more general and more common approach for implementing conditional behavior. The execution order of a set of machine code instructions can be altered with a jump instruction, indicating that control should pass to some other part of the program, possibly contingent on the result of some test. The compiler must generate instruction sequences that build upon this low-level mechanism to implement the control constructs of C. 
#### 3.6.1 Condition codes
CPU maintains a set of single-bit condition code registers describing attributes of the most recent arithmetic or logical operation. These registers can then be tested to perform conditional branches. These condition codes are the most useful:
> **CF**: Carry flag. The most recent operation generated a carry out of the most significant bit. Used to detect overflow for unsigned operations. 
> **ZF**: Zero flag. The most recent operation yielded zero.
> **SF**: Sign flag. The most recent operation yielded a negative value.
> **0F**: Overflow flag. The most recent operation caused a two's complement overflow--either negative or positive.
#### 3.6.3 Jump Instructions
A jump instruction can cause the execution to switch to a completely new position in the program. These jump destinations are generally indicated in assembly code by a label. 

## Chapter 6

### Storege Tech

Difference between SRAM and DRAM and how 

这里就介绍了SRAM 跟DRAM的区别
CPU will do other work while reading file from disk.
![figure 6.12](https://upload-images.jianshu.io/upload_images/6543506-7ce7ef48c389872b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
#### 6.2 Locality

*temporal locality* - data is likely going to be referenced again in future

*spatial locality* - if a memory location is referenced once, then the program is likely to reference a nearby memory location in the near future.

> For example, Web browsers exploit temporal locality by caching recently referenced documents on a local disk. High-volume Web servers hold recently requested documents in front-end disk caches that satisfy requests for these documents without requiring any intervention from the server.

生活中的例子： 网易云音乐

a[i+1] = a[i] + b[i];

#### 6.4.3 Set Associative Caches

The problem with conflict misses in direct-mapped caches stems from the constraint that each set has exactly one line (E=1). A set associative cache relaxes this constraint so that each set holds more than one cache line. A cache with 1 < E < C / B is often called an E-way set associative cache. We will discuss the special case, where E = C/B, in the next section. Figure 6.32 shows the organization of a two-way set associative cache. 
Set selection is identical to a direct-mapped cache, with set index bits identifying the set. Figure 6.33 summarizes this principle.


#### 6.4.3 Set Associative Caches
The problem with conflict misses in direct-mapped caches stems from the constraint that each set has exactly one line (E=1). A set associative cache relaxes this constraint so that each set holds more than one cache line. A cache with 1 < E < C / B is often called an E-way set associative cache. We will discuss the special case, where E = C/B, in the next section. Figure 6.32 shows the organization of a two-way set associative cache. 
Set selection is identical to a direct-mapped cache, with set index bits identifying the set. Figure 6.33 summarizes this principle.
![figure 6.32 6.33](https://upload-images.jianshu.io/upload_images/6543506-0e3611f901b00de3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

Line matching is more involved in a set associative cache than in a direct-mapped cache because it must check the tags and valid bits of multiple lines in order to determine if the requested word is in the set. A conventional memory is an array of values that takes an address as input and returns the value stored at that address. An *associative memory*, on the other hand, is an array of (key, value) pairs that takes as input the key and returns a value from one of the (key, value) pairs that matches the input key. Thus, we can think of each set in a set associative cache as a small associative memory where the keys are the concatenation of the tag and valid bits, and the values are the contents of a block.

Figure 6.34 shows the basic idea of the line matching in an associative cache. An important idea here is that any line in the set can contain any of the memory blocks that map to that set. So the cache must search each line in the set ofr a valid line whose tag matches the tag in the If the cache finds such a line, then we have a hit and the block offset selects a word from the block, as before.

也就是说找到了tag 之后，它会逐行寻找matched address. 

Line Replacement on misses in set associative caches 
If the word requested by the CPU is not stored in any of the lines in the set, then we have a cache miss, and the cache must fetch the block that contains the word from memory. However, once the cache has retrieved the block, which lien should it replace? If there are no empty lines in the set, then it would be a good candidate. But if there are no empty lines in the set, we must choose one of the nonempty lines and hope that the CPU does not reference the replaced line anytime soon.


#### Why do all choices matter?
The advantage of increasing the degree of associativity is that it usually decreases the miss rate. The improvement in miss rate comes from reducing misses that compete for the same location. 

#### Writing cache friendly code
![image.png](https://upload-images.jianshu.io/upload_images/6543506-928c54c30e1ff0e8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

> In general, if a cache has a block size of B bytes, then a stride-k reference pattern (where k is expressed in words) results in an average of min(1, word size*k)/B misses per loop iteration. This is minimized for k = 1, so the stride-1 references to v are indeed cache friendly. for example, suppose that v is block aligned, words are 4 bytes, cache blocks are 4 words, and the cache is initially empty(a cold cache). Then, regardless of the cache organization, the references references to v will result in the following pattern of hits and misses.
> ![image.png](https://upload-images.jianshu.io/upload_images/6543506-bde84840b59e93f3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

To Summarize, out simple sumvec example illustrates two important points about writing cache-friendly code:
  * repeated references to local variables are good because the compiler can cache them in the register file (temporal locality)
  * Stride-1 reference patterns are good because caches at all levels of the memory hierarchy store data as contiguous blocks(spatial locality) 





### Chapter 8

What is a socket?

Ok-you may have heard some Unix hacker state, "Jeez, everything in Unix is a file!" What that person may have been talking about is the fact that when Unix programs do any sort of I/O, they do it by reading or writing to a file descriptor. A file descriptor is simply an integer associated with an open file. But(and here's the catch), **that file can be a network connection**, a FIFO, a pipe, a terminal, a real on-the-disk file, or just about anything else. Everything in Unix is a file! So when you want to communicate with another program over the Internet you're gonna do it through a file descriptor

You make a call to the socket() system routine. It returns the socket descriptor, and you communicate through it using the specialized send() and recv() (man send, man recv). socket calls.

#### Two types of Internet sockets 

One is "Stream sockets"; the other is "Datagram sockets" referred to as "SOCK_STREAM" and "SOCK_DGRAM", respectively. Datagram sockets are sometimes called "connectionsless sockets". 

Stream sockets are reliable two-way connected communication streams. If you output two items into the socket in the order "1,2", they will arrive in the order "1,2" at the opposite end. They will also be error-free. 

What uses steam sockets? Well, you may have heard of the telnet application, yes? it uses stream sockets. All the characters you type need to arrive in the same order you type them, right? Also, **web browsers use the Hypertext Transfer Protocol (HTTP) which uses stream sockets to get pages. Indeed, if you telnet to a web site on port 80, and type "GET / HTTP/1,0" and hit RETURN twice, it'll dump HTML back at you

How do stream sockets achieve this high level of data transmission quality? They use a protocol called "The Transmission Control Protocol", otherwise known as **"TCP"**.

TCP makes sure your data arrives sequentially and error-free. You may have heard "TCP" before as the better half of "TCP/IP" where "IP" stands for "Intenet Protocol" IP deals primarily with Intenet routing and is not generally responsible for data integrity. 

Cool. What about Datagram sockets? Why are they called connectionless? What is the deal, here, anyway? Here are some facts: if you send a datagram, it may arrive. It may arrive out of order. If it arrives, the data within the packet will be error-free.

Datagram sockets also use IP for routing, but they don't use TCP; they use the "User Datagram Protocol", or "UDP" 

Why are they connectionless? Well, basically it's beacuse you don't have to maintain an open connection as you do with stream sockets. You just build a packet, slap an IP header on it with destination information, and send it out. No connection needed. They are generally used either when a TCP stack is unavailable or when a few dropped packets here and there don't mean the end of the Universe. Sample applications: tftp(trivial file transfer protocol, a little brother to FTP), dhcpcd(a DHCP client), multiplayer games, streaming audio. video conferencing, etc.

Well, my human friend, `tftp` and similar programs have their own protocol on top of UDP. For example, the tftp protocol says that for each packet that gets sent, the recipient has to send back a packet that says, “I got it!” (an “ACK” packet). If the sender of the original packet gets no reply in, say, five seconds, he’ll re-transmit the packet until he finally gets an ACK. This acknowledgment procedure is very important when implementing reliable `SOCK_DGRAM` applications.

For unreliable applications like games, audio, or video, you just ignore the dropped packets, or perhaps try to cleverly compensate for them.

Why would you use an unreliable underlying protocol? Two reasons: speed and speed. It’s way faster to fire-and-forget than it is to keep track of what has arrived safely and make sure it’s in order and all that. If you’re sending chat messages, TCP is great; if you’re sending 40 positional updates per second of the players in the world, maybe it doesn’t matter so much if one or two get dropped, and UDP is a good choice.

### OSI

**Layered Network Model** (aka ISO/OSI). you can write sockets programs that are exactly the same without caring how the data is physically transmitted (serial, think ethernet, AUI, whatever) because programs on lower levels deal with it for you. The actual network hardware and topology is transparent to the socket programmer.

Model:

- Application
- Presentation
- Sesssion
- Transport
- Network
- Data Link
- Physical

The physical layer is hardware (serial, Ethernet, etc) The application layer is just about as far from the physical layer as you can imagine--it's the place where users interact with the network.

Now, this model is so general you could probably use it as an automobile repair guide if you really wanted to. A layered model more consistent with Unix might be:

- Application Layer (telnet, ftp, etc)
- Host-to-Host Transport layer (TCP, UDP)
- Internet Layer(IP and routing)
- Network Access Layer(Ethernet, wi-fi, or whatever)

#### IP addresses, structs, and data munging

##### IPv4

Internet protocol version 4 had addresses made up of four bytes (4 "octets"), and was commonly written in "dots and numbers" form, like 192.0.2.111.

