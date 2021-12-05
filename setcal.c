#include <stdio.h>
#include "stdbool.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

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
} RelationArray;

Set *setCreator() {
    Set *set = malloc(sizeof(Set));
    set->id = 0;
    set->cardinality = 0;
    set->items = NULL;
    return set;
}

Relation *relCreator() {
    Relation *rel = malloc(sizeof(Relation));
    rel->items = NULL;
    rel->cardinality = 0;
    rel->id = 0;
    return rel;
}

RelationPair *relPairCreator() {
    RelationPair *relPair = malloc(sizeof(Relation));
    relPair->first = NULL;
    relPair->second = NULL;
    return relPair;
}
void setDestructor(Set *set) {
    free(set->items);
    free(set);
    //if(set != NULL) exit(EXIT_FAILURE);
}
void relPairDestructor(RelationPair *relationPair){
    free(relationPair->first);
    free(relationPair->second);
    free(relationPair);
    //if(relationPair != NULL) exit(EXIT_FAILURE);
}
void relDestructor(Relation *relation){
    free(relation->items);
    free(relation);
    //if(relation != NULL) exit(EXIT_FAILURE);
}
void setIncrement(Set *set, char *item) {
    ++(set->cardinality);
    //char **ptr = NULL;
    set->items= realloc(set->items, (set->cardinality) * sizeof(char *));
    //set->items = ptr;
    printf("test: %p \n", item);
    *(set->items + (set->cardinality - 1)) = item;
    for (int i = 0; i < set->cardinality; ++i) {
        printf("test: %p   ", set->items[i]);
    }
}

void relIncrement(Relation *rel, RelationPair *tmpRelPair) {
    ++(rel->cardinality);
    rel->items = realloc(rel->items, (rel->cardinality) * sizeof(char *));
    if (rel->items == NULL)
        exit(EXIT_FAILURE);
    *(rel->items + (rel->cardinality - 1)) = tmpRelPair;
}

void isReflexive(Relation *relation, Set *universum);

void isSymmetric(Relation *relation);

void isAntiSymmetric(Relation *relation);

void isTransitive(Relation *relation);

void isFunction(Relation *relation);

void domain(Relation *relation);

void codomain(Relation *relation);

bool isInjective(Relation *relation, Set *setA, Set *setB, bool printResult);

bool isSurjective(Relation *relation, Set *setA, Set *setB, bool printResult);

void isBijective(Relation *relation, Set *setA, Set *setB);

bool containsRelationPair(Relation *relation, RelationPair relationPair);

void printSet(Set *set) {
    printf("S ");
    for (int i = 0; i < set->cardinality; ++i) {
        printf("%s", set->items[i]);

        if (i != set->cardinality - 1) {
            printf(" ");
        }
    }

    printf("\n");
}

bool empty(Set *set) {
    bool result = set->cardinality == 0 ? true : false;
    printf("%d", set->cardinality);
    printf("%s\n", result ? "true" : "false");
    return result;
}

void card(Set *set) {
    printf("%d\n", set->cardinality);
}

void complement(Set *set, Set *universum) {
    Set *complementSet = setCreator();
    for (int i = 0; i < set->cardinality; ++i) {
        setIncrement(complementSet, set->items[i]);
    }

    printSet(complementSet);
    int control;
    char *tmp;
    for (int i = 0; i < universum->cardinality; ++i) {
        control = 0;
        tmp = NULL;
        for (int j = 0; j < set->cardinality; ++j) {
            printf("Prvek mnoziny: %s\n", set->items[j]);
            printf("Prvek univerza: %s\n", universum->items[i]);
            printf("STRCMP: %d\n", strcmp(set->items[j], universum->items[i]));
            if (strcmp(set->items[j], universum->items[i]) == 0) {
                control = 1;
                break;
            }
            tmp = universum->items[i];
        }

        if (control != 1) {
            setIncrement(complementSet, tmp);
        }
    }

    printSet(complementSet);
}

