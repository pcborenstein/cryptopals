#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){

    FILE * f = fopen("4.txt", "r");

    size_t lineMax = 500;
    char * line = malloc(lineMax);

    int i, j;
    int maxCount;
    uint8_t count[0xff];
    uint8_t key;
    while(getline(&line, &lineMax, f) != -1){
        memset(count, 0, 0xff);

        printf("%s",line);
    }

    return 0;
}

