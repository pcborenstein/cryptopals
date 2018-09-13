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

uint32_t hammingDiff(const uint8_t * a1, const uint8_t * a2, uint32_t len){
    uint32_t j, hammingDistance;
    uint8_t diff;

    hammingDistance = 0;
    for(j = 0; j < len; j++){
        diff = a1[j] ^ a2[j];
        for(; diff != 0; diff >>= 1){
            if(diff & 0x01 != 0){
                hammingDistance++;
            }
        }
    }
    return hammingDistance;
}

void testCode(void){
    uint32_t inLen1 = strlen(in1);
    uint32_t inLen2 = strlen(in2);

    if(inLen1 != inLen2){
        fprintf(stderr, "unequal len\n");
        exit(EXIT_FAILURE);
    }

    uint32_t i, j;
    uint32_t hammingDistance;

    hammingDistance = hammingDiff(in1, in2, strlen(in1));

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

    //testCode();

    size_t lineLen = 0;
    char * linePtr = NULL;
    uint32_t i, j, lineIndex;
    long fileSize;
    FILE * f = fopen("6.txt", "rb");

    if(f == NULL){
        fprintf(stderr, "input file not found\n");
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);
    printf("the file is %ld characters long\n", fileSize);

    uint8_t * base64ValsStr = malloc(fileSize);
    uint8_t * base64Vals;
    uint8_t * hexVals;

    uint32_t numHexVals;
    uint32_t numBase64Vals;

    linePtr = NULL;
    lineLen = 0;
    getline(&linePtr, &lineLen, f);
    lineIndex = 0;
    ssize_t charsRead;
    for(i = 0;; i++){
        while(linePtr[lineIndex] == '\n'){
            free(linePtr);
            linePtr = NULL;
            lineLen = 0;
            charsRead = getline(&linePtr, &lineLen, f);
            if(charsRead == -1)
                break;
            lineIndex = 0;
        }
        if(charsRead == -1)
            break;
        //the file ends with a '=' which is not a base 64 character
        if(isBase64(linePtr[lineIndex]) == 0){
            free(linePtr);
            break;
        }
        base64ValsStr[i] = linePtr[lineIndex];
        lineIndex++;
    }
    numBase64Vals = i;
    numHexVals = (uint32_t)ceil((float)numBase64Vals * 3 / 4);

    base64Vals = malloc(numBase64Vals);
    hexVals = malloc(numHexVals);

    printf("caputing %d base64 characters to form %d hex values\n", numBase64Vals, numHexVals);

    base64StrToBase64(base64ValsStr, base64Vals, numBase64Vals);
    hexVals[numBase64Vals - 1] = 0xff;
    hexVals[70] = 0xaa;
    myBase64toHex(base64Vals, hexVals, numBase64Vals);

    for(i = 0; i < 120; i++)
        printf("%02x",hexVals[i]);
    printf("\n");
    //myHexToBase64(hexVals, base64Vals, numHexVals);
    uint8_t * a1, * a2;
    uint8_t diff;
    uint32_t hammingDistance[81];
    float averageHam[81];
    uint32_t maxHam = 0;
    uint32_t bytesChecked = 0;
    a1 = malloc(80);
    a2 = malloc(80);

    memset(hammingDistance, 0, sizeof(hammingDistance));
    averageHam[maxHam] = 0x7fffffff;

    for(i = 2; i < 40; i++){
        bytesChecked = 0;
        for(j = 0; j < numHexVals; j += i){
            memcpy(a1, &hexVals[j], i);
            memcpy(a2, &hexVals[i + j], i);

            hammingDistance[i] += hammingDiff(a1, a2, i);
            bytesChecked += i;
        }
        averageHam[i] = (float)hammingDistance[i] / (float)bytesChecked;
        if(averageHam[i] < averageHam[maxHam])
            maxHam = i;
    }
    printf("minimum hamming distance with key length %d\n", maxHam);

    uint32_t keyLen = maxHam;

    free(hexVals);
    free(base64Vals);
    free(base64ValsStr);
    free(a1);
    free(a2);

    return 0;
}

//Terminator X: Bring the noise
