这里主要记录CSAPP这本书每个章节自己的读书笔记，按章分开。

## Chapter 1

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



## Chapter 2

### 2.1 Information storage
> most computers use blocks of 8 bits, or bytes, as the smallest addressable unit of memory. A machine-level program views memory as a very large array of bytes, referred to as virtual memory. 

这句话我觉得还是很重要的，每个byte都有他自己的地址，malloc的时候就是根据这个赋予的地址？

> Every byte of memory is identified by a unique number, known as its address, and the set of all possible addresses is known as the virtual address space.

C中的pointer就是通过指向一个程序object在virtual memory的第一个字节来实现的
> For example, the value of a pointer in C—whether it points to an integer, a structure, or some other program object—is the virtual address of the first byte of some block of storage. 

C的compiler是存储type的信息的，但当机器实现的时候实际上并没有type的信息，也就是说int 还是char还是float在它眼里都是一块字节，程序本身就是一系列字节排在一起

> The C compiler also associates type information with each pointer, so that it can generate different machine-level code to access the value stored at the location designated by the pointer depending on the type of that value. Although the C compiler maintains this type information, the actual machine-level program it generates has no information about data types. It simply treats each program object as a block of bytes and the program itself as a sequence of bytes.

#### 2.1.1 Hexadecimal Notation
> A single byte consists of 8 bits. In binary notation, its value ranges from 000000002 to 111111112. When viewed as a decimal integer, its value ranges from 010 to 25510. Neither notation is very convenient for describing bit patterns. Binary notation is too verbose, while with decimal notation it is tedious to convert to and from bit patterns. Instead, we write bit patterns as base-16, or hexadecimal numbers.

