## Linking
Linking is the process of collecting and combining various pieces of code and data into a single file that can be loaded (copied) into memory and executed. Linking can be performed at compile time.
On modern systems, linking is performed automatically by programs called linkers.

Linkers play a crucial role in software development because they enable separate compilation. Instead of organizing a large application as one monolithic source file, we can decompose it into smaller, 
more manageble module that can be modified and compiled separately. Whenwe change oneof these modules, we simply recompile it and relink the application, without having to recompile the other files.

Why bother learning about linking? 
* Understanding linkers will help you build large programs. 
* Understanding linkers will help you avoid dangerous programming errors.
* Understanding linking will help you understand how language scoping rules are implemented. 
* Understanding linking will help you understand other important systems concepts.
* Understanding linking will enable you to exploit shared libraries.


### 7.2 Static Linking
Static linkers such as the Linux LD program take as input a collection of relocatable object files and command-line arguments and generate as output a fully linked executable object file that can be loaded and run. 

The input relocatable object file consist of various code and data sections, where each section is a contiguous sequence of bytes. Instructions are in one section, initialized global variables are in another section, and uninitialized variables are in yet another section.

the linker must perform 2 main tasks to build executable
1. Symbol resolution. 
2. Relocation. 

Keep in mind: **Object files are merely collections of blocks of bytes.**
Some of these blocks contain program code, others contain program data, and others contain data structures that guide the linker and loader. 
A linker concatenates blocks together, decides on run-time locations for the concatenated blocks, and modifies various locations
within the code and data blocks. Linkers have minimal understanding of the target machine. The compilers and assemblers
that generate the object files have already done most of the work.

### 7.3 Object files
Object files come in three forms:
1. Relocatable object file.
2. Executable object file.
3. Shared object file.

Compilers and assemblers generate relocatable object files (including shared object files).
Linkers generate executable object files. Technically, an object module is a sequence of bytes, and 
an *object file* is an object module stored on disk in a file. However, CSAPP will use them interchangeably.


