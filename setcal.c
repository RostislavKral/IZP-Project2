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
    int id;
    int cardinality;
    RelationPair **items;
} Relation;
typedef struct {
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
Relation *relCreator(){
    Relation *rel = malloc(sizeof(Relation));
    rel->items = malloc(1);
    rel->cardinality = 0;
    rel->id =0;
    return rel;
}
RelationPair *relPairCreator(){
    RelationPair *relPair = malloc(sizeof(Relation));
    relPair->first = malloc(1);
    relPair->second = malloc(1);
    return relPair;
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
void relIncrement(Relation *rel, RelationPair *tmpRelPair){
    ++(rel->cardinality);
    rel->items = realloc(rel->items, (rel->cardinality) * sizeof(char*));
    if(rel->items == NULL) exit(EXIT_FAILURE);
    *(rel->items + (rel->cardinality - 1)) = tmpRelPair;
}

void isReflexive(Relation *relation, Set *universum){
    printf("noice\n");
    for (int j = 0; j < relation->cardinality; ++j) {
        printf("( %s ",relation->items[j]->first);
        printf("%s )", relation->items[j]->second);
    }
    printf("\n");

};
void isSymmetric(Relation *relation){
    printf("noice\n");
};
void isAntiSymmetric(Relation *relation){
    printf("noice\n");
};
void isTransitive(Relation *relation){
    printf("noice\n");
};
void isFunction(Relation *relation){
    printf("noice\n");
};
void domain(Relation *relation){
    printf("noice\n");
};
void codomain(Relation *relation){
    printf("noice\n");
};
void isInjective(Relation *relation, Set *setA, Set *setB){
    printf("noice\n");
};
void isSurjective(Relation *relation, Set *setA, Set *setB){
    printf("noice\n");
};
void isBijective(Relation *relation, Set *setA, Set *setB){
    printf("noice\n");
};
void *findRelation(RelationArray *relArray, int num){
    for(int i = 0; i < relArray->length; i++){
        if(relArray->relations[i]->id == num) {
            return relArray->relations[i];
        }
    }
  //  return NULL;
}
void *findSet(SetArray *setArray, int num){
    for(int i = 0; i < setArray->length; i++){
        if(setArray->sets[i]->id == num) {
            return setArray->sets[i];
        }
    }
    //return NULL;
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
    Relation *tmpRel;
    RelationPair *tmpRelPair;
    universum = setCreator();
    tmpSet = setCreator();
    tmpRel = relCreator();
    tmpRelPair = relPairCreator();

    char c, type = ' ';
    int cardinality = 0, sequence = 0, lineNum = 0, lineChar = 0;
    char *tmpStr = malloc(1);
    char *tmpRelItem = NULL;
    bool first = false, second = false;
    char *command = NULL;
    char **cmdArgs = NULL;
    int cmdNum = 0;
    while (true) {
        c = fgetc(file);
        lineChar++;
        if (feof(file))break;
        if (lineChar == 2)continue;
        if (type == ' ') {
            if (c != 'U' && c != 'C' && c != 'R' && c != 'S'){
                printf("Unknown command %c in file %s on line %d \n", c, argv[1], lineNum+1);
                exit(EXIT_FAILURE);
            }
            type = c;
            continue;
        }
        // TODO: když není řádek ukončen \n tak se celý řádek nepropíše
        if (c == ' ' || c == '\n') {
            ++cardinality;
            sequence = 0;
            if(type == 'U'){
                setIncrement(universum, tmpStr);
            }
            if(type == 'S') {
                setIncrement(tmpSet, tmpStr);
            }
            if(type == 'R'){
                if(first){
                    tmpRelPair = malloc(sizeof (tmpStr));
                    tmpRelPair->first = tmpStr;
                    first = false;
                }
                if (second) {
                    tmpRelPair->second = tmpStr;
                    second = false;
                    relIncrement(tmpRel, tmpRelPair);
                    tmpRelPair = NULL;
                }
            }
            if(type == 'C'){
                if(command != NULL) {
                    cmdNum++;
                    cmdArgs = realloc(cmdArgs, sizeof(char*));
                    if(cmdArgs == NULL )exit(EXIT_FAILURE);
                    *(cmdArgs + (cmdNum - 1)) = tmpStr;
                }
                if(command == NULL) command = tmpStr;
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
                    tmpSet = setCreator();
                }
                if(type == 'R'){
                    tmpRel->id = lineNum;
                    relArray.length++;
                    relArray.relations = realloc(relArray.relations, relArray.length * sizeof(Relation *));
                    *(relArray.relations + (relArray.length - 1)) = tmpRel;
                    tmpRel = relCreator();
                }
                if(type == 'C'){
                    int firstArg = 0, secondArg = 0, thirdArg = 0;
                    if(cmdArgs[0] != NULL) firstArg = atoi(cmdArgs[0]);
                    if(cmdArgs[1] != NULL) secondArg = atoi(cmdArgs[1]);
                    if(cmdArgs[2] != NULL) thirdArg = atoi(cmdArgs[2]);
                    if(strcmp(command, "reflexive") == 0){isReflexive(findRelation(&relArray,firstArg), universum);}
                    if(strcmp(command, "symmetric") == 0){isSymmetric(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "antisymmetric") == 0){isAntiSymmetric(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "transitive") == 0){isTransitive(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "function") == 0){isFunction(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "domain") == 0){domain(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "codomain") == 0){codomain(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "injective") == 0){isInjective(findRelation(&relArray,firstArg), findSet(&setArray,secondArg),findSet(&setArray, thirdArg));}
                    if(strcmp(command, "surjective") == 0){isSurjective(findRelation(&relArray,firstArg), findSet(&setArray,secondArg),findSet(&setArray, thirdArg));}
                    if(strcmp(command, "bijective") == 0){isBijective(findRelation(&relArray,firstArg), findSet(&setArray,secondArg),findSet(&setArray, thirdArg));}
                    printf("Command: %s Args:", command);
                    for (int i = 0; i < cmdNum; i++){
                        printf(" %s ", cmdArgs[i]);
                    }
                    printf("\n");
                    command = NULL;
                    cmdNum = 0;
                    cmdArgs = NULL;
                }
                type = ' ';
                //command = NULL;
            }
            continue;
        }
        if(type == 'R'){
            if(c == '('){
                first = true;
                continue;
            }
            if(c == ')') {
                second = true;
                continue;
            }
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

   // printf("\n");
    for (int i = 0; i < relArray.length; ++i) {
        printf("Rel %d ", relArray.relations[i]->id);
        for (int j = 0; j < relArray.relations[i]->cardinality; ++j) {
            printf("( %s ", relArray.relations[i]->items[j]->first);
            printf("%s )", relArray.relations[i]->items[j]->second);
            /*for(int k = 0; j < relArray.relations; k++){
                printf("%s", rel)
            }*/
        }
        printf("\n");
    }
}