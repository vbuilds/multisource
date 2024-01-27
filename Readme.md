Multiple source files in C:

This Gist presents an introduction to a few different ways of working with multiple source files in C, including:

Simple .c source files and .h header files compiled into a .exe
First compiling into .o object files, and then linking together
Makefiles
Statically linked libraries
Dynamically linked libraries
The concepts are demonstrated using gcc (tdm64-1) 5.1.0 on Windows 8.1, using 3 C source files (linkedlist.c, listprimes.c and main.c) and 2 header files (linkedlist.h and listprimes.h), all of which are included at the end. It is assumed that all the source files are saved in a single directory, and any terminal commands are entered in a terminal window open in that same directory.

Note that the header files contain function declerations (which describe the input types, output type, and name of the function), whereas the source files contain the function definitions. In this case, the linkedlist.h header also includes a struct definition.

Source files and header files:

To compile the C program, enter the following command in the terminal:

gcc main.c listprimes.c linkedlist.c -o list-primes

This command compiles the 3 source files main.c listprimes.c linkedlist.c and outputs a single executable list-primes.exe which can be run in terminal. The order of the 3 source files (which are used as arguments for the compiler) does not matter, as long as there is a single valid main function in one of the 3 files. To compile the program and run the program upon successful compilation, use:

gcc main.c listprimes.c linkedlist.c -o list-primes && list-primes
Optionally, the header files can be placed in a subdirectory. For example, if the header files are placed in a subdirectory called "includes", then the gcc command must be updated with the -I flag as follows:

gcc main.c listprimes.c linkedlist.c -I ./includes -o list-primes && list-primes
The -I flag adds the subdirectory ./includes (which can be specified as a relative or absolute path) to the search path of standard headers. This means that the #include preprocessor directives can optionally be specified with angle brackets instead of quotations (for example #include <linkedlist.h> instead of #include "linkedlist.h"); if the -I flag is used, either will work.

Object files:

Using the command gcc main.c listprimes.c linkedlist.c -o list-primes will recompile every source file every time, even if a change is just being made to one source file. If a program uses many source files and some of them are very large, then this can be very slow; this is because every time the compiler is being run, it is recompiling every source file, even the source files which have not been changed since the last compile.

One way to resolve this issue is to use object files, which contain object code. Under the hood, every time the compiler is being run, it first creates object code for each source file, and then it links all the object code together into a single executable file. The -c flag can be used to tell the compiler to just create an object file, but not to link anything together into an executable. That way, if just one source file is modified, it is only necessary to regenerate the object file for that one source file and then to link together all the object files into the executable, instead of generating object code for all of the source files and linking it all together, which can save a lot of time.

The program can be compiled into object files and then linked together into an executable using the following commands (note that the compiler will automatically give the object file the same name as the source file, except with the .c suffix replaced with .o):

gcc -c main.c -I ./includes
gcc -c listprimes.c -I ./includes
gcc -c linkedlist.c -I ./includes
gcc main.o listprimes.o linkedlist.o -o list-primes
Now, if a change is made to one source file, it is only necessary to recompile the object code for that one source file, and then to run the single linking command at the end.

Makefiles:

Makefiles provide a way of automating the build process of programs with multiple source files; instead of manually telling the compiler to recompile the object code for each source file that has been updated since the last build, and then telling the compiler to link everything together into the executable file, a makefile can be used to automatically decide which object files to recompile by comparing the time-stamp of those object files with the source files which generate them.

