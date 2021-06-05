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
3. Shared object file. (Libraries) 

Compilers and assemblers generate relocatable object files (including shared object files).
Linkers generate executable object files. **So linkers make executable files**

Technically, an object module is a sequence of bytes, and 
an *object file* is an object module stored on disk in a file. However, CSAPP will use them interchangeably.

### 7.4 Relocatable Object Files

ELF (executable and linkable format) header begins with a 16-byte sequence that describes the word size and byte ordering of the system that generated the file. (big endian and little endian?) The rest of the ELF header contains information that allows a linker to parse and interpret the object file. this includes the size of the ELF header, the obj file type (e.g., relocatable, executable, or shared), the machine type, the file offset of the section header table,

the size and number of entries in the section header table.

there is a lot of information on header!

Sandwiched between the ELF header and the section header table are the sections themselves. A typical ELF relocatable object file contains the following sections

* .text the machine code
* .rodata read only data
* .data Initialized global and static C variables.
* .bss Uninitialized global and static C variables. this section occupies no actual space in the obj file; its merely a placeholder
* .symtab A symbol table with information about functions and global variables that are defined and referenced in the   program
* .rel.text A list of locations in the .text section that will need to be modified when the linker combines this object file with others. 
* .rel.data Relocation information for any global variables that are referenced or defined by the module.
* .debug A debugging symbol table with entries for local variables and typedefs defined in the program. Only present if the compiler driver is invoked with the -g option.

* .line A mapping between line numbers in the original C source program and machine code instructions in the .text section. Only present if the compiler invoked with -g option
* .strtab A string table for the symbol tables in the .symtab and .debug sections and for the section names in the section headers. 

### 7.5 Symbols and Symbol Tables

Each relocatable obj module, m, has a symbol table that contains information about the symbols that are defined and referenced by m. There are three different kinds of symbols:

* Global symbols defined by m that can be referenced by other modules (nonstatic C functions and global variables)
* Global symbols referenced by m but defined by some other module. Such symbols are called externals and correspond to nonstatic C functions and global variables that are defined in other modules.
* Local symbols defined and referenced exclusively by m. static C functions and static global variables. These symbols are visible anywhere in m but cannot be referenced by other modules.

### 7.6 Symbol Resolution

Local variables have unique names in linker. Global symbols in current module will be assumed defined in some other module. So it generate a linker symbol table entry, and leaves it for the linker to handle. 
![image.png](https://upload-images.jianshu.io/upload_images/6543506-8dd030af0d499530.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![image.png](https://upload-images.jianshu.io/upload_images/6543506-67a174e7427f81b4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

If multiple modules define global symbols with the same name. Linux compilation system will exports each global symbol to the assembler as either strong or weak

Functions and initialized global variable get strong symbols. Uninitialized global variables get weak symbols.

Linux Linkers use 3 rules dealing with duplicate symbol names:

1. Multiple strong symbol with the same name are not allowed.
2. Given strong and weak symbols with the same name, choose the strong symbol
3. Given multiple weak symbols with the same name, choose any of the weak symbols.

