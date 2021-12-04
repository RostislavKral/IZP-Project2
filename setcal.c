#include <stdio.h>
#include "stdbool.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    int cardinality;
    char **items;
} Set;
typedef struct {
    int length;
    Set **sets;
} SetArray;
typedef struct {
    char *first;
    char *second;
} RelationPair;
typedef struct {
    int cardinality;
    RelationPair **items;
} Relation;
typedef struct {
    int id;
    int length;
    Relation **relations;
}RelationArray;

Set *setCreator(){
    Set *set = malloc(sizeof(Set));
    set->id = 0;
    set->cardinality = 0;
    set->items = malloc(1);
    return set;
}
void *setDestructor(Set *set){
    if(set){
      for(int i = 0; i < set->cardinality; i++){
          free(set->items[i]);
          if(set->items[i] != NULL) exit(EXIT_FAILURE);
      }
      free(set->items);
      free(set);
      if(set != NULL) exit(EXIT_FAILURE);
    }
    return 0;
}
void setIncrement(Set *set, char *item){
    ++(set->cardinality);
    set->items = realloc(set->items, (set->cardinality) * sizeof(char*));
    if(set->items == NULL) exit(EXIT_FAILURE);
    *(set->items + (set->cardinality - 1)) = item;
}
int main (int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid number of args\n");
        exit(EXIT_FAILURE);
    }

    printf("Arg: %s\n", argv[1]);
    FILE *file;
    file = fopen(argv[1], "r");

    SetArray setArray;
    setArray.length = 0;
    setArray.sets = NULL;

    RelationArray relArray;
    relArray.length = 0;
    relArray.relations = NULL;

    Set *universum;
    Set *tmpSet;
    universum = setCreator();
    tmpSet = setCreator();

    char c, type = ' ';
    int cardinality = 0, sequence = 0, lineNum = 0, lineChar = 0;
    char *tmpStr = malloc(1);

    while (true) {
        c = fgetc(file);
        lineChar++;
        if (feof(file))break;
        if (lineChar == 2)continue;
        if (type == ' ') {
            type = c;
            continue;
        }
        if (c == ' ' || c == '\n') {
            ++cardinality;
            sequence = 0;

            if(type == 'U'){
                setIncrement(universum, tmpStr);
            } else if(type == 'R') {
                setIncrement(tmpSet, tmpStr);
            } else {
                setIncrement(tmpSet, tmpStr);
            }
            tmpStr = NULL;
            if (c == '\n') {
                lineNum++;
                lineChar = 0;
                cardinality = 0;
                if(type == 'S'){
                    tmpSet->id = lineNum;
                    setArray.length++;
                    setArray.sets = realloc(setArray.sets, setArray.length * sizeof(Set *));
                    *(setArray.sets + (setArray.length - 1)) = tmpSet;
                }
                type = ' ';
                tmpSet = setCreator();
            }
            continue;
        }
        if(type == 'R'){
            if(c == '(') continue;
            if(c == ')') continue;
        }
        tmpStr = realloc(tmpStr, (sequence + 1) * sizeof(char));
        if (tmpStr == NULL) exit(EXIT_FAILURE);
        *(tmpStr + sequence) = c;
        ++sequence;
    }
    printf("Universum: ");
    for (int i = 0; i < universum->cardinality; ++i) {
        printf("%s ", universum->items[i]);
    }
    printf("\n");
    for (int i = 0; i < setArray.length; ++i) {
        printf("set %d (", setArray.sets[i]->id);
        for (int j = 0; j < setArray.sets[i]->cardinality; ++j) {
            printf(" %s ", setArray.sets[i]->items[j]);
        }
        printf(")\n");
    }
}