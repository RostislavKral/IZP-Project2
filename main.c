#include <stdio.h>
#include <malloc.h>

typedef struct {
    int cardinality;
    char **items;
} setTest;
int main(int argc, char **argv) {

    FILE *file = fopen("../test.txt", "r");

    int sequence = 0;
    char *tmpStr = malloc(1);
    setTest set;
    char c;
    set.cardinality = 0;
    set.items = malloc(0);
    while(1) {
        c = fgetc(file);
        if( feof(file) ) {
            break ;
        }


        if (c == ' ' || c == '\n') {
            printf("\n*%s*\n", tmpStr);
            ++set.cardinality;
            set.items = realloc(set.items, set.cardinality * sizeof(char*));

            *(set.items + (set.cardinality - 1)) = tmpStr;

            sequence = 0;
            tmpStr = NULL;
        }
        else {
            tmpStr = realloc(tmpStr, (sequence + 1) * sizeof(char));
            *(tmpStr + sequence) = c;

            ++sequence;
        }
    }

    for (int i = 0; i < set.cardinality; ++i) {
        printf("%s\n", set.items[i]);
    }
    return 0;
}
