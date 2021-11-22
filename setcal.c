#include <stdio.h>
#include "stdbool.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cardinality;
    char items[][30];
} universum;

typedef struct {
    int id;
    int cardinality;
    char items[][30];
} set_t;

typedef struct {
    char firstItem;
    char secondItem;
} setItem;

typedef struct {
    int id;
    int cardinality;
    setItem relationItems[];
} relation;

void initSet_t(int size) {

}
/*
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
*/
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

int main(int argc, char *argv[]) {
    if(argc != 2){
        fprintf(stderr, "Invalid number of args\n");
        exit(EXIT_FAILURE);
    }
    printf("Arg: %s\n", argv[1]);
    FILE *file;
    file = fopen(argv[1], "r");
    int lineNum = 1, cardinality, sequence;
    bool U_found = false, R_found = false, S_found = false;
    //int string[][];
    universum universum;
    universum.cardinality = 0;
    set_t set;
    set.cardinality = 0;
    relation relation;
    while(!feof(file) || lineNum > 1000){
        int letter = fgetc(file);
        if(letter == EOF) break;
        if(!(letter >= 'A' && letter <= 'Z') && !(letter >= 'a' && letter <= 'z') && letter != 32 && !(letter >= '0' && letter <= '9') && letter != '\n' && (letter != 40 || letter != 41)) exit(EXIT_FAILURE);
        //printf("\n line: %d %c", lineNum, letter);
        if(letter == 'U') {
            U_found = true;
            continue;
        }
        if(letter == 'R') {
            R_found = true;
            continue;
        }
        if(letter == 'S') {
            S_found = true;
            continue;
        }
        if(letter == '\n'){
            U_found = false; R_found = false; S_found = false;
            lineNum++; sequence = 0;
            printf("\n%d:  ", lineNum);
            continue;
        }
        if(U_found){
            if(letter == 32) {
                universum.cardinality++;
                sequence = 0;
                printf("%d", universum.cardinality);
            } else {
                universum.items[universum.cardinality][sequence] = letter;
                sequence++;
            }
        }
        if(S_found){
            set.id = lineNum;
            if(letter == 32){
                sequence = 0;
                //printf("%c", letter);
                set.cardinality++;
            } else {
                set.items[set.cardinality][sequence] = letter;
                sequence++;
            }
        }
        if(R_found){
            relation.id = lineNum;
            if()
        }
    }
    printf("\ntest\n");
    fclose(file);
    for(int i = 0; i < 5; i++){
        printf("\n %d prvek: ", i);
        for(int j = 0; j < 1;j++){
            printf("%c",universum.items[i][j]);
        }
    }

/*
    set_t set;
    set.cardinality = 1;
    set.items[0] = 1;

    set_t set1;
    set1.cardinality = 1;
    set1.items[0] = 2;

    printf("Empty: %d \n", empty(set));
    printf("Card: %d\n", card(set));

    _union(&set, &set1);
*/
    return 0;
}
