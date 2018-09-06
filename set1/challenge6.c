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

    hexStrToHex(challenge1Input, hexVals, strlen(challenge1Input));
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

    uint32_t numHexVals;
    uint32_t hexStrLen;
    uint32_t numBase64Vals;
    //site suggests checking a key length 2-40
    //doing 2-80 in case they are sneaky
    numHexVals = 80;
    hexStrLen = (numHexVals * 2) + 1;
    numBase64Vals = (uint32_t)ceil((float)numHexVals * 4/3);

    char * hexStr = malloc(hexStrLen);
    hexStr[hexStrLen - 1] = 0;
    uint8_t * hexVals = malloc(numHexVals);
    uint8_t * base64Vals = malloc(numBase64Vals);
    uint8_t * base64ValsStr = malloc(numBase64Vals);

    printf("caputing %d base64 characters to form %d hex values\n", numBase64Vals, numHexVals);
    uint32_t i, lineIndex;
    getline(&linePtr, &lineLen, f);
    printf("\nline: %s\n", linePtr);
    lineIndex = 0;
    printf("%d numBase64Vals\n", numBase64Vals);
    for(i = 0; i < numBase64Vals; i++){
        while(linePtr[lineIndex] == '\n'){
            free(linePtr);
            getline(&linePtr, &lineLen, f);
            lineIndex = 0;
            printf("line: %s\n", linePtr);
        }
        base64ValsStr[i] = linePtr[lineIndex];
        lineIndex++;
    }

    base64StrToBase64(base64ValsStr, base64Vals, numBase64Vals);
    printBase64(base64Vals, numBase64Vals);
    hexVals[numBase64Vals - 1] = 0xff;
    hexVals[70] = 0xaa;
    myBase64toHex(base64Vals, hexVals, numBase64Vals);

    for(i = 0; i < numHexVals; i++)
        printf("%02x",hexVals[i]);
    printf("\n");
    //myHexToBase64(hexVals, base64Vals, numHexVals);

    free(hexVals);
    free(hexStr);
    free(base64Vals);
    free(base64ValsStr);
    free(linePtr);

    return 0;
}

