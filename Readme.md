##Getting started

\# To compile <br />
make

\# To run without a log file <br />
./adj input.txt

\# To run with a log file <br />
./adj input.txt > output.txt

##Introduction
AdjacentSwaps is a software tool, which is deveoped using GNU C++ language based on our previously developed TSG software tool \[1\]. 
It uses group-theoretic methods to find a minimum-length sequence of adjacent swaps required to sort an initial (bijective) assignment between <i>n</i> objects and <i>n</i> vertices in a graph with a line, ring, star, or complete topology. 
Our current implementation (Version 1.0) was tested both using gcc 4.1.2 running under a Linux operating system and using gcc 4.9.3 and Cygwin 2.3.1 running under a Windows operating system.
The background knowledge of AdjacentSwaps is discussed in \[2\] in detail.
##How to compile and run AdjacentSwaps (Version 1.0)
To find out if your system already has the [GNU C++ compiler][3], type "g++ -v" at a command prompt (or a [cygwin console][4]) and press return. If your system has the GNU C++ compiler and it is ready for use, it will show you the version of the GNU C++ compiler.<br />
Once the GNU C++ compiler is ready for use on your system, uncompress our source codes and data. <br />
To compile our source codes, type "make" at the source code directory. Then, you will find the executable file called "adj" in your source code directory if the compilation process is successful. <br />
To execute the program, type "./adj input.txt", where the "input.txt" is the file name of your input file. The output is displayed on the standard output. <br />
To execute the program with the output file, type "./adj input.txt > output.txt", where the notation ">" is used here for the redirection of the standard output to the output file. 
We provide a wide variety of the sample input files in the "data" directory, where the input files are configurable for the user's purposes.
##Availability
AdjacentSwaps is released under [GPLv3][1]. The latest source code is [freely
available at GitHub][2]. You may compile and run our source codes using [GNU C++ compiler][3] under a linux platform or a windows platform with the Cygwin toolkit. 
(The [Cygwin toolkit][4] provides a unix-like environment and a command line interface for Windows platform, and you may install the GNU C++ compiler during the installation procedure of the Cygwin toolkit.)
The version 1.0 of AdjacentSwaps was tested both using gcc 4.1.2 running under a Linux operating system and using gcc 4.9.3 and Cygwin 2.3.1 running under a Windows operating system.

##Brief description of source codes (Version 1.0)
\* main.cpp : This file is the main file of AdjacentSwaps. It takes a file as input and initializes the runtime environment of AdjacentSwaps.<br />
\* PGroup.h : This file is the header file of PGroup.cpp. <br />
\* PGroup.cpp: This file contains permutation group related functions. For example, it contains the routines of computing permutation inverse, multiplication, cycle decomposition, etc. <br />
\* MGS.h: This file is the header file of MGS.cpp. <br />
\* MGS.cpp: This file contains adjacent swap-based sorting functions using minimum generator sequences for permutations in the symmetric group S_n with respect to several generating sets of S_n.
<br />
\* Makefile: This file contains a building configuration that is used by the [GNU make][5] utility.<br />
\* 10input.txt, 20input.txt, ... , 200input.txt: These files are input files of AdjacentSwaps (see the "data" directory). For example, the input file "10input.txt" denotes the input file involving 10 objects and 10 vertices in a graph with a line, ring, star, or complete topology.<br />
\* 10output.txt, 20output.txt, ... , 200output.txt: These files are output files of AdjacentSwaps (see the "data" directory). They provide output for input files, such as 10input.txt, 20input.txt, 200input.txt, etc. <br />
##References

\[1\] Dohan Kim, "Task swapping networks in distributed systems", International Journal of Computer Mathematics, vol. 90, no. 11, pp. 2221-2243, 2013.

\[2\] Dohan Kim, "Sorting on graphs by adjacent swaps using permutation groups", Computer Science Review, vol. 22, pp. 89-105, 2016.

[1]: http://en.wikipedia.org/wiki/GNU_General_Public_License
[2]: https://github.com/SortingOnGraphs/AdjacentSwaps
[3]: https://gcc.gnu.org/
[4]: https://www.cygwin.com/
[5]: https://en.wikipedia.org/wiki/Make_(software)
