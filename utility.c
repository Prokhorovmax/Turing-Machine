#include "turingmachine.h"

#define DEFAULT_SIZE 15

// Checking symbol for belonging to numbers
int isNumber(char ch) {
    char num[] = "0123456789";
    if (strchr(num, ch) != NULL) {
        char *string;
        string = (char *) calloc(2, sizeof(char));
        string[0] = ch;
        return atoi(string);
    } else {
        return -1;
    }
}

// x^y
int pow(int x, int y) {
    int res = 1;
    for (int i = 0; i < y; i++) {
        res = res * x;
    }
    return res;
}

// Parsing line from stream to string
char *parseStreamLine(FILE *file) {
    char *string;
    int newNumber = DEFAULT_SIZE;
    int total = DEFAULT_SIZE;
    string = (char *) calloc(DEFAULT_SIZE, sizeof(char));
    if (string == NULL) {
        printf("Memory allocation error\n");
        printf("\nProcess finished with exit code %d\n", 3);
        exit(3);
    }
    fgets(string, DEFAULT_SIZE, file);
    char *firstNullSymbol = strchr(string, '\0');
    while (((firstNullSymbol - string + 1) == total) && (string[strlen(string) - 1] != '\n')) {
        newNumber = newNumber * 2;
        char *string1;
        string1 = (char *) calloc(DEFAULT_SIZE, sizeof(char));
        if (string1 == NULL) {
            printf("Memory allocation error\n");
            printf("\nProcess finished with exit code %d\n", 3);
            exit(3);
        }
        string1 = (char *) realloc(string1, newNumber * sizeof(char));
        if (string1 == NULL) {
            printf("Memory allocation error\n");
            printf("\nProcess finished with exit code %d\n", 3);
            exit(3);
        }
        char *ret = fgets(string1, newNumber, file);
        if (ret != NULL) {
            string = strcat(string, string1);
        }
        firstNullSymbol = strchr(string, '\0');
        total += (newNumber - 1);
    }
    return string;
}

void fileOpenning (FILE *file, char *arg, char *nextArg, char *flag, char *key) {
    if (strcmp(arg, flag) == 0) {
        file = fopen(nextArg, key);
        if (file == NULL) {
            printf("Cannot get file %s\n", nextArg);
            printf("\nProcess finished with exit code %d\n", 23);
            exit(23);
        }
    }
}
