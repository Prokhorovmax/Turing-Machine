#include "turingmachine.h"

#define DEFAULT_SIZE 15

int start(FILE *inputTape, FILE *alphabet, FILE *machine, FILE *output, int flag) {

    // Alphabet
    char *alphabetString = parseStreamLine(alphabet); // Stores alphabet characters
    int alphabetLength = strlen(alphabetString);
    for (int i = 0; i < alphabetLength; i++) {
        if (strchr(alphabetString, alphabetString[i]) != strrchr(alphabetString, alphabetString[i])) {
            printf("Symbols in alphabet input file cannot have duplicate\n");
            printf("\nProcess finished with exit code %d\n", 15);
            exit(15);
        }
    }
    if (strchr(alphabetString, '_') == NULL) {
        alphabetString = strcat(alphabetString, "_");
        alphabetLength = alphabetLength + 1;
    }
    fclose(alphabet);

    // Head
    char *headString = parseStreamLine(inputTape);
    headString[strlen(headString) - 1] = '\0'; // Deleting '\n' from the end of the string
    int headPos = -1; // Stores position of the head, counts from 0
    for (int i = 0; i < strlen(headString); i++) {
        if ((headString[i] != '.') && (headString[i] != 'V')) {
            printf("The problem of determining the position of the head\n");
            printf("Input tape file. Error in line: 1");
            printf("\nProcess finished with exit code %d\n", 17);
            exit(17);
        } else if ((headString[i] == 'V') && (headPos > 0)) {
            printf("Tape must contain exactly one head\n");
            printf("Input tape file. Error in line: 1");
            printf("\nProcess finished with exit code %d\n", 18);
            exit(18);
        } else if (headString[i] == 'V') {
            headPos = i;
        }
    }
    if (headPos < 0) {
        printf("Tape must contain exactly one head\n");
        printf("Input tape file. Error in line: 1");
        printf("\nProcess finished with exit code %d\n", 18);
        exit(18);
    }

    // Initial tape
    char *tape = parseStreamLine(inputTape);
    for (int i = 0; i < strlen(tape); i++) {
        if (strchr(alphabetString, tape[i]) == NULL) {
            printf("Tape must contain only alphabet characters\n");
            printf("Input tape file. Error in line: 2");
            printf("\nProcess finished with exit code %d\n", 16);
            exit(16);
        }
    }
    fclose(inputTape);

    // State-machine
    int numberOfStates = 0;
    int maxStatesNumber = DEFAULT_SIZE;
    int *stateNumbers;
    int *stateIndexes; // Start line index of each state column
    struct COMMAND **commands;

    // Memory allocation
    commands = (struct COMMAND **) calloc(DEFAULT_SIZE, sizeof(struct COMMAND *));
    if (commands == NULL) {
        printf("Memory allocation error\n");
        printf("\nProcess finished with exit code %d\n", 3);
        exit(3);
    }
    if (alphabetLength > DEFAULT_SIZE) {
        commands = (struct COMMAND **) realloc(commands, alphabetLength * sizeof(struct COMMAND *));
        if (commands == NULL) {
            printf("Memory allocation error\n");
            printf("\nProcess finished with exit code %d\n", 3);
            exit(3);
        }
        for (int i = 0; i < alphabetLength; i++) {
            commands[i] = (struct COMMAND *) calloc(DEFAULT_SIZE, sizeof(struct COMMAND));
            if (commands[i] == NULL) {
                printf("Memory allocation error\n");
                printf("\nProcess finished with exit code %d\n", 3);
                exit(3);
            }
        }
    }
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        commands[i] = (struct COMMAND *) calloc(DEFAULT_SIZE, sizeof(struct COMMAND));
        if (commands[i] == NULL) {
            printf("Memory allocation error\n");
            printf("\nProcess finished with exit code %d\n", 3);
            exit(3);
        }
    }
    stateNumbers = (int *) calloc(DEFAULT_SIZE, sizeof(int));
    if (stateNumbers == NULL) {
        printf("Memory allocation error\n");
        printf("\nProcess finished with exit code %d\n", 3);
        exit(3);
    }
    stateIndexes = (int *) calloc(DEFAULT_SIZE, sizeof(int));
    if (stateIndexes == NULL) {
        printf("Memory allocation error\n");
        printf("\nProcess finished with exit code %d\n", 3);
        exit(3);
    }

    // Parsing first line of state-machine input data file
    char *firstMachineLine = parseStreamLine(machine);
    firstMachineLine[strlen(firstMachineLine) - 1] = '\0';
    if ((firstMachineLine[0] != '.') && (firstMachineLine[1] != ' ')) {
        printf("Wrong state-machine input data format\n");
        printf("State-machine input file. Error in line: 1\n");
        printf("\nProcess finished with exit code %d\n", 5);
        exit(5);
    }
    for (int i = 2; i < strlen(firstMachineLine) - 1; i++) {
        if (((isNumber(firstMachineLine[i]) == -1) && (firstMachineLine[i] != 'q') && (firstMachineLine[i] != '.') &&
             (firstMachineLine[i] != ' ')) ||
            ((firstMachineLine[i] == '.') && (firstMachineLine[i + 1] != ' ') && (firstMachineLine[i + 1] != 'q') &&
             (firstMachineLine[i + 1] != '\0')) ||
            ((firstMachineLine[i] == 'q') && (isNumber(firstMachineLine[i + 1]) == -1)) ||
            ((isNumber(firstMachineLine[i] != -1)) && (isNumber(firstMachineLine[i + 1] == -1)) &&
             (firstMachineLine[i + 1] != '.')) ||
            ((firstMachineLine[i] == ' ') && (firstMachineLine[i + 1] != ' ') && (firstMachineLine[i + 1] != '.') &&
             (firstMachineLine[i + 1] != '\0'))) {
            printf("Wrong state-machine input data format\n");
            printf("State-machine input file. Error in line: 1\n");
            printf("\nProcess finished with exit code %d\n", 5);
            exit(5);
        } else if ((firstMachineLine[i] == '.') && (firstMachineLine[i + 1] == 'q')) {
            stateNumbers[numberOfStates] = parseState(firstMachineLine, i + 2);
            stateIndexes[numberOfStates] = i;
            numberOfStates++;
        }
        if (i == maxStatesNumber) {
            maxStatesNumber = maxStatesNumber * 2;
            stateNumbers = (int *) realloc(stateNumbers, maxStatesNumber * sizeof(int));
            if (stateNumbers == NULL) {
                printf("Memory allocation error\n");
                printf("\nProcess finished with exit code %d\n", 3);
                exit(3);
            }
            stateIndexes = (int *) realloc(stateIndexes, maxStatesNumber * sizeof(int));
            if (stateIndexes == NULL) {
                printf("Memory allocation error\n");
                printf("\nProcess finished with exit code %d\n", 3);
                exit(3);
            }
        }
    }

    // Parsing state-machine commands
    for (int i = 0; i < alphabetLength; i++) {
        char *line = parseStreamLine(machine);
        if (line[0] == '\0') {
            printf("State-machine must contain all alphabet symbols in the first column\n");
            printf("State-machine input file. Error in line: %d\n", i + 2);
            printf("\nProcess finished with exit code %d\n", 7);
            exit(7);
        }
        if (i != alphabetLength - 1) {
            line[strlen(line) - 1] = '\0';
        }
        if ((i == alphabetLength - 1) && (line[strlen(line) - 1]) == '\n') {
            printf("State-machine input file cannot have additional line at the end\n");
            printf("State-machine input file. Error in line: %d\n", i + 2);
            printf("\nProcess finished with exit code %d\n", 12);
            exit(12);
        }
        if (line[0] != alphabetString[i]) {
            if (strlen(line) == 0) {
                printf("Empty line in state-machine file if forbidden\n");
            }
            printf("First symbols of lines in state-machine file must have the same sequence "
                           "as the sequence of characters in the alphabet\n");
            printf("State-machine input file. Error in line: %d\n", i + 2);
            printf("\nProcess finished with exit code %d\n", 14);
            exit(14);
        }

        struct COMMAND *lineCommands;
        lineCommands = (struct COMMAND *) calloc(DEFAULT_SIZE, sizeof(struct COMMAND));
        if (numberOfStates > DEFAULT_SIZE) {
            lineCommands = (struct COMMAND *) realloc(lineCommands, numberOfStates * sizeof(struct COMMAND));
        }
        if (lineCommands == NULL) {
            printf("Memory allocation error\n");
            printf("\nProcess finished with exit code %d\n", 3);
            exit(3);
        }

        int prev = 1;
        for (int j = 0; j < numberOfStates; j++) {
            int n = stateIndexes[j];
            if ((line[n] == NULL) || (line[n] == '\0')) {
                struct COMMAND command;
                command.newSymbol = '?';
                command.move = '?';
                command.newState = -1;
                lineCommands[j] = command;
                continue;
            }
            for (int k = prev + 1; k < n; k++) {
                if (line[k] != ' ') {
                    printf("The state columns in the input file must have strong structure separated by spaces\n");
                    printf("State-machine input file. Error in line: %d\n", i + 2);
                    printf("\nProcess finished with exit code %d\n", 10);
                    exit(10);
                }
            }
            lineCommands[j] = parseCommand(line, n, i + 2);
            if ((lineCommands[j].newSymbol == '?') && (lineCommands[j].move == '?') &&
                (lineCommands[j].newState == -1)) {
                continue;
            }
            if (strchr(alphabetString, lineCommands[j].newSymbol) == NULL) {
                printf("New tape symbol must be from alphabet\n");
                printf("State-machine input file. Error in line: %d\n", i + 2);
                printf("\nProcess finished with exit code %d\n", 8);
                exit(8);
            }
            if ((lineCommands[j].move != '.') && (lineCommands[j].move != '>') && (lineCommands[j].move != '<')) {
                printf("Unknown move command\n");
                printf("State-machine input file. Error in line: %d\n", i + 2);
                printf("\nProcess finished with exit code %d\n", 9);
                exit(9);
            }
            int exist = 0;
            for (int k = 0; k < numberOfStates; k++) {
                if (stateNumbers[k] == lineCommands[j].newState) {
                    exist = 1;
                    break;
                }
            }
            if ((lineCommands[j].newState != 0) && (exist == 0)) {
                printf("New state in commands must be present in the first line of state-machine table (it must exist)\n");
                printf("State-machine input file. Error in line: %d\n", i + 2);
                printf("\nProcess finished with exit code %d\n", 13);
                exit(13);
            }
            char *stateNumStr;
            stateNumStr = (char *) calloc(DEFAULT_SIZE, sizeof(char));
            itoa(lineCommands[j].newState, stateNumStr, 10);
            prev = n + 2 + strlen(stateNumStr);
        }
        commands[i] = lineCommands;
    }
    fclose(machine);

    free(headString);
    free(stateIndexes);
    free(firstMachineLine);

    process(alphabetString, headPos, tape, stateNumbers, numberOfStates, commands, flag, output);
}