void _union(Set *setA, Set *setB) {
    Set *unionSet = setCreator();
    for (int i = 0; i < setA->cardinality; ++i) {
        setIncrement(unionSet, setA->items[i]);
    }
    printf("sad");
    printSet(unionSet);
    int control;
    char *tmp;
    for (int i = 0; i < setB->cardinality; ++i) {
        control = 0;
        tmp = NULL;
        for (int j = 0; j < setA->cardinality; ++j) {
            printf("Prvek mnoziny: %s\n", setA->items[j]);
            printf("Prvek univerza: %s\n", setB->items[i]);
            printf("STRCMP: %d\n", strcmp(setA->items[j], setB->items[i]));
            if (strcmp(setA->items[j], setB->items[i]) == 0) {
                control = 1;
                break;
            }
            tmp = setB->items[i];
        }

        if (control != 1) {
            setIncrement(unionSet, tmp);
        }
    }

    printSet(unionSet);
}

void intersect(Set *setA, Set *setB) {
    Set *intersectSet = setCreator();
    /* for (int i = 0; i < setA->cardinality; ++i) {
         setIncrement(intersectSet, setA->items[i]);
     }*/
    printSet(intersectSet);
    int control;
    char *tmp;
    for (int i = 0; i < setB->cardinality; ++i) {
        control = 0;
        tmp = NULL;
        for (int j = 0; j < setA->cardinality; ++j) {
            printf("Prvek mnoziny: %s\n", setA->items[j]);
            printf("Prvek univerza: %s\n", setB->items[i]);
            printf("STRCMP: %d\n", strcmp(setA->items[j], setB->items[i]));
            if (strcmp(setA->items[j], setB->items[i]) == 0) {
                control = 1;
                tmp = setB->items[i];
                break;
            }
        }

        if (control == 1) {
            setIncrement(intersectSet, tmp);
        }
    }

    printSet(intersectSet);
}

int minus(Set *setA, Set *setB) {
    Set *minusSet = setCreator();
    /* for (int i = 0; i < setA->cardinality; ++i) {
         setIncrement(intersectSet, setA->items[i]);
     }*/
    printSet(minusSet);
    int control;
    char *tmp;
    for (int i = 0; i < setA->cardinality; ++i) {
        control = 0;
        tmp = NULL;
        for (int j = 0; j < setB->cardinality; ++j) {
            printf("Prvek mnoziny: %s\n", setB->items[j]);
            printf("Prvek univerza: %s\n", setA->items[i]);
            printf("STRCMP: %d\n", strcmp(setB->items[j], setA->items[i]));
            if (strcmp(setB->items[j], setA->items[i]) == 0) {
                control = 1;
                break;
            }
            tmp = setA->items[i];

        }

        if (control != 1) {
            setIncrement(minusSet, tmp);
        }
    }

    printSet(minusSet);
}

bool subseteq(Set *setA, Set *setB, bool print) {
    int control = 0;
    for (int i = 0; i < setA->cardinality; ++i) {
        control = 0;
        for (int j = 0; j < setB->cardinality; ++j) {
            if (strcmp(setA->items[i], setB->items[j]) == 0) {
                control = 1;
            }
        }

        if (control == 0) {
            print ? printf("false") : 0;
            return false;
        }
    }

    print ? printf("true") : 0;

    return true;

}


bool equals(Set *setA, Set *setB, bool print) {
    if (setA->cardinality != setB->cardinality) {
        print ? printf("false") : 0;
        return false;
    }

    int control = 0;

    for (int i = 0; i < setA->cardinality; ++i) {
        control = 0;
        for (int j = 0; j < setB->cardinality; ++j) {
            if (strcmp(setA->items[i], setB->items[j]) == 0) {
                control = 1;
            }
        }

        if (control == 0) {
            print ? printf("false") : 0;
            return false;
        }
    }

    print ? printf("true") : 0;

    return true;
}

