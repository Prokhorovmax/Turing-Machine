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
        fileOpenning(alphabet, argv[i], argv[i + 1], "-a", "rt");
        fileOpenning(inputTape, argv[i], argv[i + 1], "-i", "rt");
        fileOpenning(machine, argv[i], argv[i + 1], "-q", "rt");
        fileOpenning(output, argv[i], argv[i + 1], "-a", "wt");
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