#include "turingmachine.h"

void printTape(int headPos, char *tape, FILE *output) {
    int length = strlen(tape);
    // Head line
    for (int i = 0; i < length; i++) {
        if (i == headPos) {
            printf("%c", 'V');
            fprintf(output, "%c", 'V');
        } else {
            printf("%c", '.');
            fprintf(output, "%c", '.');
        }
    }
    printf("\n");
    fprintf(output, "\n");

    // Tape
    printf("%s\n", tape);
    fprintf(output, "%s\n", tape);

    // Numbers
    int i = 0;
    int cond = 0;
    while (cond != length) {
        char str[2];
        itoa(i, str, 10);
        printf("%1s", str);
        fprintf(output, "%1s", str);
        if (i < 9) {
            i++;
        } else {
            i = 0;
        }
        cond++;
    }
    printf("\n\n");
    fprintf(output, "\n\n");
}

void printCommand(int currentState, char currentSymbol, struct COMMAND command, FILE *output) {
    printf("q%d %c %c %c q%d\n", currentState, currentSymbol, command.move, command.newSymbol, command.newState);
    fprintf(output, "q%d: %c %c %c q%d\n", currentState, currentSymbol, command.move, command.newSymbol, command.newState);
}

void printStart(FILE *output) {
    printf("START\n\n");
    fprintf(output, "START\n\n");
}

void printEnd(FILE *output) {
    printf("END\n");
    fprintf(output, "END\n");
}

void printStop(FILE *output) {
    printf("FORCED STOP\n");
    fprintf(output, "FORCED STOP\n");
}