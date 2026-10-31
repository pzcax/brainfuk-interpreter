#include <malloc.h>
#include <stdio.h>

int main() {
    #define TAPE_SIZE 30000 // this is how many bytes the "tape" has i guess

    unsigned char tape[TAPE_SIZE] = {0}; // putting [] after name is just declaring its "dimensions".
    unsigned char * ptr = tape;

    FILE * file = fopen("in.brainfuck", "r"); // open the file with read mode. similar to python's "with" stuff

    if (file == NULL) {
        printf("Death");
        return 1;
    }

    // get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size+1); //+1 for the \0 terminator

    if (buffer == NULL) {
        printf("malloc");
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, file_size, file);
    buffer[bytesRead] = '\0';

    fclose(file);


    for (int i = 0; buffer[i] != '\0'; i++) {
        char n = buffer[i];

        switch (n) {
            case '>': {
                ptr++;
                break;
            }
            case '<':{
                ptr--;
                break;
            }
            case '+': {
                (*ptr)++;
                break;
            }
            case '-': {
                (*ptr)--;
                break;
            }
            case '.': {
                char character = (*ptr);
                printf("%c", character);
                break;
            }
            case ',': {
                char input;
                scanf("%c", &input);
                (*ptr) = input;
                break;
            }
            case '[': {
                if ((*ptr) != 0) { break; } // skip if not
                int bracketCount = 1;
                while (bracketCount != 0) {
                    i++;
                    if (buffer[i] == '[') { bracketCount++; }
                    if (buffer[i] == ']') { bracketCount--; }
                }
                break;
            }
            case ']': {
                if ((*ptr) == 0) { break; }
                int bracketCount = 1;
                while (bracketCount > 0) {
                    i--;
                    if (buffer[i] == '[') { bracketCount--; }
                    if (buffer[i] == ']') { bracketCount++; }
                }
                break;
            }
        }
    }
    printf("\n");
    free(buffer);
    return 0;
}
