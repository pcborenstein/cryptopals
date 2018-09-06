#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "myConversions.h"

const char in1[] = "this is a test";
const char in2[] = "wokka wokka!!!";
const char challenge1Input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
const char challengeAnswer[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

void testCode(void){
    uint32_t inLen1 = strlen(in1);
    uint32_t inLen2 = strlen(in2);

    if(inLen1 != inLen2){
        fprintf(stderr, "unequal len\n");
        exit(EXIT_FAILURE);
    }

    uint32_t i, j;
    uint32_t hammingDistance = 0;
    uint8_t diff;

    diff = 0x80;
    for(i = 0; i < inLen1; i++){
        diff = in1[i] ^ in2[i];
        for(; diff != 0; diff >>= 1)
            if(diff & 0x01 != 0)
                hammingDistance++;
    }
    printf("Hamming distance is %d\n", hammingDistance);
}

void challenge1TestCode(void){
    uint8_t * hexVals;
    uint32_t inputLen = strlen(challenge1Input);
    uint32_t numHexVals = inputLen >> 1;
    if((inputLen & 1) != 0)
        numHexVals++;
    hexVals = malloc(numHexVals);

    uint32_t numBase64Vals;
    numBase64Vals = (uint32_t)ceil(numHexVals * 4/3);
    uint8_t * base64Vals = malloc(numBase64Vals);

    hexStr2Hex(challenge1Input, hexVals, strlen(challenge1Input));
    myHexToBase64(hexVals, base64Vals, numHexVals);

    printf("%s\n", challenge1Input);
    uint32_t i;
    for(i = 0; i < numHexVals; i++)
        printf("%02x",hexVals[i]);
    printf("\n");

    printf("%s\n", challengeAnswer);
    printBase64(base64Vals, numBase64Vals);

    free(hexVals);
    free(base64Vals);

}
int main(){

    size_t lineLen = 0;
    char * linePtr = NULL;

    FILE * f = fopen("6.txt", "r");
    getline(&linePtr, &lineLen, f);

    printf("%s", linePtr);

    free(linePtr);

    return 0;
}

