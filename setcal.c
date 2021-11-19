#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cardinality;
    int items[];
}set_t;

typedef struct {
    char firstItem;
    char secondItem;
}setItem;

typedef struct {
    int cardinality;
    setItem relationItems[];
}relation;

void initSet_t(int size){

}

int main(int argc, char *argv[]) {
    if(argc != 2){
        fprintf(stderr, "Invalid number of args\n");
        exit(EXIT_FAILURE);
    }
    printf("Arg: %s\n", argv[1]);
    FILE *file;
    file = fopen(argv[1], "r");
    int display, lineNum = 1, cardinality;
    while(1){
        display = fgetc(file);
        if(feof(file) || lineNum > 1000){
            break;
        }
        printf("%c", display);
        if(display == '\n'){
            initSet_t(cardinality);
            lineNum++;
            printf("\nnum of lines %d\n", lineNum);
        };
        if(display == 32){

        }

    }
    fclose(file);
    return 0;
}
