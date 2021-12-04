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
void addToSetArray(SetArray *setArray, Set *set){
    setArray->length++;
    setArray->sets = realloc(setArray->sets, (setArray->length + 1)*sizeof(Set*));
    if(setArray->sets == NULL) exit(EXIT_FAILURE);
    //setArray->sets[setArray->length-1] = &set;
    *(setArray->sets + (setArray->length - 1)) = set;
}
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
int main (int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Invalid number of args\n");
        exit(EXIT_FAILURE);
    }

    printf("Arg: %s\n", argv[1]);
    FILE *file;
    file = fopen(argv[1], "r");

    SetArray setArray;
    setArray.length = 0;
    setArray.sets = NULL;

    char c, type = ' ';
    int cardinality = 0, sequence = 0, lineNum = 0, lineChar = 0;
    Set *universum;
    universum = setCreator();
    Set *set = setCreator();
    Set *tmpSet;
    char *tmpStr = malloc(1);

    while(true){
        c = fgetc(file);
        lineChar++;
        if(feof(file))break;
        if(lineChar == 2)continue;
        if(type == ' ') {
            type = c;
        }
        if((type == 'S' || type == 'U')&& lineChar == 1){
            tmpSet = setCreator();
            printf("Set created \n");
            continue;
        }
        if(c == ' ' || c == '\n'){
            ++cardinality;
            //printf(">> %s  %d\n", tmpStr, sequence);
            sequence = 0;

            setIncrement(tmpSet, tmpStr);
            tmpStr = NULL;
            if(c == '\n'){
                lineNum++;
                lineChar = 0;
                type = ' ';
                cardinality = 0;
                tmpSet->id = lineNum;
                //addToSetArray(&setArray, tmpSet);
                setArray.length++;
                setArray.sets = realloc(setArray.sets, setArray.length * sizeof(Set*));
                //printf("tmp card %d", tmpSet->cardinality);
                *(setArray.sets + (setArray.length - 1)) = tmpSet;
            }
            continue;
        }
        tmpStr = realloc(tmpStr, (sequence+1)*sizeof (char));
        if(tmpStr == NULL) exit(EXIT_FAILURE);
        *(tmpStr + sequence) = c;
        ++sequence;
        //printf("\n %c \n", tmpStr);
    }

    for (int i = 0; i < universum->cardinality; ++i) {
        printf("%s\n", universum->items[i]);
    }
    for (int i = 0; i < setArray.length; ++i) {
        printf("set %d (", setArray.sets[i]->id);
        for (int j = 0; j < setArray.sets[i]->cardinality; ++j) {
            printf(" %s ", setArray.sets[i]->items[j]);
        }
        printf(")\n");
    }
   /* for (int i = 0; i < 12; ++i) {
        printf("%s\n", set->items[i]);
    }*/
    //printf("test: %d", *tmpStr);
}