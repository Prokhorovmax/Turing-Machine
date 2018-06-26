#include "turingmachine.h"

int main(int argc, char *argv[]) {

    if (argc == 1) {
        information();
        printf("\nProcess finished with exit code %d\n", 0);
        exit(0);
    }

    if ((argc != 9) && (argc != 10)) {
        printf("Wrong number of arguments in command line launch\n");
        printf("\nProcess finished with exit code %d\n", 22);
        exit(22);
    }

    FILE *inputTape;
    FILE *alphabet;
    FILE *machine;
    FILE *output;
    int flag;

    for (int i = 1; i < 8; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            alphabet = fopen(argv[i + 1], "rt");
            if (alphabet == NULL) {
                printf("Cannot get file %s\n", argv[i + 1]);
                printf("\nProcess finished with exit code %d\n", 23);
                exit(23);
            }
        }
        if (strcmp(argv[i], "-i") == 0) {
            inputTape = fopen(argv[i + 1], "rt");
            if (inputTape == NULL) {
                printf("Cannot get file %s\n", argv[i + 1]);
                printf("\nProcess finished with exit code %d\n", 23);
                exit(23);
            }
        }
        if (strcmp(argv[i], "-q") == 0) {
            machine = fopen(argv[i + 1], "rt");
            if (machine == NULL) {
                printf("Cannot get file %s\n", argv[i + 1]);
                printf("\nProcess finished with exit code %d\n", 23);
                exit(23);
            }
        }
        if (strcmp(argv[i], "-o") == 0) {
            output = fopen(argv[i + 1], "wt");
            if (output == NULL) {
                printf("Cannot get file %s\n", argv[i + 1]);
                printf("\nProcess finished with exit code %d\n", 23);
                exit(23);
            }
        }
    }
    if ((alphabet == NULL) || (inputTape == NULL) || (machine == NULL) || (output == NULL)) {
        printf("Wrong format of command line launch\n");
        printf("\nProcess finished with exit code %d\n", 24);
        exit(24);
    }

    if ((argc == 10) && (strcmp(argv[9], "-debug") == 0)) {
        flag = 1;
    } else {
        flag = 0;
    }

    start(inputTape, alphabet, machine, output, flag);
}

void information() {
    printf("Turing Machine simulator.\n"
                   "The simulator is based on a text representation.\n"
                   "It converts the input tape according to the commands of state-control machine.\n"
                   "A feature of this machine is its one-sidedness.\n"
                   "It means that head-pointer cannot go to the left of the initial position.\n\n"
                   "To RUN the program type this line:\n"
                   "TuringMachine.exe -a alphabet.txt -i inputtape.txt -q machine.txt -o output.txt [-debug]\n"
                   "Format of alphabet input file:\n"
                   "0123ABC\n"
                   "Format of input tape file:\n"
                   "....V....\n"
                   "____1010_\n"
                   "Format of state-machine input file:\n"
                   ". .q1. .q2.\n"
                   "0 1>q1 1>q1\n"
                   "1 2>q1 2>q1\n"
                   "2 0>q2 0.q0\n"
                   "_ _.q0 _.q0\n"
                   "\n"
                   "Symbol '_' stands for empty cell.\n"
                   "Flags '-a', '-i', '-q', '-o' must be placed in front of the corresponding file.\n"
                   "Flag '-debug' runs debug configuration, where:\n"
                   "'N' -> next step\n"
                   "'RUN' -> running to the end\n"
                   "'STOP' -> stops the program\n");
}