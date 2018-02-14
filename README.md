# Oblig1_OS

Zohaib Butt, Anders Bjørklund Jensen and Kent W. Holt


Task1
oppgave_4b.c

compile: gcc -Wall -o <file_name> oppgave_4b.c 
run: ./<file_name>

1. gcc file -Wall
	compile using gcc with all warnings.

Install: 
	Already existing on Ubuntu and OSX

2. cppcheck --enable=all ./<file_name>
	Cppcheck is code analysis tool for C/C++ code. 

Install:
	apt-get install cppcheck

3.	clang-tidy-5.0 -checks='*' <file_name> -- -std=c11
	Linter tool for C/C++ 

Install:
	apt-get install clang-tidy-5.0

4. valgrind

Task2
cd Task2
compile: gcc -Wall -pthread -o  <file_name> oppgave_5a.c
run: ./<file_name>

Task3
cd Task3
compile: gcc -Wall -pthread -o  <file_name> oppgave_6a.c
run: ./<file_name>



