#include <stdio.h>
#include "stdbool.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct {
    int cardinality;
    char **items;
} universum;

typedef struct {
    int id;
    int cardinality;
    char **items;
} set_t;

typedef struct {
    char *firstItem;
    char *secondItem;
} setItem;

typedef struct {
    int id;
    int cardinality;
    setItem *relationItems;
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
    int lineNum = 1, cardinality, sequence, itemCount;
    bool U_found = false, R_found = false, S_found = false, firstItem, secondItem;
    //int string[][];
    universum universum;
    universum.cardinality = 0;
    set_t set;
    set.cardinality = 0;
    relation relation;
    setItem item;
    //int*tmpItems; char*tmpItem;
    char *tmpStr = malloc(1);
    while(!feof(file) || lineNum > 1000){
        int letter = fgetc(file);
        if(letter == EOF) break;
        if(!(letter >= 'A' && letter <= 'Z') && !(letter >= 'a' && letter <= 'z') && letter != 32 && !(letter >= '0' && letter <= '9') && letter != '\n' && (letter != 40 || letter != 41)) exit(EXIT_FAILURE);
        //printf("\n line: %d %c", lineNum, letter);
        if(letter == 'U') {
            U_found = true;
            universum.items = malloc(0);
            continue;
        }
        if(letter == 'R') {
            R_found = true;
            relation.relationItems = malloc(0);
            continue;
        }
        if(letter == 'S') {
            S_found = true;
            set.items = malloc(0);
            continue;
        }
        if(letter == '\n'){
            //universum.items[universum.cardinality][0] = *tmpItem;
            U_found = false; R_found = false; S_found = false; firstItem = false; secondItem = false;
            lineNum++; sequence = 0; itemCount = 0;
            printf("\n%d:  ", lineNum);
            continue;
        }
        if(U_found){
            if(letter == 32) {
                sequence = 0;
                //printf("%c", letter);
                printf("\n*%s*\n", tmpStr);
                ++universum.cardinality;
                universum.items = realloc(universum.items, universum.cardinality * sizeof(char*));

                *(universum.items + (universum.cardinality - 1)) = tmpStr;

                sequence = 0;
                tmpStr = NULL;
            } else {
                tmpStr = realloc(tmpStr, (sequence + 1) * sizeof(char));
                *(tmpStr + sequence) = letter;
                ++sequence;
            }
        }
        if(S_found){
            set.id = lineNum;
            if(letter == 32){
                sequence = 0;
                //printf("%c", letter);
                printf("\n*%s*\n", tmpStr);
                ++set.cardinality;
                set.items = realloc(set.items, set.cardinality * sizeof(char*));

                *(set.items + (set.cardinality - 1)) = tmpStr;

                sequence = 0;
                tmpStr = NULL;
            } else {
                tmpStr = realloc(tmpStr, (sequence + 1) * sizeof(char));
                *(tmpStr + sequence) = letter;
                ++sequence;
            }
        }
        if(R_found){
            relation.id = lineNum;
            //neukonceny prvek
            if(letter == 41 && firstItem == true) exit(EXIT_FAILURE);
            if(letter == 41) {
                firstItem = true;
                relation.cardinality++;
                itemCount++;
                item.firstItem = malloc(0);
                continue;
            }
            if(letter == 32){
                printf("\n*%s*\n", tmpStr);
                firstItem = false;
                secondItem = true;
                sequence = 0;
                item.secondItem = malloc(0);
                continue;
            }
            //nezacnuty prvek
            if(letter == 41 && secondItem == true) exit(EXIT_FAILURE);
            if(letter == 42){
                firstItem = false;
                secondItem = false;
                relation.relationItems[itemCount] = item;
                relation.relationItems = realloc(relation.relationItems, relation.cardinality * sizeof(char*));
                continue;
            }
            if(firstItem){
                tmpStr = realloc(tmpStr, (sequence + 1) * sizeof(char));
                item.firstItem[sequence] = letter;
                sequence++;
            }
            if(secondItem){
                tmpStr = realloc(tmpStr, (sequence + 1) * sizeof(char));
                item.secondItem[sequence] = letter;
                sequence++;
            }
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
    free(tmpStr);
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