![Figure2.2](https://upload-images.jianshu.io/upload_images/6543506-b98a0df16c2b4041.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### little endian 和 big endian
两种不同的排序方式，手机上面大部分都是little endian
![figure2.6](https://upload-images.jianshu.io/upload_images/6543506-86ec58851f91d003.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
#### Representing Strings
###### 0 means null in C??
>A string in C is encoded by **an array of characters** terminated by the null(having value 0) character.

#### boolean algebra
这个想法很有意思，我之前学propositional logic law 的时候没这么想过……
![image.png](https://upload-images.jianshu.io/upload_images/6543506-11cd402bcff6a02d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
#### 2.2 Integer representation

![Figure 2.8](https://upload-images.jianshu.io/upload_images/6543506-b01d7c6ab7d79d04.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### Two's complement encoding
为了实现负数，最大一位数被当作负数，然后之后的数都还是当作正数的，这样1111其实就是表达为-1，因为-8 + 7 等于-1.
下面是公式
![2.3 and 2.4](https://upload-images.jianshu.io/upload_images/6543506-d087ab91a44bafcc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![2.14](https://upload-images.jianshu.io/upload_images/6543506-f92ab69d6f419c48.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

>This line was generated by a disassembler, a tool that determines the instruction sequence represented by an executable program file. We will learn more about disassemblers and how to interpret lines such as this in Chapter 3. For now, we simply note that this line states that the hexadecimal byte sequence 01 05 43 0b 20 00 is the byte-level representation of an instruction that adds a word of data to the value stored at an address computed by adding 0x200b43 to the current value of the program counter, the address of the next instruction to be executed. If we take the final 4 bytes of the sequence 43 0b 20 00 and write them in reverse order, we have 00 20 0b 43.

我突然想起来谷歌那道面试题可能还是有实际作用的，因为你在reverse 一个由个别单词组成的string 而不用额外空间的时候好像这里就可以用到，因为它是按byte来读取的，而每台机器的byte order有可能不一样，所以有的机器需要做倒序处理，这样不用而外空间来操作就可以省出很多空间了，特别是读取数据量特别大的时候。

### Two's complement
有正负数的时候第一位永远都是表示这个数位是否是负，而那位的二进制表示如果是1，那么就是```-2^w```
所以unsigned转成signed数字的时候就是加上```-2^w```，因为第w位（最大位）的数字表示为负数了

#### Casting
In casting from unsigned to int, the underlying bit representation stays the same. This is a general rule for how most C implementations handle conversions between signed and unsigned numbers with the same word size -- the numeric values might change, but the bit patterns do not. 
The bit representation of 32 bit int for unsigned value is same as -1 bit pattern then it is signed int.
That is, 
>T2U32(−1) = 4,294,967,295, and U2T32(4,294,967,295) = −1. That is, UMax has the same bit representation in un- signed form as does −1 in two’s-complement form. We can also see the relationship between these two numbers: 1 + UMaxw = 2w.

Going the other direction, the most left bit value will represent negative. So the unsigned value will reduce by 2^w where w is the left most bit. When it is 4 bit word, change from unsigned to signed, the number will reduce 2 ^ 3. 
![2's complement](https://upload-images.jianshu.io/upload_images/6543506-2f670aa789cfd274.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### Integer Alrithmatic
两个w bit 长度的数相加需要w+1bits （因为会进位） 而如果我们只保存w bit 长度的结果，那么我们实际上是对两个数的和进行了```mod 2^(w)```的操作
> This can be characterized as a form of modular arithmetic, computing the sum modulo 2w by simply discarding any bits with weight greater than 2w−1 in the bit-level representation of x + y. For example, consider a 4-bit number representation with x = 9 and y = 12, having bit representations [1001] and [1100], respectively. Their sum is 21, having a 5-bit representation [10101]. But if we discard the high-order bit, we get [0101], that is, decimal value 5. This matches the value 21 mod 16 = 5.

### Overflow 
4 cases. This graph is helpful.
Case 1 Negative overflow
Case 2 Normal negative
Case 3 Normal positive
Case 4 Positive Overflow
![Overflow example for 4 bit int](https://upload-images.jianshu.io/upload_images/6543506-bd80543edb1388f8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
#### 与算法
因为two's complement 的性质，-x 跟 ~x + 1 是一样的，那么x & -x 其实就保留了最后一位1。
&其实就是对两个set取并集。而-x只有最后一位1是一样的。
![x&-x](https://upload-images.jianshu.io/upload_images/6543506-3c82343de2fddf68.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
### Integer multiplication
> Historically, the integer multiply instruction on many machines was fairly slow, requiring 10 or more clock cycles, whereas other integer operations—such as addition, subtraction, bit-level operations, and shifting—required only 1 clock cycle. Even on the Intel Core i7 Haswell we use as our reference machine, integer multiply requires 3 clock cycles. As a consequence, one important optimization used by compilers is to attempt to replace multiplications by constant factors with combinations of shift and addition operations. 

### float alrithmitic
因为float group不是associative，所以a+b+c != b+c+a，这很重要因为顺序matters。那么之前我们做测试，一个float 乘以很大的一个数的时候可能就把小数位忽略掉了。





## Chapter3

### Why need to understand machine code? 
> So why should we spend our time learning machine code? Even though com- pilers do most of the work in generating assembly code, being able to read and understand it is an important skill for serious programmers. By invoking the compiler with appropriate command-line parameters, the compiler will generate a file showing its output in assembly-code form. By reading this code, we can under- stand the optimization capabilities of the compiler and analyze the underlying inefficiencies in the code.

Programmers seeking to maximize the performance of a critical section of code often try different variations of the source code, each time compiling and examining the generated assembly code to get a sense of how efficiently the program will run. Furthermore, there are times when the layer of abstraction provided by a high-level language hides information about the run-time behavior of a program that we need to understand. For example, when writing concurrent programs using a thread package, as covered in Chapter12, **it is important to understand how program data are shared or kept private by the different threads and precisely how and where shared data are accessed.** Such information is visible at the machine-code level. **As another example, many of the ways programs can be attacked, allowing malware to infest a system, involve nuances of the way programs store their run-time control information.** Many attacks involve exploiting weaknesses in system programs to overwrite information and thereby take control of the system. Understanding how these vulnerabilities arise and how to guard against them requires a knowledge of machine-level representation of programs. 

The need for programmers to learn machine code has shifted over the years from one of being able to write programs directly in assembly code to one of being able to read and understand the code generated by compilers.

上次提到为什么要用C学系统：

![p34](https://upload-images.jianshu.io/upload_images/6543506-954f1f48c974d1e6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![p36](https://upload-images.jianshu.io/upload_images/6543506-2db892c25ab57f0f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
x86 is intel product line
![x86](https://upload-images.jianshu.io/upload_images/6543506-c6b344ed958fcb71.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![x86 product line](https://upload-images.jianshu.io/upload_images/6543506-8d538373180ddd18.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![moore's law](https://upload-images.jianshu.io/upload_images/6543506-2b294f4c58845680.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### Instruction set architecture
The format and behavior of a machine-level program is defined by the *instruction set architecture* or **ISA**. Most ISA describe the behavior of a program as if each instruction is executed in sequence, with one instructino completing before the next one begins. 
![ISA definition](https://upload-images.jianshu.io/upload_images/6543506-bfb12b1a4cf5e48a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
机器底层的实现逻辑永远是简单的，只不过经过了各种组合以及叠加才变得复杂并且能够实现近乎神奇般的功能
就好像air foil的作用，能组成gas turbines，也可以用来做机翼
![air foil](https://upload-images.jianshu.io/upload_images/6543506-32af1979063ab889.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### Assembly code

Assembly-code representation is very close to machine code. Its main feature is that it is a more readable textual format.

> Whereas C provides a model in which objects of different data types can be declared and allocated in memory, machine code views the memory as simply a large byte-addressable array. Aggregate data types in C such as arrays and structures are represented in machine code as contiguous collections of bytes.

The machine code for x86-64 differs greatly from the original C code. Parts of the processor state are visible that normally are hidden from the C programmer.

* The program counter (known as **PC**, and called **%rip** in x86-64) indicates the address in memory of the next instruction to be executed.
* The integer register file contains 16 named locations storing 64 bit values. These registers can hold addresses (corresponding to C pointers) or integer data. Some registers are used to keep track of critical parts of the program state, while others are used to hold temporary data, such as the arguments and local variables of a procedure, as well as the value to be returned by a function.
* The condition code registers hold status information about the most recently executed arithmetic or logical instruction. These are used to implement **if** and **while** statements.
* A set of vector registers can each hold one or more integer or floating-point values.

Machine code views the memory as simply a large byte-addressable array. Aggregate data types in C such as arrays are represented in machine code as contiguous collections of bytes.

> A single machine instruction performs only a very elementary operation. For example, it might add two numbers stored in registers, transfer data between memory and a register, or conditionally branch to a new instruction address. The compiler must generate sequences of such instructions to implement program constructs such as arithmetic expression evaluation, loops, or procedure calls and returns.

The program memory contains the executable machine code for the program, some information required by the OS, a run-time stack for managing **procedure calls** and returns (这里没准还要回来看), and blocks of memory allocated by the user (by **malloc** function). A program memory is addressed using virtual addresses. More typical programs will only have access to a few megabytes, or perhaps several gigabytes. OS manages this virtual address space, translating virtual addresses into the physical addresses of values in the actual processor memory.

### running code on linux
![Snip20210325_15.png](https://upload-images.jianshu.io/upload_images/6543506-0726fdc4841ee895.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
#### rax rbp 名字由来
> An x86-64 central processing unit (CPU) contains a set of 16 general-purpose registers storing 64-bit values. These registers are used to store integer data as well as pointers. Figure 3.2 diagrams the 16 registers. Their names all begin with %r, but otherwise follow multiple different naming conventions, owing to the historical evolution of the instruction set.
> The original 8086 had eight 16-bit registers, shown in Figure 3.2 as registers %ax through %bp. Each had a specific purpose, and hence they were given names that reflected how they were to be used. With the extension to IA32, these registers were expanded to 32-bit registers, labeled %eax through %ebp. 
> In the extension to x86-64, the original eight registers were expanded to 64 bits, labeled %rax through %rbp. In addition, eight new registers were added, and these were given labels according to a new naming convention: %r8 through %r15.

下面这张图很好表达了register 不同名字以及他们对应的大小
![figure3.2](https://upload-images.jianshu.io/upload_images/6543506-69bc0859534a16f7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![legacy](https://upload-images.jianshu.io/upload_images/6543506-d96c8473b2209e29.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![Operand Forms](https://upload-images.jianshu.io/upload_images/6543506-23f427bfb199468c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![Procedure data flow 22:08](https://upload-images.jianshu.io/upload_images/6543506-1554609d4143140e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

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
#### Procedure call

这个之前leon问到过，procedure call is same as function call or method call in OOD. It utilize stack to return to previous state. 

![8:56](https://upload-images.jianshu.io/upload_images/6543506-e4acbdf24e3d2e3a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![14:57](https://upload-images.jianshu.io/upload_images/6543506-c39d7b0b9970c1f8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### Pushing and poping stack data
![figure3.9](https://upload-images.jianshu.io/upload_images/6543506-d44f63283c680ffb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
The pushq instruction provides the ability to push data onto the stack, while the popq instruction pops it. Each of these instructions takes a single operand --the data source for pushing and the data destination for popping. 
Pushing a quad word value onto the stack involves first decrementing the stack pointer by 8 and then writing the value at the new top-of-stack address. Therefore, the behavior of the instruction pushq %rbp is equivalent to that of the pair of instructions 
```c
subq $8, %rsp //Decrement stack pointer
movq %rbp, (%rsp)  //store %rbp on stack
```
except that the pushq instruction is encoded in the machine code as a single byte, whereas the pair of instructions shown above requires a total of 8 bytes. The first two columns in Figure 3.9 illustrate the effect of executing the instruction pushq %rax when %rsp is 0x108 and %rax is 0x123. 

The third column of Figure 3.9 illustrates the effect of executing the instruction opoq %edx immediately after executing the **pushq**. Value 0x123 is read from memory and written to register %rdx. Register %rsp is incremented back to 0x108. As shown in the figure, the value 0x123 remains at memory location 0x104 until it is overwritten (e.g. by another push operation). However, the stack popo is always considered to be the address indicated by %rsp.

Since the stack is contained in the same memory as the program code and other forms of program data, programs can access arbitrary positions within the stack using the standard memory addressing methods. For example, assuming the topmost element of the stack is quad word, the instruction **movq 8(%rsp), %rdx will copy the second quad word from the stack to register %rdx
![45:28](https://upload-images.jianshu.io/upload_images/6543506-e040d856de892b0e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

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
![1:07:47](https://upload-images.jianshu.io/upload_images/6543506-dc9467aabb16db2d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

The third group consists of binary operations, where the second operand is used as both a source and a destination. This syntax is reminiscent of the C assignment operators, such as x -= y. Observe, however, that the source operand is given first and the destination second. This looks peculiar for noncommutative operations. For example, the instruction subq %rax, %rdx decrements register %rdx by the value %rax The first operand can be either an immediate value, a register, or a memory location. The second can be either a register or a memory location. As with the MOV instructions, the two operands cannot both be memory locations. Note that when the second operand is a memory location, the processor must read the value from memory, perform the operation, and then write the result back to memory.

#### 3.5.3 shift operations
The final group consists of shift operations, where the shift amount is given first and the value to shift is given second. Both arithmetic and logical right shifts are possible. the different shift instructions can specify the shift amount either as an immediate value or with the single-byte register %cl. In principle, having a 1-byte shift amount would make it possible to encode shift amounts ranging up to 2^8-1 = 255. With x86-64, a shift instruction operating on data values that are w bits long determines the shift amount from the low-order m bits of register %cl, where 2^m = w. The higher-order bits are ignored. So, for example, when register %cl has hexadecimal value 0xFF, then instruction salb would shift by 7 (one byte), while salw would shift by 15(2byte). sall would shift by 31, and salq would shift by 63.

There are two names for the left shift instruction: SAL and SHL, both have same effect, filling from the right with zeros. The right shift instructions differ in that SAR performs an arithmetic shift (fill with copies of the sign bit), for example -8 >> 1 gives 1100 in four digit representation. The destination operand of a shift operation can be either a register or a memory location. Right shift has two type (arithmetic and logical)

#### 3.5.4 discussion
We see that most of the instructions shown in figure 3.10 can be used for either unsigned or two's complement arithmetic. Only right shifting requires instructions that differentiate between signed versus unsigned data. This is one of the features that makes two's-complement arithmetic the preferred way to implement signed integer arithmetic. 
talk about figure 3.11 as example
Figure 3.11 shows an example of a function that performs arithmetic operations and its translation into assembly code. Arguments x, y, and z are initially stored in registers %rdi, %rsi, and %rdx, respectively. the assembly-code instructions correspond closely with the lines of C source code. 

#### 3.5.5 Special arithmetic operations
As we saw in Section 2.3, multiplying two 64-bit signed or unsigned integers can yield a product that requires 128 bits to represent. The x86-63 instruction set provides limited suport for operations involving 128-bit numbers. Continueing with the naming convention of word, double word, and quad word, Intel refers to a 16 byte quantity as an oct word. 
```c
void remdiv(long x, long y, long *qp, long *rp) {
  long q = x/y;
  long r = x%y;
  *qp = q;
  *rp = r;
}
```
```assembly
 remdiv:
  movq    %rdx, %r8
  movq    %rdi, %rax
  cqto 
  idivq     %rsi
  movq    %rax, (%r8)
  movq    %rdx, (%rcx)
  ret
```
### 3.6 Control
Machine code provides two basic low-level mechanisms for implementing conditional behavior: it tests data values and then alters either the control flow or the data flow based on the results of these tests.
Data-dependent control flow is the more general and more common approach for implementing conditional behavior. The execution order of a set of machine code instructions can be altered with a jump instruction, indicating that control should pass to some other part of the program, possibly contingent on the result of some test. The compiler must generate instruction sequences that build upon this low-level mechanism to implement the control constructs of C. 
![5:02](https://upload-images.jianshu.io/upload_images/6543506-be1cde9d9c48c8c6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
%rsp is stack pointer to current stack top
%rip is instruction pointer to current instruction

#### 3.6.1 Condition codes
Machine code provides two basic low-level mechanisms for implementing conditional behavior:
1. it tests data values and then alters either the control flow
2. the data flow based on the results of these tests

Book talked about data-dependent control flow first because it is more general
Normally, both statements in C and instructions in machine code are executed sequentially, in the order they appear in the program. **jump instruction can alter the execution order**, indicating that control should pass to some other part of the program, possibly result from some test. 
CPU maintains a set of single-bit condition code registers describing attributes of the most recent arithmetic or logical operation. These registers can then be tested to perform conditional branches. These condition codes are the most useful:
> **CF**: Carry flag. The most recent operation generated a carry out of the most significant bit. Used to detect overflow for unsigned operations. 
> **ZF**: Zero flag. The most recent operation yielded zero.
> **SF**: Sign flag. The most recent operation yielded a negative value.
> **OF**: Overflow flag. The most recent operation caused a two's complement overflow--either negative or positive.

Rather than reading the condition codes directly, there are three common ways of using the condition codes:
1. we can set a single byte to 0 or 1 depending on some combination of the condition codes
2. we canconditionally jump to some other part of the program
3. we can conditionally transfer data. 
> In addition to the setting of condition codes by the instructions of Figure 3.10, there are two instruction classes (having 8-, 16-, 32-, and 64-bit forms) that set condition codes without altering any other registers; 

compare instruction
cmpq src2, src1
cmpq b, a like computing a-b without setting destination

![3.13](https://upload-images.jianshu.io/upload_images/6543506-d2b492e36e508f5b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![figure 3.14](https://upload-images.jianshu.io/upload_images/6543506-9842734c337f6009.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

Test instruction
testq src2, src1
testq b, a like computing a&b without setting destination
#### 3.6.3 Jump Instructions
A jump instruction can cause the execution to switch to a completely new position in the program. These jump destinations are generally indicated in assembly code by a *label*. 

![figure 3.15](https://upload-images.jianshu.io/upload_images/6543506-102038c1db740cc0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 3.6.4 Jump instruction Encodings
For the most part, we will not concern ourselves with the detailed format of machine code. on the other hand, understanding how the targets of jump instructions are encoded will become more important when we study linking in Chapter 7. In addition, it helps when interpreting the output of a disassembler. In assembly code, jump targets are written using symbolic labels. The assembler, and later the linker, generate the proper encodings of the jump targets. there are several different encodings for jumps, but some of the most commonly used ones are PC relative. That is, they encode the difference between the address of the target instruction and the address of the instruction immediately following the jump. These offsets can be encoded using 1, 2, or 4 bytes. A second encoding method is to give an "absolute" address, using 4 bytes to directly specify the target. 
* conditional control
* conditional move 
> The assembler and linker select the appropriate encodings of the jump destinations. 

#### 3.6.5 Implementing conditional branches with conditional control
The most general way to translate conditional expressions and statements from C into machine code is to use combinations of conditional and unconditional jumps. For example, Figure 3.16 shows the C code for a function that computes the absolute value of the difference of two numbers . The function also has a side effect of incrementing one of two counters, encoded as global variables It_cnt and ge_cnt. GCC generates the assembly code shown as Figure 3.16c. 
> 3.16b shows goto version in C code of the original code

![figure3.16](https://upload-images.jianshu.io/upload_images/6543506-48a9e3db1f9ccd70.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
Assembly implementation typically adheres to the following form, where we use C syntax to describe the control flow:
```c
  t = test-expr;
  if (!t) {
    goto false;
  then-statement
  goto done;
false:
    else-statement;
done:
```

why conditional data transfers can outperform code based on conditional control transfers? 
> As we will see in Chapters 4 and 5, processors achieve high performance through pipelining 
> When the machine encounters a conditional jump (re- ferred to as a “branch”), it cannot determine which way the branch will go until it has evaluated the branch condition. Processors employ sophisticated branch pre- diction logic to try to guess whether or not each jump instruction will be followed. Mispredicting a jump, on the other hand, requires that the processor discard much of the work it has already done on future instructions and then begin filling the pipeline with instructions starting at the correct location. In a typical application, the outcome of the test x < y is highly unpredictable, and so even the most sophisticated branch prediction hardware will guess correctly only around 50% of the time. In addition, the computations performed in each of the two code sequences require only a single clock cycle. As a consequence, the branch misprediction penalty dominates the performance of this function. 

As described in class lecture, the CPU is like a boat with full speed. So it's hard for it to turn to different direction. Rather tell it to turn, we could run it until it have to turn

To understand how conditional operations can be implemented via condi- tional data transfers, consider the following general form of conditional expression and assignment:
```c
v = test-expr ? then-expr : else-expr;
```
for the code based on a conditional move, both the then-expr and the else-expr are evaluated, with the final value choasen based on the evaluation test-expr. This can be described by the following abstract code:
```c
v = then-expr;
ve = else-expr;
t = test-expr;
if (!t) v = ve;
```
The final statement in this sequence is implemented with a conditional move -- value ve is copied to v only if test condition t does not hold.

at the end, they still use conditional control transfer more.. So conditional data transfer is an alternative
> Compilers must take into account the relative performance of wasted computation versus the potential for performance penalty due to branch misprediction. In truth, they do not really have enough information to make this decision reliably; for example, they do not know how well the branches will follow predictable patterns. Our experiments with gcc indicate that it only uses conditional moves when the two expressions can be computed very easily, for example, with single add instructions. In our experience, gcc uses conditional control transfers even in many cases where the cost of branch misprediction would exceed even more complex computations.


#### 3.6.7 loops
C provides several looping 
* do-while
* while
* for
No corresponding instructions exist in machine code. Combinations of conditional tests and jumps are used to implement the effect of loops
##### do while
```c
do
  body-statement;
  while (test-expr);
```
![figure 3.19](https://upload-images.jianshu.io/upload_images/6543506-09bbfcb585331908.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### while
```c
while (test-expr)
  body-statement
```
First translation method
![figure 3.20](https://upload-images.jianshu.io/upload_images/6543506-097e770e12588dd5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
The second translation method, which we refer to as *guarded do*, first transforms the code into a do-while loop by using a conditional branch to skip over the loop if the initial test fails. 

> GCC follows this strategy when compiling with higher levels of optimization, for example, with command-line option -O1. This method can be expressed by the following template for translating from the general while loop form to a do-while loop:
```c
t = test-expr;
if (!t)
  goto done;
do
  body-statement;
  while (test-expr);
done:
```
![figure 3.21](https://upload-images.jianshu.io/upload_images/6543506-c88ae3105a16264b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
##### for loop
```c
for (init-expr; test-expr; update-expr)
  body-statement
```
The C language standard states (with one exception), that the behavior of such a loop is identical to the following code using a while loop:
```c
init-expr;
while (test-expr) {
  body-statement;
  update-expr;
}
```
> the program first evaluates the initialization expression init-expr. It enters a loop where it first evaluates the test condition test-expr, exiting if the test fails, then executes the body of the loop body-statement, and finally evaluates the update expression update-expr.

##### switch statement
> Not only do they make the C code more readable, but they also allow an efficient implementation using a data structure called a jump table. 

A jump table is an array where entry i is the address of a code segment implementing the action the program should take when the switch index equals i. The code performs an array reference into the jump table using the switch index to determine the target for a jump instruction.

highlighted in picture is the assembly code that referencing a jump table
![figure 3.22 &3.33](https://upload-images.jianshu.io/upload_images/6543506-92b0b99a1eeb40d4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![1:00:55](https://upload-images.jianshu.io/upload_images/6543506-f1e2e6467ee1a54b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![1:13:13](https://upload-images.jianshu.io/upload_images/6543506-eeefdc8179c871f6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 3.7 procedures
Procedures come in many guises in different programming languages -- functions, methods, subroutines, handlers, and so on
The following will be involve with procedures
* Passing control. The program counter must be set to the starting address of the code for Q upon entry and then set to the instruction in P following the call to Q upon return.
* Passing data. P must be able to provide one or more parameters to Q, and Q must be able to return a value back to P.
* Allocating and deallocating memory. Q may need to allocate space for local variables when it begins and then free that storage before it returns.

if the procedure can be stored on the register, then this procedure call won't be allocated to new spaces, 
when an x86 procedure requires storage beyond what it can hold in registers, it allocates space on the stack. (by decreasing sp address with appropriate size)
and when Q finishes, the caller address will be restored on sp and local storage it has allocated can be freed. (increase sp)

![figure3.25](https://upload-images.jianshu.io/upload_images/6543506-d8c1cefa2538b6b3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### 3.7.2 control transfer
Passing control from P to Q simply set the program counter (PC) to the starting address of the code for Q.
```call Q``` will record the P address when it is invoked. 

![figure3.27](https://upload-images.jianshu.io/upload_images/6543506-ade9bc3e4d695b99.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


The effect of the call is to push the return address 0x400568 onto the stack and to jump to the first instruction in function multstore continues until it hits the ret instruction at address 0x40054d. This instruction pops the value 0x400568 from the stack and jumps to this address, resuming the excution of main just after the call instruction.

As a more detailed example of passing control to and from procedures, Figure 3.27 shows the disassembled code for two functions, top and leaf, as well as the portion of code in function main where top gets called. 

stack pointer is a pointer to a value of memory space. When function returns, it dereference the sp to get its value and set that value back to the PC.

##### 3.7.3 data transfer
In addition to passing control to a procedure when called, and then back again when the procedure returns, procedure calls may involve passing data as arguments, and returning from a procedure may also involve returning a value. With x86-64, most of these data passing to and from procedures take place via registers. For example, we have already seen numerous examples of functions where arguments are passed in registers %rdi, %rsi, and others. and where values are returned in register %rax. 

When procedure P calls procedure Q, the code for P must first copy the arguments into the proper registers. Similarly, when Q returns back to P, the code for P can access the returned value in register %rax. In this section, we explore these conventions in greater detail.

With x86-64, up to six integral (i.e. integer and pointer) arguments can be passed via registers. The registers are used in a specified order, with the name used used for a register depending on the size of the data type being passed. these are shown in Figure 3.28. Arguments are allocated to these registers according to their 
ordering in the argument list. Arguments smaller than 64 bits can be accessed using the appropriate subsection of the 64-bit register. For example, if the first argument is 32 bits, it can be accessed as %edi.

![figure 3.28](https://upload-images.jianshu.io/upload_images/6543506-8eba091013cff53c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

When a function has more than six integral arguments, the other ones are passed on the stack. Assume that procedure P calls procedure Q with n integral arguments, such that n > 6. Then the code for P must allocate a stack frame with enough storage for arguments 7 at the top of the stack. When passing parameters on the stack, all data sizes are rounded up to be multiples of eight. With the arguments in place, the program can then execute a **call** instruction to transfer control to procedure Q. Procedure Q can access its arguments via registers and possibly from the stack. If Q, in turn, calls some function that has more than six arguments, it can allocate space within its stack frame for these, as is illustrated by the area labeled "Argument build area" in Figure 3.25.

In summary, the procedure will copy the variable on to the stack first and then give the control to the callee

As an example of argument passing, consider the C function proc shown in Figure 3.29(a). This function has eight arguments, including integers with different numbers of bytes(8, 4, 2, and 1), as well as different types of pointers, each of which is 8 bytes.

The assembly code generated for proc is shown in Figure 3.29(b). The first 
![figure 3.29](https://upload-images.jianshu.io/upload_images/6543506-08c33bf36d3666e2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### 3.7.4 local storage on the stack
Most of the procedure examples we have seen so far did not require any local storage beyond what could be held in registers. At times, however, local data must be stored in memory. 
suppose procedure P calls procedure Q, and Q then executes and returns back to P.
Common cases of this include these:
* There are not enough registers to hold all of the local data.
* The address operator '&' is applied to a local variable, and hence we must be able to generate an address for it.
* Some of the local variables are arrays or structures and hence must be accessed by array or structure references. We will discuss this possibility when we describe how arrays and structures are allocated.

Typically, a procedure allocates space on the stack frame by decrementing the stack pointer. This results in the portion of the stack frame labeled "Local variables" in figure 3.25
As an example of the handling of the address operator, consider the two functions shown in Figure 3.31(a)

The code for caller starts by decrementing the stack pointer by 16; this effectively allocates 16 bytes on the stack. Letting S denote the value of the stack pointer, we can see that the code computes &arg2 as S+8, &arg1 as S. Therefore, local variables arg1 and arg2 are stored within the stack frame at offsets 0 and 8 relative to the stack pointer.
![figure 3.31](https://upload-images.jianshu.io/upload_images/6543506-a75383e57809ef68.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

Then when the function returns caller will get arg1 value by reading from (%rsp) and read arg2 from 8(%rsp) increase the pointer address by 8 byte then subtract it from arg1 (stored in rdx)

![figure 3.32](https://upload-images.jianshu.io/upload_images/6543506-fe053688b5b51ad6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### 3.7.5 Local Storage in Registers
In order to make sure callee does not overwrite some register value that the caller planned to use later. x86 adopts a uniform set of conventions for register usage that must be respected by all procedures.
> By convention, registers %rbx, %rbp, and %r12–%r15 are classified as callee- saved registers.

callee saved register must be preserved by the callee.
![figure3.34](https://upload-images.jianshu.io/upload_images/6543506-c90c89b1463d4129.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
value x and y won't be changed after this procedure call.

##### recursive call
![figure3.35](https://upload-images.jianshu.io/upload_images/6543506-e1a167f2e6b9d5ca.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
it is naturally implemented by the stack when we recursively call the function because %rbx will store the data by the callee and the %rax will give the return result. When condition has met, return. If not, it will keep calling itself and store rbx

### 3.8 Array Allocation and access
Arrays in C are one means of aggregating scalar data into larger data types. C uses a particularly simple implementation of arrays, and hence the translation into machine code is fairly straightforward. One unusual feature of C is that we can generate pointers to elements within arrays and perform arithmetic with these pointers. These are translated into address computations in machine code.

Optimizing compilers are particularly good at simplifying the address computations used by array indexing. This can make the correspondence between the C code and its translation into machine code somewhat difficult to decipher.

##### 3.8.1 Basic Principles

For datatype T and integer constant N, consider a declaration of the form T a[n]
Let us denote the starting location as xa. The declaration has two effects. First, it allocates a contiguous region of L * N bytes in memory where L is the size of data type T. second, it introduces an identifier A that can be used as a pointer to the beginning of the array. The value of this pointer will be xa. The array elements can be accessed using an integer index ranging between 0 and N-1.
Array element i will be stored at address xa + L * i

pointer has size of 8 bytes 

The memory referencing instructions of x86-64 are designed to simplify array access. For example, suppose E is an array of values of type int and we wish to evaluate E[i], where the address of E is stored in register %rdx and i is stored in register %rcx. 
Then ```movl (%rdx, %rcx, 4), %eax```
will perform the address computation xe + 4i, read that memory location, and copy the result to register %eax. The allowed scaling factors of 1,2,4,and 8 cover the sizes of the common primitive data types. 
#### 3.8.2 Pointer arithmetic 
The unary operators '&' and '*' allow the generation and dereferencing of pointers. That is, for an expression Expr denoting some object, &Expr is a pointer giving the address of the object. FOr an expression AExpr denoting an address, *AExpr gives the value at that address. The expressions Expr and *&Expr are equivalent. The array subscripting operation can be applied to both arrays and pointers The array reference A[i] is identical to the expression *(A+i); It computes the address of the ith array element and then accesses this memory location. Expanding on our earlier example, suppose the starting address of integer array E and integer index i are stored in registers %rdx and %rcx, respectively. The following are some expressions involving E. We also show an assembly-code implementation of each expression, with the result being stored in either register %eax or register %rax

![image.png](https://upload-images.jianshu.io/upload_images/6543506-4d410b33d79e22cf.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

In these examples, we see that operations that return array values have type int, and hence involve 4-byte operations and registers (e.g. %eax). Those that return pointers have type int *, and hence involve 8-byte operations and registers. The final example shows that one can compute the difference of two pointers within the same data structure, with the result being data having type long and value equal to the difference of the two addresses divided by the size of the data type

##### 3.8.3 Nested Arrays
The general principles of array allocation and referencing hold even when we create arrays of arrays. For example, the declaration
```int A[5][3];```
is equivalent to the declaration 
```c
typedef int row3_t [3];
row3_t A[5];
```
data type row3_t is defined to be an array of three integers. Array A contains five such elements, each requiring 12 bytes to store the three integers. The total array size is then 4 * 5 * 3 = 60 bytes.

The array elements are ordered in memory in row-major order, meaning all elements of row 0, which can be written A[0], followed by all elements of row 1 (A[1]), and. so on. This is illustrated in Figure 3.36.

![figure 3.36](https://upload-images.jianshu.io/upload_images/6543506-7920158a8742fd25.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

This ordering is a consequence of our nested declaration. Viewing A as an array of five elements, each of which is an array of three int's, we first have A[0], followed by A[1], and so on.

To access elements of multidimensional arrays, the compiler generates code to compute the offset of the desired element and then uses one of the MOV instructions with the start of the array as the base address 

##### Fixed size arrays
Figure 3.37b contains a number of clever optimizations. It removes the integer index j and converts all array references to pointer derederences. this involves 
1. generating a pointer, which we have named Aptr, that points to successive elements in row i of A
2. generating a pointer, which we have named Bptr, that points to successive elements in column k of B
3. Generating a pointer, which we have named Bend, that equals the value Bptr will have when it is time to terminate the loop. The initial value for Aptr is the address of the first element of row i of A, given by the C expression &A[i][0]. The initial value for Bptr is the address of the first element of column k of B, given by the C expression &B[0][k]. The value for Bend is the index of what would be the (n+1)st element in column j of B, given by the C expression &B[N][k].
![figure3.37](https://upload-images.jianshu.io/upload_images/6543506-9865d384fffbfb80.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### Variable-size arrays
Historically, C only supported multidimensional arrays where the sizes (with the possible exception of the first dimension) could be determined at compile time. 
Programmers requiring variable-size arrays had to allocate storage for these arrays using functions such as malloc or calloc, and they had to explicitly encode the mapping of multidimensional arrays into single-dimensino ones via row-major indexing, as expressed in Equation 3.1
C99 introduced the capability of having array dimension expressions that are computed as the array is being allocated. 

In the C version of variable-size arrays, we can declare an array int A[expr1][expr2]
either as a local variable or as an argument to a function, and then the dimensions of the array are determined by evaluating the expressions expr1 and expr2 at the time the declaration is encountered. So, for example, we can write a function to access element i, j of an n x n array as follows:
```c
int var_ele(long n, int A[n][n], long i, long j) {
  return A[i][j];
}
```
The parameter n must precede the parameter A[n][n], so that the function can compute the array dimensions as the parameter is encountered.
Gcc generates code for this referencing function as 
```assembly
var_ele:
  imulq %rdx, %rdi
  leaq   (%rsi, %rdi, 4), %rax
  movl   (%rax, %rcx, 4), %eax
  ret
```
As the annotations show, this code computes the address of element i, j as xa + 4(n*i) + 4j 

When variable-size arrays are referenced within a loop, the compiler can often opimize the index computations by exploiting the regularity of the access patterns. For example, Figure 3.38(a) shows C code to compute element i, k of the product of two n x n arrays A and B. Gcc generates assembly code, which we have recast into C figure 3.38b. This code follows a different style from the optimized code for the fixed-size array, but that is more an artifact of the choices made by the compiler, rather than a fundamental requirement for the two different functions. The code of Figure 3.38 retains loop variable j, both to detect when the loop has terminated and to index into an array consisting of the elements of row i of A.
The following is the assembly code for the loop of var_prod_ele:

![figure3.38](https://upload-images.jianshu.io/upload_images/6543506-d07323ffa1c28c8b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 3.9 Heterogeneous data structures
struct aggregate multiple objects into a single unit; unions, declared using the keyword union, allow an object to be referenced using several different types.

##### 3.9.1 Structures
The C struct declaration creates a data type that groups objects of possibly different types into a single object. The different components of a structure are referenced by names. The implementation of structures is similar to that of arrays in that all of the components of a structure are stored in a contiguous region of memory and a pointer to a structure is the address of its first byte. The compiler maintains information about each structure type indicating the byte offset of each field. It generates references to structure elements using these offset of each field. It generates references to structure elements using these offsets as displacements in memory referencing instructions.

##### 3.9.2 unions
Unions provide a way to circumvent the type system of C, allowing a single object to be referenced according to multiple types. The syntax of a union declaration is identical to that for structures, but its semantics are very different. Rather than having the different fields reference different blocks of memory, they all reference the same block.

Consider the following declarations:
```c
struct S3 {
  char c;
  int i[2];
  double v;
}
union U3 {
  char c;
  int i[2];
  double v;
}
```

![image.png](https://upload-images.jianshu.io/upload_images/6543506-d02586a20015b2c6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
##### Data alignment 
Restrictions on data in order to have a good memory performance

##### Buffer Overflow
Most common security issue is from buffer overflow
attacker can insert code they want to execute by buffer overflow

![image.png](https://upload-images.jianshu.io/upload_images/6543506-7c745d8853087e89.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

Internet worm (1988) 
IM war(1999)
![image.png](https://upload-images.jianshu.io/upload_images/6543506-6454297440b1f51c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![image.png](https://upload-images.jianshu.io/upload_images/6543506-5ae54c3c35e84ca9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![image.png](https://upload-images.jianshu.io/upload_images/6543506-d6d2c0840a9b299c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

Worm run on itself, propagate itself to other computers
Virus add itself to other programs but does not run independently

How to mitigate buffer overflow?
1. Avoid overflow vulnerabilities in code (use fgets instead of gets)
2. Randomized stack offsets (ASLR)
3. Avoid file to be executable 
4. Canaries (place special value on stack just beyond buffer

### Summary
We have get a view of machine-level programming. We gain insights into both the compiler and its optimization capabilities, along with the machine, its data types, and its instruction set.

We also gotten mote complete picture of how the program stores data in different memory regions. 

Machine level code is expressed as a sequence of instructions, each of which performs a single operation. Parts of the program state, such as registers and the run-time stack, are directly visible to the programmer. 

## Chapter 5

![image.png](https://upload-images.jianshu.io/upload_images/6543506-a67a295b40c2a9d0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 

#### 5.4 Eliminating loop inefficiencies

Observe that procedure combine1, as shown in Figure 5.5, calls functino vec_length as the test condition of the for loop. Recall from our discussion of how to translate code containing loops into machine-level programs that the test condition must be evaluate on every iteration of the loop. On the other hand, the length of the vector does not change as the loop proceeds. We could therefore compute the vector length only once and use this value in our test condition.

Figure 5.6 shows a modified version called combine2. It calls vec_length at the beginning and assigns the result to a local variable length. This transformation has noticeable effect on the overall performance for some data types and operations, and minimal or even none for others. In any case, this transformation is required to eliminate inefficiencies that would become bottlenecks as we attempt further optimizations. 

##### Reduce procedure calls
As we have seen, procedure calls can incur overhead and also block most forms of program optimization. We can see in the code for combine2 (figure 5.6) that get_vec_element is called on every loop iteration to retrieve the next vector element. This function checks the vector index i against the loop bounds with every vector reference, a clear source of inefficiency. Bounds checking might be a useful feature when dealing with arbitrary array accesses, but a simple analysis of the code for combine2 shows that all references will be valid.



![figure 5.6](https://upload-images.jianshu.io/upload_images/6543506-ff18338c06c5fa1d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![figure 5.9](https://upload-images.jianshu.io/upload_images/6543506-21f7daa3b55547be.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 5.6 Eliminating unneeded memory references
The code for combine3 accumulates the value being computed by the combining operation at the location designated by the pointer dest. this attribute can be seen by examining the assembly code generated for the inner loop of the compiled code. We show here the x86-64 code generated for data type double and with multiplication as the combining operation:

We see in this loop code that the address corresponding to pointer dest is held in register %rbx. It has also transformed the code to maintain a pointer to the ith data element in register %rdx, shown in the annotations as data+i. This pointer is incremented by 8 on every iteration. The loop termination is detected by comparing this pointer to one stored in register %rax. We can see that the accumulated value is read from and written to memory on each iteration. this reading and writing is wasteful, since the value read from dest at the begining of each iteration should simply be the value written at the end of the previous iteration.
We can eliminate this needless reading and writing of memory by rewriting the code in the style of combine4 in figure5.10. We introduce a temporary variable acc that is used in the loop to accumulate the computed value. The result is stored at dest only after the loop has been completed. As the assembly code that follows shows, the compiler can now use register %xmm0 to hold the accumulated value. Compared to the loop in combine3, we have reduced the memory operations per iteration from two reads and one write to just a single read.


> holding the accumulated value in local variable acc eliminated the need to retrieve it from memory and write back the updated value on every loop iteration
> ![figure5.10](https://upload-images.jianshu.io/upload_images/6543506-adb1cb18ba83ef52.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
> We see a significant improvement in program performance, as shown in the following table 
> ![image.png](https://upload-images.jianshu.io/upload_images/6543506-fbf4711140e1e3f5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
> All of our times improve by factors ranging from 2.2 to 5.7, with the integer addition case fropping to just 1.27 clock cycles per element.
> Again, one might think that a compiler should be able to automatically transform the combine3 code shown in figure 5.9 to accumulate the value in a register, as it does with the code for combine4 shown in figure 5.10. In fact, however, the two functions can have different behaviors due to memory aliasing. Consider, for example, the case of integer data with multiplication as the operation and 1 as the identity element. Let v = [2,3,5] be a vector of three elements and consider the following two function calls:

combine3(v, get_vec_start(v) + 2);
combine4(v, get_vec_start(v) + 2);
![image.png](https://upload-images.jianshu.io/upload_images/6543506-40140619cf2ce715.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 5.7 Understanding modern processors
Up to this point, we have applied optimizations that did not rely on any features of the target machine. They simply reduced the overhead of procedure calls and eliminated some of the critical "optimization blockers" that cause difficulties for optimizing compilers. As we seek to push the performance further, we must consider optimizations that exploit the microarchitecture of the processor -- that is, the underlying system design by which a processor executes instructions. Getting every last bit of performance requires a detailed analysis of the program as well as code generation tuned for the target processor. Nonetheless, we can apply some basic optimizations that will yield an overall performance improvement on a large class of processors. the detailed performance results we report here may not hold for other machines, but the general principles of operation and optimization apply to a wide variety of machines. 

To understand ways to improve performance, we require a basic understanding of the microarchitectures of modern processors. Due to the large number of transistors that can be integrated onto a single chip, modern microprocessors employ complex hardware that attempts to maximize program performance. one result is that their actual operation is far different from the view that is perceived by looking at machine-level programs. At the code level, it appears as if instructions are executed one at a time, where each instructino involves fetching values from registers or memory, performing an operation, and storing results back to a register or memory location. In the actual processor, a number of instructions are evaluated simultaneously, a phenomenon referred to as instruction-level parallelism. In some designs, there can be 100 or more instructions "in flight." Elaborate mechanisms are employed to make sure the behavior of this parallel execution exactly captures the sequential semantic model required by the machine-level program. this is one of the remarkable feats of modern microprocessors: they employ complex and exotic microarchitectures, in which multiple instructions can be executed in parallel, while presenting an operational view of simple sequential instruction execution.

Although the detailed design of a modern microprocessor is well beyond the scope of this book, having a general idea of the principles by which they operate suffices to understand how they achieve instruction-level parallelism. We will find that two different lower bounds characterize the maximum performance of a program. The latency bound is encountered when a series of operations must be perfromed in strict sequence, because the result of on operation is required before the next one can begin. This bound can limit program performance when the data dependencies in the code limit the ability of the processor to exploit instruction-level parallelism. The throughput bound characterizes the raw computing capacity of the processor's functional units. This bound becomes the ultimate limit on program performance.

##### 5.7.1 Overall operation 
Figure 5.11 shows a very simplified view of a modern microprocessor. Our hypothetical processor design is based loosely on the structure of recent Intel processors. these processors are described in the industry as being superscalar, which means they can perform multiple operations on every clock cycle and out of order, meaning that the order in which instructions execute need not correspond to their ordering in the machine-level program. The overall design has two main parts: the *instruction control unit* (ICU), which is responsible for reading a sequence of instructions from memory and generating from these a set of primitive operations to perform on program data, and the execution unit (EU), which then executes these operations. out-of-order processors require far greater and more complex hardware, but they are better at achieving higher degrees of instruction-level parallelism.

Branch (conditional jump) can be costly, modern processors employ a technique known as branch prediction, in which they guess whether or not a branch will be taken and also predict the target address for the branch. Using a technique known. as speculative execution, calculates the branch and determine wether if this branch will execute or not.

The *instruction decoding logic takes the actual program instructions and converts them into a set of primitive operations (sometimes referred to as micro-operations) each of these operations performs some simple computational task such as adding two numbers, reading data from memory, or writing data to memory. For machines with complex instructions, such as x86 processors, an instruction can be decoded into multiple operations. The details of how instructions are decoded into sequences of operations varies between machines, and this information is considered highly proprietary. Fortunately, we can optimize our programs without knowing the low-level details of a particular machine implementation. In a typical x86 implementation, an instruction that only operates on registers. 

![figure 5.11](https://upload-images.jianshu.io/upload_images/6543506-e8a530306695558f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

The EU receives operations from the instruction fetch unit. Typically, it can receive a number of them on each clock cycle. These operations are dispatched to a set of functional units that perform address computations. Similarly, the store unit handles operations that write data from the processor to the memory. It also has an adder to perform address computations. As shown in the figure, the load and store units access memory via a data cache, a high-speed memory containing the most recently accessed data values.

With speculative execution, the operations are evaluated, but the final results are not stored in the program registers or data memory until the processor can be certain that these instructions should actually have been executed. Branch operations are sent to the EU, not to determine where the branch should go, but rather to determine whether or not they were predicted correctly. If the prediction was incorrect, the EU will discard the results that have been computed beyond the branch point. it will also signal the branch unit that the prediction was incorrect fetching at the new location. 

Figure 5.11 indicates that the different functional units are designed to perform different operations. those labeled as performing "arithmetic operations" are typically specialized to perform different combinations of integer and floating-point operations. As the number of transistors that can be integrated onto a single microprocessor chip has grown over time, successive models of microprocessors have increased the total number of functional units, the combinations of operations each unit can perform, and the performance of each of these units. The arithmetic units are intentionally designed to be able to perform a variety of different operations, since the required operations vary widely across different programs. For example, some programs might involve many integer operations, while others require many floating-point operations. If one functional unit were specialized to perform integer operations while another could only perform floating-point operations, then none of these programs would get the full benefit of having multiple functional units.

in the above list, "integer arithmetic" refers to basic operations. A store operation requires two functional units -- one to compute the store address and one to actually store the data. 

Within the ICU, the retirement unit keeps track of the ongoing processing and makes sure that it obeys the sequential semantics of the machine-level program. 

First, once the operations for the instruction have completed and any branch points leading to this instruction are confirmed as having been correctly predicted, the instruction can be retired, with any updates to the program registers being made. If some branch point leading to this instruction was mispredicted, on the other hand, the instruction will be flushed, idscarding any results that may have been computed. by this means, mispredictions will not alter the program state. 

The most common mechanism for controlling the communication of operands among the execution units is called register renaing. When an instruction that updates register r is decoded, a tag t is generated giving a unique identifier to the result of the operation. An entry (r, t) is added to a table maintaining the association between program register r and tag t. for an operation that will update this register. When a subsequent. instruction using register r as an operand is decoded, the operation sent to the execution unit will contain t as the source for the operand value. When some execution unit completes the first operation, it generates a result (v,t), indicating that the operation with tag t produced value v. Any operation waiting for t as a source will then use v as the source value, a form of data forwarding. By this mechanism, values can be forwarded directly from one operation to another, rather than being written to and read from the register file, enabling the second operation to begin as soon as the first has completed. The renaming table only contains entries for registers having pending write operations. When a decoded instruction requires a register r, and there is no tag associated with this register, the operand is retrieved directly from theregister file. With register renaing, an entire sequence of operations can be performed speculatively, even though the registers are updated only after the processor is certain of the branch outcomes.

##### 5.7.2 Functional Unit Performance
From figure 5.12 
Each operation is characterized by its latency, meaning the total time required to perform the operation, the issue time, meaning the minimum num- ber of clock cycles between two independent operations of the same type, and the capacity, indicating the number of functional units capable of performing that operation.
![figure5.12](https://upload-images.jianshu.io/upload_images/6543506-9a3597dc493213bc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

concept of data flow (graphical representation of data flow) 有点像工厂的流程图，也有bottleneck
combine4 can classify the register into four categories:
* Read-only %rax in this case
* write-only No such element in this function
* Local %rax (compare)
* Loop %rdx and %xmm0

![image.png](https://upload-images.jianshu.io/upload_images/6543506-6252496261dc48eb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
repeated over and over to generate graph for loop. The critical path is determined by the dependency on the path with highest latency. (In this case, the mul operation)
就跟工厂生产一样，绝大部分瓶颈都在组装……
![image.png](https://upload-images.jianshu.io/upload_images/6543506-2c8425f0a7d77226.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 5.8 Loop Unrolling
Loop unrolling is a program transformation that reduces the number of iterations for a loop by increasing the number of elements computed on each iteration. 
##### 2x1 loop unrolling
The first loop steps through the array two elements at a time. That is, the loop index i is incremented by 2 on each iteration, and the combining operation is applied to array elements i and i + 1 in a single iteration.
#### 5.9 Enhancing parallelism
With multiple functional units, we could further optimize the performance of the loop unrolling.
![figure5.21](https://upload-images.jianshu.io/upload_images/6543506-daea056a396394c1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

with association (2x1a)
![image.png](https://upload-images.jianshu.io/upload_images/6543506-f7e099b6fa0829fc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![image.png](https://upload-images.jianshu.io/upload_images/6543506-c9f764f46b3078c2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

In Example A of Figure 5.33, argument src is a pointer to array element a[0], while dest is a pointer to array element a[1]. In this case, each load by the pointer reference *src will yield the value -10. Hence, after two iterations, the array elements will remain fixed at -10 and -9, respectively. the result of the read from src is not affected by the write to dest. Measuring this example over a larger number of iterations gives a CPE of 1.3.

In Example B of figure 5.33, both arguments src and dest are pointers to array element a[0]. In this case, each load by the pointer reference *src will yield the value stored by the previous execution of the pointer reference *dest. 
As a consequence, a series of ascending values will be stored in this location. In general, if function write_read is called with arguments src and dest pointing to the same memory location, and with argument cnt having some value n > 0, the net effect is to set the location to n-1. This example illustrates a phenomenon we will call a write/read dependency -- the outcome of a memory read depends on a recent memory write. The write/read dependency causes a slowdown in the processing of around 6 clock cycles.

#### 5.13 Performance improvement techniques
* Eliminate excessive function calls
* Eliminate unnecessary memory references
Low-level optimizations
* Unroll loops to reduce overhead and to enable further optimizations.
* Find ways to increase instruction-level parallelism by techniques such as multiple accumulators and reassociation
* Rewrite conditional operations in a functional style to enable compilation via conditional data transfer.

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

## Chapter 8

### Exceptional control flow
From the time you first apply power to a processor until the time you shut if off, the program counter assumes a sequence of values 
where each ak is the address of some corresponding instruction I. each transition from ak to ak+1 is called a control transfer. A sequence of such control trnasfers is called the flow of control, or control flow, of the processor.

The simplest kind of control flow is a "smooth" sequence where each Ik and Ik+1 are adjacent in memory. Typically, abrupt changes to this smooth flow, where Ik+1 is not adjacent to Ik, are caused by familiar program instructions such as jumps, calls, and returns. Such instructions are necessary mechanisms that allow programs to react to changes in internal program state represented by the program variables.

But systems must also be able to react to changes in system state that are not captured by internal program variables and are not necessarily related to the execution of the program. For example, a hardware timer goes off at regular intervals and must be dealt with. Packets arrive at the network adapter and must  be stored in memory. Programs request data from a disk and then sleep until they are notified that the data are ready. Parent processes that create child processes must be notified when their children terminate.
Modern Systems react to these situations by making abrupt changes in the control flow. In general, we refer to these abrupt changes as exceptional control flow (ECF). ECF occurs at all levels of computer system. At the operating system level, the kernel transfers control from one user process to another via context swiches. At the application level, a process can send a signal to another process that abruptly transfers control to a signal handler in the recipient. An individual program can react to errors by sidestepping the usual stack discipline and making nonlocal jumps to arbitrary locations in other functions. 

As programmers, there are a number of reasons why it is important for you to understand ECF:
 * understanding ECF will help you understand important systems concepts. ECF is the basic mechanism that operating systems use to implement I/O, processes and virtual memory. Before you can really understand these important ideas, you need to understand ECF.

* understanding ECF will help you understand how applications interact with the operating system. Applications request services from the operating system by using a form of ECF known as a trap or system call. For example, writing data to a disk, reading data from a network, creating a new process, and terminating the current process are all accomplished by application programs invoking system calls. Understanding the basic system call mechanism will help you understand how these services are provided to applications.
* Understanding ECF will help you write interesting new application programs.
The operating system provides application programs with powerful ECF mechanisms for creating new processes, waiting for processes to terminate, notifying other processes of exceptional events in the system, and detecting and responding to these events. If you understand these ECF mechanisms, then you can use them to write interesting programs such as Unix shells and Web servers.
* understanding ECF will help you understand concurrency. ECF is a basic mechanism for implementing concurrency in computer systems. The following are all examples of concurrency in action: an exception handler that interrupts the execution of an application program; processes and threads whose execution overlap in time; and a signal handler that interrupts the execution of an application program. Understanding ECF is a first step to understanding concurrency. We will return to study it in more detail in Chapter 12. 
* Understanding ECF will help you understand how software exceptions work.
#### 8.1 Exceptions
Exceptions are a form of exceptional control flow that are implemented partly by the hardware and partly by the operating system. Because they are partly implemented in hardware, the details vary from system to system. However, the basic ideas are the same for every system. Our aim in this section is to give you a general understanding of exceptions and exception handling and to help demystify what is often a confusing aspect of modern computer systems.
An exception is an abrupt change in the control flow in response to some change in the processor's state. 
![figure 8.1](https://upload-images.jianshu.io/upload_images/6543506-2017600f7e511779.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

Each type of possible exception in a system is assigned a unique nonnegative integer exception number. Some of these numbers are assigned by the designers of the processor. Other numbers are assigned by the designers of the operating system kernel.
> Kernel is the memory-resident part of the operating system

Examples of former (hardware exception) include divide by zero, page faults, memory access violations, break points, and arithmetic overflows. Examples of latter include system calls and signals from external I/O devices.

At system boot time (the operating system allocates and initializes a jump table called an exception table, so that entry k contains the address of the handler for exception k. 

At run time (when the system is executing some program), the processor detects that an event has occurred and determines the corresponding exception number k. The processor then triggers the exception by making an indirect procedure call, through entry k of the exception table, to the corresponding handler. 

#### 8.1.2 Classes of exceptions
Exceptions can be divided into four classes: interrupts, traps, faults, and aborts. The table in Figure 8.4 summarizes the attributes of these classes. 
##### Interrupts 
Interrupts occur asynchronously as a result of signals from I/O devices that are external to the processor. Hardware interrupts are asynchronous in the sense that they are not caused by the execution of any particular instruction. Exception handlers for hardware interrupts are often called interrupt handlers.

就比如你要终止一个infinite loop，ctrl+c 就是asynchronously interrupts from I/O

Figure 8.5 summarizes the procesing for an interrupt. I/O devices such as network adapters, disk controllers, and timer chips trigger interrupts by signaling a pin on the processor chip and placing onto the system bus the exception number that identifies the device that caused the interrupt.
![Figure8.5](https://upload-images.jianshu.io/upload_images/6543506-d90224a179a5c9ee.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
机械设备中也有hardware interrupt。就比如solenoid valve
![solenoid valve](https://upload-images.jianshu.io/upload_images/6543506-878d67cb0371463a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### Traps and System calls
Traps are intentional exceptions that occur as a result of executing an instruction. The most important use of traps is to provide a procedure-like interface between user programs and the kernel, known as a system call.

User programs often need to request services from the kernel such as reading a file, creating a new process(fork), loading a new program(execve), and terminating the current process(exit). To allow controlled access to such kernel services, processors provide a special syscall n instruction that user programs can execute when they want to request service n. Executing the syscall instruction causes a trap to an exception handler that decodes the argument and calls the appropriate kernel routine. Figure 8.6 summarize the processing for a system call.

From a programmer's perspective, a system call is identical to a regular function call. However, their implementations are quite different. Regular functions run in user mode, which restricts the types of instructions they can execute, and they access the same stack as the calling function. A system call runs in kernel mode, which allows it to execute privileged instructions and access a stack defined in the kernel. Section 8.2.4 discusses user and kernel modes in more detail.

![figure8.10](https://upload-images.jianshu.io/upload_images/6543506-0dd5145a4303285d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

> Exceptions are the basic building blocks that allow the operating system kernel to provide the notion of a process
> 一个程序是在process的context中运行的（也可以理解为program 在progress中运行）
> The classic definition of a process is an instance of a program in execution. Each program in the system runs in the *context* of some process. The context consists of the state that the program needs to run correctly. This state includes the program's code and data stored in memory, its stack, the contents of its general purpose registers, its program counter, environment variables, and the set of open file descriptors.

主要关注下面两个abstraction
> Each time a user runs a program by typing the name of an executable object file to the shell, the shell creates a new process and then runs the executable object file in the context of this new process. 

> key abstractions that a process provides to the application:
> * An independent logical control flow that provides the illusion that our pro- gram has exclusive use of the processor. 
> * A private address space that provides 

figure 8.10 lists some popular Linux system calls. Each system call has a unique integer number that corresponds to an offset in a jump table in the kernel. 


![figure8.12](https://upload-images.jianshu.io/upload_images/6543506-04f645d05e0e82f1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
The key point in Figure 8.12 is that processes take turns using the processor. Each process executes a portion of its flow and then is preempted (temporarily suspended) while other processes take their turns. To a program running in the context of one of these processes, it appears to have exclusive use of the processor. 
> A logical flow whose execution overlaps in time with another flow is called a concurrent flow

Concurrent flow is independent of the number of processor cores. If two flow overlap in time, they are concurrent. If two flows are running concurrently on different processor cores or computers, then we say that they are parallel flows. Parallel flow is a subset of concurrent flow.

#### 8.2.3 Private address space
The bottom portion of the address space is reserved for the user program, with the usual code, data, heap, and stack segments. The code segment always begins at address 0x400000. The top portion of the address space is reserved for the kernel.  
![figure 8.13](https://upload-images.jianshu.io/upload_images/6543506-b03ef395c0a7348f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
#### 8.2.5 Context switches
> The kernel maintains a context for each process. The context is the state that the kernel needs to restart a preempted process.

context switch cost?

#### 8.3 System call error handling

这里应该是写shell的时候需要注意的地方
when Unix system-level functions encounter an error, they typically return -1 and set the global integer variable **[errno](https://man7.org/linux/man-pages/man3/errno.3.html)** to indicate what went wrong. Programmers should *always* check for errors, but unfortunately, many skip error checking because it bloats the code and makes it harder to read. For example, 
```C
if ((pid = fork() < 0 ) {
  fprintf(stderr, "fork error: %s\n", strerror(errno));
  exit(0);
}
```
The strerror function returns a text string that describes the error associated with a prticular value of errno. 


#### 8.4 Process control
Unix provides a number of system calls for manipulating processes from C programs. This section describes the important functions and gives examples of how they are used.
##### 8.4.41 Obtaining process IDs
Each process has a unique positive process ID (PID) 这让我想起了PID controller. The **getpid** function returns the PID of the calling process. The ```getppid``` function returns the PID of its parent (i.e the process that created the calling process)
```c
#include <sys/types.h>
#include <unistd.h>
pid_t getpid(void);
pid_t getppid(void);
```
The ```getpid``` and ```getppid``` routines return an integer value of type pid_t, which on Linux systems is defined in types.h as an int.
##### 8.4.2
From a programmer's perspective, we can think of a process as being in one of three states:
Running The process is either excuting on the CPu or waiting to be executed and will eventually be scheduled by the kernel.
Stopped. The execution of the process is suspended and will not be scheduled. 
Terminated. the process is stopped permanently. A process becomes terminated for one of three reasons
1. receiving signal whose default action is to terminate the process.
2. returning from the main routine
3. calling the exit function

```c
#include <stdlib.h>
void exit(int status);
```
 The exit function terminates the process with an exit status. 
A parent process creates a new runnning child process by calling the fork function. 

Fork本身就是最基本的concurrent programming了吧。

```c
#include <sys/types.h>
#include <unistd.h>
pid_t fork(void);
// return 0 to child, PID of child to parent, -1 on error
```
The child gets an identical copy of the parent user-level virtual address space, including the code and data segments, heap shared libraries, and user stack. The child also gets identical copies of any of the parent's open file descriptors, which means the child can read and write any files that were open in the parent when it called fork. The most significant difference between the parent and the newly created child is that they have different PIDs.
*Duplicate but separate address.* Since parent and the child are separate processes, they each have their own private address spaces.
When first learning about the fork function, it is often helpful to sketch the process graph, which is a simple kind of precedence graph that captures the [partial ordering](https://mathworld.wolfram.com/PartiallyOrderedSet.html) (离散数学里的一个概念) of program statements.
![image.png](https://upload-images.jianshu.io/upload_images/6543506-ae7d0e99ca62274c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

[Hasse diagram](https://mathworld.wolfram.com/HasseDiagram.html#:~:text=A%20Hasse%20diagram%20is%20a,1.) might also be helpful

![figure8.17](https://upload-images.jianshu.io/upload_images/6543506-86265c05f857ad3c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### topological sort 
topological sort can be used to show the process generated by fork(). Because parent has no entry and since it will be the starting point. Child process will have entries and it can be sorted based on how many entries each child has. 

#### 8.4.3 Reaping Child Processes
Kernel does not remove process from the system immediately after it terminates. Instead, the process is kept around in a terminated state until it is *reaped* by its parent. A terminated process that has not yet been reaped is called a zombie.
kernel arranges init process to become parent of any orphaned children, which has PID of 1. If parent process terminates without reaping its zombie children, then the kernel arranges for the init process to reap them.

A process waits for its children to terminate or stop by calling the waitpid function. 
```c
#include <sys/types.h>
#include <sys/wait.h>
pid_t waitpid(pid_t pid, int *statusp, int options); /* returns pid of child if ok, 0 if (WNOHANG), -1 on error)
```

##### Modifying the default behavior
The default behavior can be modified by setting options to various combinations of the WNOHANG, WUNTRACED, and WCONTINUED 
WNOHANG. Return immediately (with a return value of 0) if none of the child processes in the wait set has terminated yet. The default behavior suspends the calling process until a child terminates; this option is useful in those cases where you want to continue doing useful work while waiting for a child to terminate.
要做其他有用的事情的时候用这个
WUNTRACED. Suspend excution of the calling process until a process in the wait set becomes either terminated or stopped. Return the PID of the terminated or stopped child that cuased the return.  
用来检查stopped or terminated process 
WCONTINUED suspend execution of the calling process until a running process in the wait set is terminated or until a stopped process in the wait set has been resumed by the receipt of a SIGCONT signal.  
> WNOHANG | WUNTRACED: Return immediately, with a return value of 0, if none of the children in the wait set has stopped or terminated, or with a return value equal to the PID of one of the stopped or terminated children.

union of two set.

go over code in book

##### 8.4.5 Loading and Running programs
The ```execve``` function loads and runs a new program in the context of the current process.
```c
#include <unistd.h>
int execve(const char *filename, const char *argv[], const char *envp[]);
// Does not return if OK; return -1 on error
```
The execve function loads and runs the executable object file ```filename``` with the argument list ```argv``` and the environment variable list ```envp```. ```execve``` returns to the calling program only if there is an error, such as not being able to find ```filename```.
The argument list is represented by the data structure shown in figure 8.20. The ```argv``` variable points to a null-terminated array of **pointers**, each of which points to an argument string. By convention, ```argv[0]``` is the name of the executable object file. 

The ```envp``` variable points to a null-terminated array of pointers to environment variable strings, each of which is a name-value pair of the form ```name=value```
![8.20 && 8.21](https://upload-images.jianshu.io/upload_images/6543506-2a6f23f84b634592.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
The start-up code sets up the stack and passes control to the main routine of the new program, which has a prototype of the form
```c
int main(int argc, char **argv, char **envp);
```
or equivalently,
```c
int main(int argc, char *argv[], char *envp[]);
```
这个比较太有帮助了……因为之前一直没法理解pointer of a pointer 到底是什么，看完这段至少有了一个直观理解。


##### lowbit 的应用
![29:32](https://upload-images.jianshu.io/upload_images/6543506-e79e5bf47c48be64.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
这一段终于了解求最后一位1有什么用了，原来在signal里面有用到……

### pointer of a pointer
pointer of a pointer 在这一章中也有解释。
> int main(int argc, char **argv, char **envp);
> or equivalently,
> int main(int argc, char *argv[], char *envp[]);
> 也就是说每一个pointer都指向了一个array？

### shell
programs such as Unix shells and Web servers make heavy use of the fork and execve functions. A shell is an interactive application-level program that runs other programs on behalf of the user. The original shell was the sh program, which was followed by variants such as csh, tcsh, ksh and bash. A shell performs a sequence of read/evaluate steps and then terminates. the read step reads a command line from the user. The evaluate step parses 

### Signals
To this point in our study of exceptional control flow, we have seen how hardware and software cooperate to provide the fundamental low-level exception mechanism. We have also seen how the operating system uses exceptions to support a form of exceptional control flow known as the process context switch. In this section, we will study a higher-level software form of exceptional control flow known as the process context switch. In this section , we will study a higher-level software form of exceptional control flow, known as a Linux signal, that allows processes and the kernel to interrupy other processes.
![figure 8.26](https://upload-images.jianshu.io/upload_images/6543506-a7fe09ad01f82740.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

A signal is a small message that notifies a process that an event of some type has occurred in the system.
Each signal type corresponds to some kind of system event. Low-level hardware exceptions are processed by the kernel's exception handlers and would not normally be visible to user processes. Signals provide a mechanisms for exposing the occurrence of such exceptions to user processes. For example, if a process at tempts to divide by zero, then the kernel sends it a SIGFPE signal. 
if a process makes an illegal memory reference, the kernel sends it a events in the kernel or in other user processes. For example, if you type Ctrl+C while a process is running in the foreground, then the kernel sends a SIGINT to each process in the foreground process group. A process can forcibly terminate another process by sending it a SIGKILL signal. When a child process terminates or stops, the kernel sends a SIGCHLD signal to the parent.

&

#### Process group
Unix systems provide a number of mechanisms for sending signals to processes. All of the mechanisms rely on the notion of a *process group*.
Every process belongs to exactly one process group, which is identified by a process group ID (pid). The **getpgrp** function returns the process group ID of the current process.
```c
#include <unistd.h>
pid_t getpgrp(void); /* returns: process group ID of calling process */
```
A process can change the process group of itself or another process by using the setpgid function:
```c
int setpgid(pid_t pid, pid_t pgid);  /* returns 0 on success, -1 on error */
```
the setpgid function changes the process group of process pid to pgid. if pid is zero, the pid of the current process is used. if pigid is zero, the pid of the process specified by pid is used for the process group ID. 

The /bin/kill program sends an arbitrary signal to another process. For example, the command 
```
/bin/kill/ -9 15213
```
sends signal 9 (sigkill) to process 15213. A negative PID causes the signal to be sent to every process in process group PID. For example, the command 
```
/bin/kill/ -9 15213
```
sends signal to every process in group 15213

####fg and bg
Unix shells use abstraction of a job to represent the processes that are created as a result of evaluating a single command line. There is at most one foreground job and zero or more background jobs. For example, typing
```ls | sort```
creates a foreground job consisting of two processes connected by a Unix pipe: one running the ls program, the other running the sort program. The shell creates a separate process group for each job. Typically, the process group ID is taken from one of the parent processes in the job. 
![Figure 8.28](https://upload-images.jianshu.io/upload_images/6543506-5eddfdfa10629625.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

这张图很有用，shell本身就是一个program，有自己的pid，然后foreground job跟background job都有自己的PID 和pgid

#### sending signals with the kill function
Processes send signals to other processes (including themselves) by calling the kill function. 
```
int kill(pid_t pid, int sig);  /*returns 0 if ok, -1 on error */
```
If pid is greater than zero, then the kill function sends signal number sig to process pid. if **pid** is equal to zero, then **kill** sends signal sig to every process in the process group of the calling process, including the calling process itself. If pid is less than zero, then **kill** sends signal sig to every process in process group |pid|. 
```c
#include "csapp.h"
int main() {
  pid_t pid;
  /* Child sleeps until SIGKILL signal received, then dies */
if ((pid = Fork()) == 0) {
  Pause();
  printf("control should never reach here!\n";
exit(0);
}

/* Parent sends a SIGKILL signal to a child */
Kill(pid, SIGKILL);
exit(0);
}
```
#### 8.5.3 Receiving Signals
When the kernel switches a process p from kernel mode to user mode (e.g., returning from a system call or completing a context switch), it checks the set of unblocked pending signals (pending & ~blocked) for p. if this set is empty(the usual case), then the kernel passes control to the next instruction (Inext) in the logical control flow of p. However, if the set is nonempty, then the kernel chooses some signal k in the set (usually smallest)
and forces p to receive signal k. The receipt of the signal triggers some action by the process. Once the process completes the action, then control passes back to the next instruction in the logical control flow of p.
[figure8.1](#8.1-Exceptions)
Each signal type has a predefined default action, which is one of the following: 
- The process terminates.
- The process terminates and dumps core.
- The process stops (suspends) until restarted by a SIGCOUNT signal.
- The process ignores the signal.

A process can modify the default action associated with a signal by using the **signal** function. The only exceptions are SIGTOP and SIGKILL, whose default actions cannot be changed.
 ```c
#include <signal.h>
/* Returns: pointer to previous handler if OK, SIG_ERR on error (does not set errno) */
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
 ```
The signal function can change the action associated with a signal signum in one of three ways: 
1. If handler is SIG_IGN,  then signals of type signum are ignored.
2. If handler is SIG_DFL, then the action for signals of type signum reverts to the default action.

Otherwise, handler is the address of a user-defined function, called a signal handler, that will be called whenever the process receives a signal of type signum. Changing the default action by passing the address of a handler to the signal function is known as installing the handler. The invocation of the handler is called catching the signal. The execution of the handler is referred to as handling the signal. 
自定义handler: (wrapper function of signal)
```c
1 handler_t *Signal(int signum, handler_t *handler) 2{
3 struct sigaction action, old_action;
4
5 action.sa_handler = handler;
6 sigemptyset(&action.sa_mask); /* Block sigs of type being handled */
7 action.sa_flags = SA_RESTART; /* Restart syscalls if possible */
8
9 if (sigaction(signum, &action, &old_action) < 0)
10 unix_error("Signal error");
11 return (old_action.sa_handler);
12 }
```

more info on [sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html).
When a process catches a signal of type k, the handler installed for signal k is invoked with a single integer argument set to k. This argument allows the same handler function to catch different types of signals.
When the handler executes its return statement, control (usually) passes back to the instruction in the control flow where the process was interrupted by the receipt of the signal. 

#### 8.5.4 Blocking and unblocking signals 
Linux provides implicit and explicit mechanisms for blocking signals:
Implicit blocking mechanism. by default, the kernel blocks any pending signals of the type currently being processed by a handler. For example, in figure 8.31, suppose the program has caught signal s and is currently running handler S. If another signal s is sent to the process, then s will become pending but will not be received until after handler S returns.
Explicit blocking mechanisms. Applications can explicitly block and unblock selected signals using the sigprocmask function and tis helpers.
```c
#include <signal.h>
/* Returns: 0 if OK, −1 on error */
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
/* Returns: 1 if member, 0 if not, −1 on error */
int sigismember(const sigset_t *set, int signum);
```
The sigprocmask function changes the set of currently blocked signals. The specific behavior depends on the value of **how**:
SIG_BLOCK. Add the signals in set to blocked (blocked = blocked | set)

SIG_UNBLOCK. Remove the signals in set from blocked (blocked = blocked & ~set)
sig_setmask blocked = set.

从集合的角度看这种操作就清晰很多了

if oldset is non-NULL, the previous value of the blocked bit vector is stored in oldset.

Signal sets such as set are manipulated using the following functions: The sigemptyset initializes set to the empty set. The sigfillset function adds every signal to set. The sigaddset function 

Signals can interrupt each other if not handled correctly

#### Safe signal handling
Signal handlers are tricky because they can run concurrently with main program and with each other. If a handler and the main program access the same global data structure concurrently, then the results can be unpredictable and often fatal.

#### Correct signal handling
One of the nonintuitive aspects of signals is that pending signals are not queued. Because the pending bit vector contains exactly one bit for each type of signal, there can be at most one pending signal of any particular type. Thus, if two signals of type k are sent to a destination process while signal k is blocked because the destiination process is currently executing a handler for signal k, then the second signal is simply discarded; it is not queued. The key idea is that the existence of a pending merely indicates that at least one signal has arrived.

G0 keep it simple
G1 call only async-signal-safe functions
G2 Save and restore errno.
G3 Protect accesses to shared global data structures by blocking all signals
G4 Declare global variables with volatile.
G5 Declare flags with sig_atomic_t. 
buggy example
![figure 8.36](https://upload-images.jianshu.io/upload_images/6543506-88f14d664efe7018.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
> The key idea is that the existence of a pending signal merely indicates that at least one signal has arrived.

#### 8.5.6
> 1. The parent executes the fork function and the kernel schedules the newly created child to run instead of the parent.
> 2. Before the parent is able to run again, the child terminates and becomes a zombie, causing the kernel to deliver a SIGCHLD signal to the parent.
> 3. Later, when the parent becomes runnable again but before it is executed, the kernel notices the pending SIGCHLD and causes it to be received by running the signal handler in the parent.
> 4. The signal handler reaps the terminated child and calls deletejob, which does nothing because the parent has not added the child to the list yet.
> 5. After the handler completes, the kernel then runs the parent, which returns from fork and incorrectly adds the (nonexistent) child to the job list by calling addjob.

figure 8.17 may help to visualize

#### 8.5.7 Explicitly waiting for signals
Sometimes a main program needs to explicitly wait for a certain signal handler to run. For example, when a Linux shell creates a foreground job, it must wait for the job to terminate and be reaped by the SIGCHLD handler before accepting the next user command.
Use pause will cause race condition. Use sleep will have a huge cost

Proper solution is to use sigsuspend
```c
#include <signal.h>
int sigsuspend(const sigset_t *mask);  /* returns -1 */
```
> The sigsuspend version is less wasteful than the original spin loop, avoids the race introduced by pause, and is more efficient than sleep.

如果需要wait for child process to complete, use sigsuspend
### 8.6 Nonlocal Jumps
```c
/* Returns: 0 from setjmp, nonzero from longjmps */
#include <setjmp.h>
int setjmp(jmp_buf env);
int sigsetjmp(sigjmp_buf env, int savesigs);
```
The setjmp function saves the current calling environment in the env buffer, for later use by longjmp, and return 0. The calling environment includes the program counter, stack pointer, and general-purpose registers. 
setjmp should not be assigned to a variable
```c
#include <setjmp.h>
/* never returns */
void longjmp(jmp_buf env, int retval);
void siglongjmp(sigjmp_buf env, int retval);
```
The longjmp function restores the calling environment from the env buffer and then triggers a return from the most recent setjmp call that initialized env. 
![figure 8.43](https://upload-images.jianshu.io/upload_images/6543506-11ceae73e1aff64f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

> An important application of nonlocal jumps is to permit an immediate return from a deeply nested function call, usually as a result of detecting some error condition.

The feature of longjmp that allows it to skip up through all intermediate calls can have unintended consequences.

##### c++ and java
> The exception mechanisms provided by C++ and Java are higher-level, more structured versions of the C setjmp and longjmp functions. You can think of a catch clause inside a try statement as being akin to a setjmp function. Similarly, a throw statement is similar to a longjmp function.

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



## Concurrency programming

notes from https://github.com/angrave/SystemProgramming/wiki/Pthreads%2C-Part-1%3A-Introduction

To use pthreads you will need to include ```pthread.h``` AND you need to compile with ```-pthread``` compiler option. This option tells the compiler that your program requires threading support

To create a thread use the function ```pthread_create```. This function takes four argumens:

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
                   void *(*start_routine) (void *), void *arg);
```

* The first is a pointer to variable that will hold the id of the newly created thread.
* The second is a pointer to attributes that we can use to tweak and tune some of the advanced feature of pthreads.
* The third is a pointer to a function that we want to run
* Fourth is a pointer that will be given to our function

The argument ```void *(*start_routine) (void *)``` is difficult to read. It means a pointer that takes a ```void*``` pointer and returns a ```void *``` pointer. It looks like a function declaration except that the name of the function is wrapped with ```(* ...)```

Here's the simplest example:

```c
#include <stdio.h>
#include <pthread.h>

void *busy(void *ptr) {
  //ptr will point to "Hi"
  puts("Hello World");
  return NULL;
}

int main() {
  pthread_t id;
  pthread_create(&id, NULL, busy, "Hi");
  while (1) {} //Loop forever
}
```



If we want to wait for our thread to finish use ```pthread_join```

```c
void *result;
pthread_join(id, &result);
```

In the above example, ```result``` will be ```null``` because the busy function returned ```null```. We need to pass the address of result because ```pthread_join``` will be writing into the contents of our pointer.

#### Part 2

If I call ```pthread_create``` twice, how many stacks does my process have? 

Your process will contain three stacks - one for each thread. Each thread requires a stack because the stack contains automatic variables and the old CPU PC register, so that it can back to executing the calling function after the function is finished. (Makes sense! 因为你要在这个thread结束后回到call它的function，所以有一个单独stack并且contains automatic variables and PC register 就很合理了，因为PC要回到之前的function address)

#### What is the difference between a full process and a thread?

In addition, unlike processes, threads within the smae process can share same global memory (data and heap segments)

### ```exit``` and ```pthread_exit```

```exit``` exit the entire process and sets the processes exit value. All threads inside the process are stopped.

```pthread_exit(void *)``` only stops the calling thread i.e. the thread never returns after calling ```pthread_exit```. The pthread library will automatically finish the process if there are no other threads running. ```pthread_exit(...) is equivalent to returning from the thread's function; both finish the thread and also set the return value (void *pointer) for the thread.

Calling ```pthread_exit``` in the main thread is a common way for simple programs to ensure that all threads finish. For example, in the following program, the ```myfunc``` threads will probably not have time to get started.

```c 
int main() {
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, myfunc, "Jabbberwocky");
  pthread_create(&tid2, NULL, myfunc, "Vorpel");
  exit(42);
  
}
```

The next two programs will wait for the new threads to finish

```c 
int main() {
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, myfunc, "Jabberwocky");
  pthread_create(&tid2, NULL, myfunc, "Vorpel");
  pthread_exit(NULL);
}
```

Alternatively, we join on each thread (i.e. wait for it to finish) before we return from main (or call exit).

```c
int main() {
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, myfunc, "Jabberwocky");
  pthread_create(&tid2, NULL, myfunc, "Vorpel");
  void* result;
  pthread_join(tid1, &result);
  pthread_join(tid2, &result);
  return 42;
}
```

Note that pthread_exit version creates **thread zombies**, however this is not a long-running processes, so we don't care.

### How can a thread be terminated?

* Returning from te thread function
* Calling ```pthread_exit```
* Cancelling the thread with ```pthread_cancel```
* Terminating the process (e.g. SIGTERM); exit(); returning from ```main```

#### What is the purpose of pthread_join?

* wait for a thread to finish
* Clean up thread resources
* Grabs the return value of the thread

#### What happens if you don't call ```pthread_join```?

Finished thread will continue to consume resources. Eventually, if enough threads are created, ```pthread_create``` will fail. In practice, this is only an issue for long-running processes but is not an issue for simple, short-lived processes as all thread resources are automatically freed when the process exits.

#### Should I use ```pthread_exit``` or ```pthread_join```?

Both ```pthread_exit``` and ```pthread_join``` will let the other threads finish on their own. However, only ```pthread_join``` will return to you when the specified thread finishes. ```pthread_exit``` does not wait and will immediately end your thread and give you no chance to continue executing.

To overcome race-condition, we will give each thread a pointer to it's own data area. for example, for each thread we may want to store the id, a starting value and an output value:

```c
struct T {
  pthread_t id;
  int start;
  char result[100];
};
```

 These can be stored in an array -

```c
struct T *info = calloc(10, sizeof(struct T)); // reserve enough bytes for ten T structures
```

And each array element passed to each thread -

```c
pthread_create(&info[i].id, NULL, func, &info[i]);
```

#### What are condition variables, semaphores, mutexes?

These are synchronization locks that are used to prevent race conditions and ensure proper synchronization between threads running in the same program. In addition, these locks are conceptually identical to the primitives used inside the kernel.

#### sem

The POSIX thread library contains functions for working with semaphores and mutexes. 

A semaphore is fundamentally an integer whose value is never allowed to fall below 0. There are two operations on a semaphore: wait and post. The post operation increment the semaphore by 1, and the wait operations does the following: If the semaphore has a value > 0, the semaphore is decremented by 1

If the semaphore has value 0, the caller will be blocked (busy-waiting or more likely on a queue) until the semaphore has a value larger than 0, and then it is decremented by 1.

we declare a semaphore as:

```sem_t sem;```

where sem_t is a typedef defined in a header file as (apparently) a kind of unsigned char

An example of this might be that we have a set of N interchangeable resources. We start with semaphore S = N. We use a resource, so there are now N-1 available (wait), and we return it when we are done (post). If the semaphore has value 0, there are no resources available, and we have to wait (until someone does a post).

Semaphores are thus used to coordinate concurrent processes.

##### int sem_init(*sem_t * sem, int pshared, unsigned int value);

* purpose: this initilizes the semaphore *sem. The initial value of semaphore will be value. If pshared is 0, the semaphore is **shared** among all threads of a process (and hence need to be visible to all of them such as a global variable). 

##### sem_wait()

int sem_wait(sem_t * sem);

purpose: this implements the wait function described above on the semaphore *sem

##### sem_post()

Prototype: int sem_post(sem_t *sem);

purpose: this implements the post function described above on the semaphore *sem

pthread_mutex_destroy()

int pthread_mutex_destroy(pthread_mutex_t * restrict mutex);

purpose: 