A makefile consists of one or more rules, and each rule consists of a target, one or more dependencies, and a command. Each rule starts off with the target, then a colon and a space, then the list of dependencies, seperated by spaces, then a new line, then a tab character (it must be a tab character and not just several spaces, otherwise the makefile won't work), then the command. Each new rule must start on a new line. Below is an example of a rule:

linkedlist.o: linkedlist.c includes/linkedlist.h
	gcc -I ./includes -c linkedlist.c -o linkedlist.o
When this rule is encountered, the timestamp of each dependency (linkedlist.c and includes/linkedlist.h) will be compared to the timestamp of the target (linkedlist.o). If any of the dependencies is more recent than the target, then the command will be sent to the terminal.

The general syntax for a rule is as follows:

target: dependency_1 dependency_2 dependency_3 ...
	command
The full makefile for the program considered in this Gist is shown below:

list-primes.exe: main.o listprimes.o linkedlist.o
	gcc main.o listprimes.o linkedlist.o -o list-primes
	
linkedlist.o: linkedlist.c includes/linkedlist.h
	gcc -I ./includes -c linkedlist.c -o linkedlist.o

listprimes.o: listprimes.c includes/linkedlist.h includes/listprimes.h
	gcc -I ./includes -c listprimes.c -o listprimes.o

main.o: main.c includes/linkedlist.h includes/listprimes.h
	gcc -I ./includes -c main.c -o main.o
In order to run this makefile, save it in a file called makefile in the same directory as the .c source files, and run the command mingw32-make in terminal (mingw32-make is the name of the tool on Windows/MinGW; on Linux, the tool is just called make). The tool will run all necessary commands to build an up-to-date version of the first target in the makefile (and all its dependencies). Optionally, the tool can be run with an argument which specifies a target to be made; if no target is specified, then the first target in the makefile is made (along with any other dependencies in the makefile).

Now, for example, after running the command mingw32-make, if a change is made only to main.c and mingw32-make is run again, the tool will automatically only rebuild the files main.o and list-primes.exe (instead of just rebuilding everything).

Statically linked libraries:

If a project requires many different object files, which might also be shared with many other projects, then it can be convenient to combine all of those object files into a library. The archive tool can be used to create an archive file (in this case called libprimes.a) which contains multiple object files as follows:

ar -r libprimes.a main.o listprimes.o linkedlist.o
The general syntax for creating an archive file for a library called name is as follows:

ar -r libname.a objectfile1.o objectfile2.o objectfile3.o ...
Now, when compiling the main program, instead of passing a list of object files to the compiler, it is sufficient to simply pass to the compiler the archive file which contains those object files, as follows:

gcc -L . -l primes -o list-primes
The -l primes argument tells the compiler the name of the library, in this case primes (meaning the compiler should look for a file called libprimes.a: the name of the file is the name of the library with the prefix lib and the suffix .a, which is what should be created with the archive tool). The -L . argument tells the compiler that the search path for libraries should include the current directory (this option can be modified if it is desirable to keep the library somewhere else, for example in a subfolder).

Note that once the compiler creates the final executable, it no longer depends on the archive file, because the object code inside the archive file is compiled into the final executable. This is in contrast to dynamic libraries, described in the next section.

Note also that the final compilation can also contain a combination of library code and standard source files; the following set of commands work fine:

gcc -I ./includes -c listprimes.c
gcc -I ./includes -c linkedlist.c
ar -r libprimes.a listprimes.o linkedlist.o
gcc -I ./includes main.c -L . -l primes -o list-primes

Dynamically linked libraries:

Instead of a static library, object files can instead be combined into a dynamic library. When the final executable is built, the object code in the dynamic library will not be compiled into the final exectubale; the final executable will be dependent on the dynamic library, and changes to the dynamic library will be reflected in the final program, without having to update the final executable.

The compiler can be used to convert object code into a dynamic library using the -shared flag as follows:

gcc -shared listprimes.o linkedlist.o -o libprimes.dll
Note that on some systems (but not Windows), it is necessary that when the original object code is compiled, the compiler is given the fPIC flag, meaning the object code is position-independent. On Windows, all code is effectively position-independent, so this flag is not necessary.

The final executable can then be compiled as follows:

gcc -I ./includes main.c -L . -l primes -o list-primes
Now, if a change is made to the libprimes.dll library (for example by changing listprimes.c and recompiling listprimes.o and libprimes.dll), then the changes will be reflected in list-primes.exe without having to rebuild the executable; this is also true for any other programs which depend on the libprimes.dll library. If libprimes.dll is moved or deleted, then list-primes.exe will no longer work.

NB the details of where a dynamic library can be located, and how it is named, vary from system to system. On Windows/MinGW, the simplest solution is to have the dynamic library located in the same directory as the final executable, and to make sure that its file extension is .dll. On Windows/Cygwin the file extension is .dll.a, on Linux/unix the file extension is .so (short for 'shared object'), and on Mac the file extension is .dylib.
