turingmachine.exe : input.o start.o process.o output.o utility.o
	gcc -o turingmachine input.o start.o process.o output.o utility.o

input.o : input.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o input.o input.c

start.o : start.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o start.o start.c

process.o : process.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o process.o process.c

output.o : output.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o output.o output.c

utility.o : utility.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o utility.o utility.c