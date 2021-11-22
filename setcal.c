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
    while(!feof(file) || lineNum > 1000){
        int letter = fgetc(file);
        if(!(letter >= 'A' && letter <= 'Z') && !(letter >= 'a' && letter <= 'z') && letter != 32 && !(letter >= '0' && letter <= '9') && letter != '\n') exit(EXIT_FAILURE);
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
                sequence++;
                universum.items[universum.cardinality][sequence] = letter;
            }
        }
        if(R_found){
            //universum universum;
            if(letter != 32){
                sequence++;
                printf("%c", letter);
            }
        }
        /*



        string[lineNum][]
        int type = fgetc(file);
        if(letter == 'U'){
            universum universum;
            while (!feof(file) || letter != '\n'){
                //letter = fgetc(file);
                if(!(letter > 'A' && letter < 'Z') && !(letter > 'a' && letter < 'z') && letter != 32 && !(letter >= '0' && letter <= '9')) exit(EXIT_FAILURE);
                if(letter != 32){
                    sequence++;
                    universum.items[universum.cardinality][sequence] = letter;
                    continue;
                }
                universum.cardinality++;
                break;
            }
            for(int i = 0; i < 4; i++){
                printf("\n %d prvek: ", i);
                for(int j = 0; i<30;j++){
                    printf("%c",universum.items[i][j]);
                }
            }
        }

        if(letter == 'S'){
            set_t set;
            set.id = lineNum;
            while (!feof(file) || letter != '\n'){
                letter = fgetc(file);
                if(!(letter > 'A' && letter < 'Z') && !(letter > 'a' && letter < 'z') && letter != 32 && !(letter >= '0' && letter <= '9')) exit(EXIT_FAILURE);
                if(letter != 32){
                    sequence++;
                    set.items[set.cardinality][sequence] = letter;
                    continue;
                }
                set.cardinality++;
                break;
            }
        }
        lineNum++;
     /*   while(!feof(file) || letter != '\n'){
            letter = fgetc(file);
            printf("%c", letter);
            if(!(letter > 'A' && letter < 'Z') && !(letter > 'a' && letter < 'z') && letter != 32 && !(letter >= '0' && letter <= '9')) exit(EXIT_FAILURE);
            if(letter == 32) sequence = 0; break;
            sequence++;
            temp[sequence] = letter;
        }
        string[lineNum][];
        lineNum++;*/
    }
    fclose(file);
    printf("test");
    for(int i = 0; i < 4; i++){
        printf("\n %d prvek: ", i);
        for(int j = 0; j < 30;j++){
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
