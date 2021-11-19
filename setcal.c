#include <stdio.h>
#include "stdbool.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cardinality;
    char items[1];
} set_t;

typedef struct {
    char firstItem;
    char secondItem;
} setItem;

typedef struct {
    int cardinality;
    setItem relationItems[];
} relation;

void initSet_t(int size) {

}

bool empty(set_t set) {
    return set.cardinality > 0 ? false : true;
}

int card(set_t set) {
    return set.cardinality;
}

int complement(set_t set) {

}

void _union(set_t *set_a, set_t *set_b) {
    char arr[set_a->cardinality];
    char arr2[set_b->cardinality];
    //printf("%d", set_b->items[0]);

    for(int i = 0; i < set_a->cardinality; i++)
    {
        arr[i]=set_a->items[i];
        printf("%d,", arr[i]);
    }

    for(int i = 0; i < set_b->cardinality; i++)
    {
        arr2[i]=set_b->items[i];
        printf("%d,", arr2[i]);

    }


}

int intersect() {

}

int minus() {

}

bool subseteq() {

}

bool subset() {

}

bool equals() {

}

int main(/*int argc, char *argv[]*/) {
    /*if(argc != 2){
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
    fclose(file);*/

    set_t set;
    set.cardinality = 1;
    set.items[0] = 1;

    set_t set1;
    set1.cardinality = 1;
    set1.items[0] = 2;

    printf("Empty: %d \n", empty(set));
    printf("Card: %d\n", card(set));

    _union(&set, &set1);

    return 0;
}
