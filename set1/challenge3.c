#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const char inputStr[] = {0x1b, 0x37, 0x37, 0x33, 0x31, 0x36, 0x3f, 0x78, 0x15, 0x1b, 0x7f, 0x2b, 0x78, 0x34, 0x31, 0x33, 0x3d, 0x78, 0x39, 0x78, 0x28, 0x37, 0x2d, 0x36, 0x3c, 0x78, 0x37, 0x3e, 0x78, 0x3a, 0x39, 0x3b, 0x37, 0x36, 0};

int main(){

    uint8_t count[0xff];
    memset(count, 0, 0xff);
    //find the most common letter
    int inputLen = strlen(inputStr);
    int i, j;
    int maxIndex;
    maxIndex = 0;

    for(i = 0; i < inputLen; i++){
        uint8_t thisChar = inputStr[i];
        count[thisChar]++;
        if(count[thisChar] > count[maxIndex])
            maxIndex = thisChar;
    }

    printf("the most common character is %d\n", maxIndex);

    //options for most common letters
    const char attempts[] = "ETAOIN SHRDLU";
    uint8_t key;
    for(i = 0; i < strlen(attempts); i++){
        key = maxIndex ^ attempts[i];
        printf("Trying for common character '%c'. Key is %2x\n", attempts[i], key & 0xff);
        for(j = 0; j < inputLen; j++)
            printf("%c", inputStr[j] ^ key);
        printf("\n");
    }

    return 0;
}