void subset(Set *setA, Set *setB) {
    if (equals(setA, setB, false)) {
        printf("false \n");
        return;
    }

    printf("%s", subseteq(setA, setB, false) ? "true" : "false");
}

void *findRelation(RelationArray *relArray, int num) {
    for (int i = 0; i < relArray->length; i++) {
        if (relArray->relations[i]->id == num) {
            return relArray->relations[i];
        }
    }
    //  return NULL;
}

void *findSet(SetArray *setArray, int num) {
    for (int i = 0; i < setArray->length; i++) {
        if (setArray->sets[i]->id == num) {
            return setArray->sets[i];
        }
    }
    //return NULL;
}

bool setContains(Set *set, char *item) {
    for (int i = 0; i < set->cardinality; ++i) {
        if (strcmp(set->items[i], item) == 0) {
            return true;
        }
    }

    return false;
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
    char *tmpStr = NULL;
    char *tmpRelItem = NULL;
    bool first = false, second = false;
    bool emptyS = false;
    char *command = NULL;
    char **cmdArgs = NULL;
    int cmdNum = 0;
    while (true) {
        c = fgetc(file);
        lineChar++;
        //printf("C: %d \n", c);
        if (lineChar == 2){
            if(type == 'S' && c == 10){
                tmpStr = realloc(tmpStr, (sequence + 1) * sizeof(char));
                if (tmpStr == NULL)
                    exit(EXIT_FAILURE);
                sequence = 0;
                *(tmpStr + sequence) = 'E';
                ++sequence;
                emptyS = true;
                c = '\n';
            } else {
                continue;
            }
            //continue;
        }
        if (type == ' ') {
            if(c == -1) break;
            if (c != 'U' && c != 'C' && c != 'R' && c != 'S') {
                printf("Unknown command %c in file %s on line %d \n", c, argv[1], lineNum + 1);
                exit(EXIT_FAILURE);
            }
            type = c;
            continue;
        }
        if (c == ' ' || c == '\n' || c == -1) {
            ++cardinality;
            sequence = 0;
            if (type == 'U') {
                setIncrement(universum, tmpStr);
            }
            if (type == 'S') {
                if(emptyS) tmpSet->cardinality = -1;
                setIncrement(tmpSet, tmpStr);
            }
            if (type == 'R') {
                if (first) {
                    tmpRelPair = malloc(sizeof(tmpStr));
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
            if (type == 'C') {
                if (command != NULL) {
                    cmdNum++;
                    cmdArgs = realloc(cmdArgs, sizeof(char *));
                    if (cmdArgs == NULL)
                        exit(EXIT_FAILURE);
                    *(cmdArgs + (cmdNum - 1)) = tmpStr;
                }
                if (command == NULL) command = tmpStr;
            }
            tmpStr = NULL;
            if (c == '\n' || c == -1) {
                lineNum++;
                lineChar = 0;
                cardinality = 0;
                emptyS = false;
                if (type == 'S') {
                    //printf("kokokokook %d\n", lineNum);
                    tmpSet->id = lineNum;
                    setArray.length++;
                    setArray.sets = realloc(setArray.sets, setArray.length * sizeof(Set *));
                    *(setArray.sets + (setArray.length - 1)) = tmpSet;
                    tmpSet = setCreator();
                }
                if (type == 'R') {
                    tmpRel->id = lineNum;
                    relArray.length++;
                    relArray.relations = realloc(relArray.relations, relArray.length * sizeof(Relation *));
                    *(relArray.relations + (relArray.length - 1)) = tmpRel;
                    tmpRel = relCreator();
                }
                if (type == 'C') {
                    int firstArg = 0, secondArg = 0, thirdArg = 0;
                    if (cmdArgs[0] != NULL) firstArg = atoi(cmdArgs[0]);
                    if (cmdArgs[1] != NULL) secondArg = atoi(cmdArgs[1]);
                    if (cmdArgs[2] != NULL) thirdArg = atoi(cmdArgs[2]);
                    printf("Command: %s Args:", command);
                    for (int i = 0; i < cmdNum; i++) {
                        printf(" %s ", cmdArgs[i]);
                    }
                    if (firstArg == 0) {
                        printf("Missing argument in file %s on line %d \n", argv[1], lineNum);
                        exit(EXIT_FAILURE);
                    }
                    printf("args: %d %d %d \n", firstArg, secondArg, thirdArg);
                    printf("\n");
                    //Relace
                    if(strcmp(command, "reflexive") == 0){isReflexive(findRelation(&relArray,firstArg), universum);}
                    if(strcmp(command, "symmetric") == 0){isSymmetric(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "antisymmetric") == 0){isAntiSymmetric(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "transitive") == 0){isTransitive(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "function") == 0){isFunction(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "domain") == 0){domain(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "codomain") == 0){codomain(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "injective") == 0){
                        if (secondArg == 0 || thirdArg == 0) {
                            printf("Missing argument in file %s on line %d \n", argv[1], lineNum);
                            exit(EXIT_FAILURE);
                        }
                        isInjective(findRelation(&relArray,firstArg), findSet(&setArray,secondArg),findSet(&setArray, thirdArg), true);}
                    if(strcmp(command, "surjective") == 0){
                        if (secondArg == 0 || thirdArg == 0) {
                            printf("Missing argument in file %s on line %d \n", argv[1], lineNum);
                            exit(EXIT_FAILURE);
                        }
                        isSurjective(findRelation(&relArray,firstArg), findSet(&setArray,secondArg),findSet(&setArray, thirdArg), true);}
                    if(strcmp(command, "bijective") == 0){
                        if (secondArg == 0 || thirdArg == 0) {
                            printf("Missing argument in file %s on line %d \n", argv[1], lineNum);
                            exit(EXIT_FAILURE);
                        }
                        isBijective(findRelation(&relArray,firstArg), findSet(&setArray,secondArg),findSet(&setArray, thirdArg));}
                    //Mnoziny
                    if (strcmp(command, "empty") == 0) { empty(findSet(&setArray, firstArg)); }
                    if (strcmp(command, "card") == 0) { card(findSet(&setArray, firstArg)); }
                    if (strcmp(command, "complement") == 0) { complement(findSet(&setArray, firstArg), universum); }
                    if (strcmp(command, "union") == 0) {
                        _union(findSet(&setArray, firstArg), findSet(&setArray, secondArg));
                    }
                    if (strcmp(command, "intersect") == 0) {
                        intersect(findSet(&setArray, firstArg), findSet(&setArray, secondArg));
                    }
                    if (strcmp(command, "minus") == 0) {
                        minus(findSet(&setArray, firstArg), findSet(&setArray, secondArg));
                    }
                    if (strcmp(command, "subseteq") == 0) {
                        subseteq(findSet(&setArray, firstArg), findSet(&setArray, secondArg), true);
                    }
                    if (strcmp(command, "subset") == 0) {
                        subset(findSet(&setArray, firstArg), findSet(&setArray, secondArg));
                    }
                    if (strcmp(command, "equals") == 0) {
                        equals(findSet(&setArray, firstArg), findSet(&setArray, secondArg), true);
                    }
                    //reset
                    command = NULL;
                    cmdNum = 0;
                    cmdArgs = NULL;
                }
                type = ' ';
                //command = NULL;
                if(c == -1){
                    if (feof(file))break;
                    break;
                }
            }
            continue;
        }
        if (type == 'R') {
            if (c == '(') {
                first = true;
                continue;
            }
            if (c == ')') {
                second = true;
                continue;
            }
        }
        tmpStr = realloc(tmpStr, (sequence + 1) * sizeof(char));
        if (tmpStr == NULL)
            exit(EXIT_FAILURE);
        *(tmpStr + sequence) = c;
        ++sequence;
    }

    //Print
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

    for (int i = 0; i < relArray.length; ++i) {
        printf("Rel %d ", relArray.relations[i]->id);
        for (int j = 0; j < relArray.relations[i]->cardinality; ++j) {
            printf("( %s ", relArray.relations[i]->items[j]->first);
            printf("%s )", relArray.relations[i]->items[j]->second);
        }
        printf("\n");
    }

    //codomain(relArray.relations[0]);
    //Memory dealoc


    for (int i = 0; i < relArray.length; ++i) {
        for (int j = 0; j < relArray.relations[i]->cardinality; ++j) {
            free(relArray.relations[i]->items[j]->first);
            free(relArray.relations[i]->items[j]->second);
            free(relArray.relations[i]->items[j]);
        }
        free(relArray.relations[i]->items);
        free(relArray.relations[i]);
    }
    free(relArray.relations);
    for(int i = 0; i < setArray.length; i++){
        for (int j = 0; j < setArray.sets[i]->cardinality; ++j) {
            free(setArray.sets[i]->items[j]);
        }
        setDestructor(setArray.sets[i]);
    }
    for(int i = 0; i < universum->cardinality; i++){
        free(universum->items[i]);
    }
    setDestructor(tmpSet);
    free(tmpSet->items);
    free(setArray.sets);
    //free(tmpSet);

   // relPairDestructor(tmpRelPair);
    relDestructor(tmpRel);
    setDestructor(universum);
    free(tmpRelPair);
    free(tmpStr);
    free(cmdArgs);
}


// Rel functions
void isReflexive(Relation *relation, Set *universum) {
    bool result = true;
    RelationPair tmpPair;
    for (int i = 0; i < universum->cardinality; ++i) {
        tmpPair.first = universum->items[i];
        tmpPair.second = universum->items[i];
        if (!containsRelationPair(relation, tmpPair)) {
            result = false;
        }
    }
    printf("%s\n", result ? "true" : "false");
}

void isSymmetric(Relation *relation) {
    bool result = true;
    RelationPair tmpPair;
    for (int i = 0; i < relation->cardinality; ++i) {
        tmpPair.first = relation->items[i]->second;
        tmpPair.second = relation->items[i]->first;
        if (strcmp(relation->items[i]->first, relation->items[i]->second) != 0) {
            if (!containsRelationPair(relation, tmpPair)) {
                result = false;
                break;
            }
        }
    }
    printf("%s", result ? "true" : "false");
}

void isAntiSymmetric(Relation *relation) {
    bool result = true;
    RelationPair tmpPair;
    for (int i = 0; i < relation->cardinality; ++i) {
        tmpPair.first = relation->items[i]->second;
        tmpPair.second = relation->items[i]->first;
        if (strcmp(relation->items[i]->first, relation->items[i]->second) != 0) {
            if (containsRelationPair(relation, tmpPair)) {
                result = false;
                break;
            }
        }
    }
    printf("%s\n", result ? "true" : "false");
}


void isTransitive(Relation *relation) {
    bool result = true;
    RelationPair tmpPair;
    for (int i = 0; i < relation->cardinality; ++i) {
        for (int j = 0; j < relation->cardinality; ++j) {
            tmpPair.first = relation->items[i]->first;
            tmpPair.second = relation->items[j]->second;
            if (strcmp(relation->items[i]->second, relation->items[j]->first) == 0) {
                if (!containsRelationPair(relation, tmpPair)) {
                    result = false;
                    break;
                }
            }
        }
    }
    printf("%s\n", result ? "true" : "false");
}

void isFunction(Relation *relation) {
    bool result = true;

    for (int i = 0; i < relation->cardinality; ++i) {
        for (int j = 0; j < relation->cardinality; ++j) {
            if (i == j) {
                continue;
            }

            if (strcmp(relation->items[i]->first, relation->items[j]->first) == 0) {
                result = false;
                break;
            }
        }
    }
    printf("%s\n", result ? "true" : "false");
}

void domain(Relation *relation) {
    Set *domain = setCreator();

    for (int i = 0; i < relation->cardinality; ++i) {
        if (!setContains(domain, relation->items[i]->first)) {
            unsigned long int length = strlen(relation->items[i]->second);
            char *newStr = malloc(length * sizeof(char));
            for (int j = 0; j < length; j++) {
                *(newStr + j) = relation->items[i]->first[j];
            }
            setIncrement(domain, newStr);
            newStr = NULL;
        }
    }

    printSet(domain);
    setDestructor(domain);
}

void codomain(Relation *relation) {
    Set *codomain = setCreator();

    for (int i = 0; i < relation->cardinality; ++i) {
        if (!setContains(codomain, relation->items[i]->second)) {
            unsigned long int length = strlen(relation->items[i]->second);
            char *newStr = malloc(length * sizeof(char));
            for (int j = 0; j < length; j++) {
                *(newStr + j) = relation->items[i]->second[j];
            }
            setIncrement(codomain, newStr);
            newStr = NULL;
        }
    }

    printSet(codomain);
    setDestructor(codomain);
}

bool isInjective(Relation *relation, Set *setA, Set *setB, bool printResult) {
    bool result = true;
    Set *codomain = setCreator();
    for (int i = 0; i < relation->cardinality; ++i) {
        if (!setContains(setA, relation->items[i]->first) || !setContains(setB, relation->items[i]->second)) {
            continue;
        }
        if (!setContains(codomain, relation->items[i]->second)) {
            unsigned long int length = strlen(relation->items[i]->second);
            char *newStr = malloc(length * sizeof(char));
            /*for (int j = 0; j < length; j++) {
                *(newStr + j) = relation->items[i]->second[j];
            } */
            strcpy(newStr, relation->items[i]->second);
            setIncrement(codomain, newStr);
            newStr = NULL;
        } else {
            result = false;
            break;
        }
    }

    setDestructor(codomain);
    if (printResult) {
        printf("%s\n", result ? "true" : "false");
    }
    return result;
}

bool isSurjective(Relation *relation, Set *setA, Set *setB, bool printResult) {
    bool result = true;

    Set *codomain = setCreator();
    for (int i = 0; i < relation->cardinality; ++i) {
        if (!setContains(setA, relation->items[i]->first) || !setContains(setB, relation->items[i]->second)) {
            continue;
        }

        if (!setContains(codomain, relation->items[i]->second)) {
            unsigned long int length = strlen(relation->items[i]->second);
            char *newStr = malloc(length * sizeof(char));
            for (int j = 0; j < length; j++) {
                *(newStr + j) = relation->items[i]->second[j];
            }
            setIncrement(codomain, newStr);
            newStr = NULL;
        } /* else {
            result = false;
            break;
        } */
    }

    result = setB->cardinality == codomain->cardinality;
    setDestructor(codomain);
    if (printResult) {
        printf("%s\n", result ? "true" : "false");
    }
    return result;
}

void isBijective(Relation *relation, Set *setA, Set *setB) {
    if (setB->cardinality != setA->cardinality) {
        printf("false\n");
        return;
    }

    bool result = isInjective(relation, setA, setB, false) && isSurjective(relation, setA, setB, false);

    printf("%s\n", result ? "true" : "false");
}

bool containsRelationPair(Relation *relation, RelationPair relationPair) {
    for (int i = 0; i < relation->cardinality; ++i) {
        if (strcmp(relation->items[i]->first, relationPair.first) == 0 &&
            strcmp(relation->items[i]->second, relationPair.second) == 0) {
            return true;
        }
    }

    return false;
};