// Determination of state number
int parseState(char *str, int index) {
    int stateNumber = 0;
    int i = index;
    int rank = 0;
    while (isNumber(str[i]) != -1) {
        rank++;
        i++;
    }
    i = index;
    while (rank > 0) {
        char *string;
        string = (char *) calloc(2, sizeof(char));
        if (string == NULL) {
            printf("Memory allocation error\n");
            printf("\nProcess finished with exit code %d\n", 3);
            exit(3);
        }
        string[0] = str[i];
        stateNumber += atoi(string) * pow(10, rank - 1);
        rank--;
        i++;
    }
    if (stateNumber > 0) {
        return stateNumber;
    } else {
        printf("Wrong state number\n");
        printf("Error in line: 1\n");
        printf("\nProcess finished with exit code %d\n", 6);
        exit(6);
    }
}

// Making command from string
struct COMMAND parseCommand(char *str, int index, int line) {
    struct COMMAND command;
    if ((str[index] == ' ') && (str[index + 1] == ' ') && (str[index + 2] == ' ') && (str[index + 3] == ' ')) {
        command.newSymbol = '?';
        command.move = '?';
        command.newState = -1;
        return command;
    }
    command.newSymbol = str[index];
    command.move = str[index + 1];
    if (str[index + 2] != 'q') {
        printf("Wrong state-machine command format\n");
        printf("State-machine input file. Error in line: %d\n", line);
        printf("\nProcess finished with exit code %d\n", 11);
        exit(11);
    }
    int i = index + 3;
    int rank = 0;
    int num = 0;
    if (isNumber(str[i]) == -1) {
        printf("Wrong state-machine command format\n");
        printf("State-machine input file. Error in line: %d\n", line);
        printf("\nProcess finished with exit code %d\n", 11);
        exit(11);
    }
    while ((str[i] != ' ') && (str[i] != '\0')) {
        if (isNumber(str[i]) != -1) {
            rank++;
            i++;
        } else {
            printf("Wrong state number\n");
            printf("State-machine input file. Error in line: %d\n", line);
            printf("\nProcess finished with exit code %d\n", 6);
            exit(6);
        }
    }
    i = index + 3;
    while (rank > 0) {
        char *string;
        string = (char *) calloc(2, sizeof(char));
        if (string == NULL) {
            printf("Memory allocation error\n");
            printf("\nProcess finished with exit code %d\n", 3);
            exit(3);
        }
        string[0] = str[i];
        num += atoi(string) * pow(10, rank - 1);
        rank--;
        i++;
    }
    command.newState = num;
    return command;
}