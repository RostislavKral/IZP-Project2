#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
    int cardinality;
    char **items;
} Set;
typedef struct {
    char *first;
    char *second;
} RelationPair;
typedef struct {
    int length;
    Set **sets;
} SetArray;
typedef struct {
    int cardinality;
    RelationPair **items;
} Relation;

Set *set_construct() {
    Set *set = malloc(sizeof(Set));
    set->cardinality = 0;
    set->items = NULL;
    return set;
};
void set_add(Set *set, char *item){
    ++(set->cardinality);
    printf("item %s, card %d\n", item, set->cardinality);
    set->items = realloc(set->items, set->cardinality * sizeof(char*));

    *(set->items + (set->cardinality - 1)) = item;
}
int main(int argc, char **argv) {

    FILE *file = fopen(argv[1], "r");

    // printf("%d\n", sizeof(Set));
    int sequence = 0;
    char *tmpStr = NULL;
    Set *universum;
    universum = set_construct();
    // printf("card %d", universum->cardinality);
    char c;
    int line=1, wordLineCount = 0;
    char type;
    SetArray setArray;
    setArray.length = 0;
    setArray.sets = NULL;

    Set *tmpSet;

    /* set.cardinality = 0;
    set.items = malloc(0); */
    while(1) {
        c = fgetc(file);
        if( feof(file) ) {
            break ;
        }


        if (c == ' ' || c == '\n') {
            wordLineCount++;
            printf("\n*%s* %d line, wordCount %d\n", tmpStr, line, wordLineCount);
            // printf("%d line, wordCount %d, string %s, char %d\n", line,wordLineCount,tmpStr, c);

            /* if (line == 1 && wordLineCount == 1 && strcmp(tmpStr, "U") != 0) {
                printf("chybi universum");
                exit(1);
            } */
            if (line == 1 && wordLineCount != 1) {
                //printf("pred add asdf %s\n", tmpStr);
                set_add(universum, tmpStr);
            }
            if (line > 1) {
                if (wordLineCount == 1) {
                    printf("type %c\n", tmpStr[0]);
                    type = tmpStr[0];

                    if (type == 'S') {
                        tmpSet = set_construct();
                    }

                } else {
                    if (type == 'S') {
                        set_add(tmpSet, tmpStr);
                    }
                }
            }
            /*++set.cardinality;
            set.items = realloc(set.items, set.cardinality * sizeof(char*));

            *(set.items + (set.cardinality - 1)) = tmpStr;*/

            if (c == '\n') {
                if (type == 'S') {
                    setArray.length++;
                    setArray.sets = realloc(setArray.sets, setArray.length * sizeof(Set*));

                    printf("tmp card %d", tmpSet->cardinality);
                    *(setArray.sets + (setArray.length - 1)) = tmpSet;

                }
                wordLineCount = 0;
                line++;
            }
            sequence = 0;
            tmpStr = NULL;
        }
        else {
            tmpStr = realloc(tmpStr, (sequence + 1) * sizeof(char));
            *(tmpStr + sequence) = c;

            ++sequence;
        }
    }

    for (int i = 0; i < universum->cardinality; ++i) {
        printf("%s\n", universum->items[i]);
    }

    // printf("%d\n", setArray.length);
    for (int i = 0; i < setArray.length; ++i) {
        printf("set (");
        for (int j = 0; j < setArray.sets[i]->cardinality; ++j) {
            printf(" %s ", setArray.sets[i]->items[j]);
        }
        printf(")\n");
    }
    return 0;
}
