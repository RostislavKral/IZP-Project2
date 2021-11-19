#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc != 2){
        fprintf(stderr, "Invalid number of args\n");
        exit(EXIT_FAILURE);
    }
    printf("Arg: %s\n", argv[1]);
    FILE *file;
    file = fopen(argv[1], "r");
    int display, lineNum = 0;
    while(1){
        display = fgetc(file);
        if(feof(file) || lineNum > 1000){
            break;
        }
        printf("%c", display);
        lineNum++;
    }
    fclose(file);
    return 0;
}
