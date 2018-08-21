#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <myConversions.h>

const char inputStr[] = "1c0111001f010100061a024b53535009181c";
const char xorStr[] = "686974207468652062756c6c277320657965";
const char ans[] = "746865206b696420646f6e277420706c6179";

int main(){

    int inputLen = strlen(inputStr);
    int xorLen = strlen(xorStr);
    if(inputLen != xorLen){
        fprintf(stderr, "length missmatch in main\n");
        exit(EXIT_FAILURE);
    }

    uint8_t * inputBytes = malloc(inputLen);
    uint8_t * xorBytes = malloc(inputLen);

    myStr2Bytes(inputStr, inputBytes, inputLen);
    myStr2Bytes(xorStr, xorBytes, inputLen);

    int i;
    printf("my attempt:\n");
    for(i = 0; i < inputLen; i++)
        printf("%x", inputBytes[i] ^ xorBytes[i]);

    printf("\n");
    printf("%s\n", ans);

    printf("^website answer^:\n");

    return 0;
}
