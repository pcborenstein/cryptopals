#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <myConversions.h>

const char input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
const char output[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
const char base64[64 + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void testPrint(void){
    printf("hello world\n");
}

void myStr2Bytes(const char * inputStr, uint8_t * buff, int len){

    int inputLen = strlen(inputStr);

    if(inputLen != len){
        fprintf(stderr, "myStr2Bytes was given a bad length. Expected %d, got %d\n", len, inputLen);
        return;
    }

    int i;
    for(i = 0; i < inputLen; i++){
        if((inputStr[i] >='0') && (inputStr[i] <='9'))
            buff[i] = inputStr[i] - '0';
        else if((inputStr[i] >='a') && (inputStr[i] <='f'))
            buff[i] = inputStr[i] - 'a' + 10;
        else{
            fprintf(stderr, "invalid input #%d: %c\n",i, input[i]);
            exit(EXIT_FAILURE);
        }
    }
}

/*
    convert 00123456|00abcdef|00123456|00abcdef
    to      123456ab|cdef1234|56abcedf|XXXXXXXX
   */
void myBase64toHex(const uint8_t * inputStr, uint8_t * buff, int inputLen){
    uint32_t i, j, offset;
    uint32_t index;
    for(i = 0, j = 0, offset = 0; (i+offset) < inputLen; i++, j++){
        index = i + offset;
        if((i % 3) == 0){
            buff[j] = (inputStr[index] << 2) & 0xfc;
            if(index < (inputLen + 1))
                buff[j] |= (inputStr[index + 1] >> 4) & 0x3;
        }else if((i %3) == 1){
            buff[j] = (inputStr[index] << 4) & 0xf0;
            if(index < (inputLen + 1))
                buff[j] |= (inputStr[index + 1] >> 2) & 0x0f;
        }else{
            buff[j] = (inputStr[index] << 6) & 0xc0;
            if(index < (inputLen + 1)){
                buff[j] |= inputStr[index + 1] & 0x3f;
                offset++;
            }
        }
    }
}


void base64StrToBase64(const char * inputStr, uint8_t * buff, uint32_t inputLen){
    uint32_t i, j;
    for(i = 0; i < inputLen; i++){
        for(j = 0; j < 64; j++){
            if(inputStr[i] == base64[j]){
                buff[i] = j;
                break;
            }
        }
        if(j == 64){
            fflush(stdout);
            fprintf(stderr, "bad base64 character: %d = %c\n", inputStr[i], inputStr[i]);
            exit(EXIT_FAILURE);
        }
    }
}

/*
    convert "1234abcd"
    to      0x12|0x34|0xab|0xcd
   */
void hexStrToHex(const char * inputStr, uint8_t * buff, uint32_t inputLen){
    uint32_t i, j;
    uint8_t numVal;
    j = 0;
    for(i = 0; i < inputLen; i++){
        printf("%c|%d|", inputStr[i], inputStr[i]);
        if((input[i] >='0') && (input[i] <='9'))
            numVal = input[i] - '0';
        else if((input[i] >='a') && (input[i] <='f'))
            numVal = input[i] - 'a' + 10;
        else{
            fflush(stdout);
            fprintf(stderr, "\ninvalid input %d: %d = '%c'\n",i, input[i], input[i]);
            exit(EXIT_FAILURE);
        }
        if((i%2) == 0)
            buff[j] = (numVal << 4) & 0xf0;
        else{
            buff[j] |= numVal & 0x0f;
            j++;
        }
    }
}

void printBase64(const uint8_t * buff, const uint32_t len){
    uint32_t i, j;
    for(i = 0; i < len; i++, j++){
        if(buff[i] > 0x3f){
            fprintf(stderr, "invalid base 64 value %d\n", buff[i]);
            exit(EXIT_FAILURE);
        }
        printf("%c",base64[buff[i]]);
    }
    printf("\n");

}

/*
    convert 12345678|abcdefgh|12345678|XXXXXXXX
    to      00123456|0078abcd|00efgh12|00345678
   */
void myHexToBase64(const uint8_t * input, uint8_t * buff, int inputLen){

    if((inputLen & 0x01) != 0){
        fprintf(stderr, "input needs to be an even number of hex bytes");
        exit(EXIT_FAILURE);
    }

    uint32_t i, j;

    for(i = 0, j = 0; i < inputLen; i++, j++){
        uint16_t part1, part2;
        if(i % 3 == 0){
            buff[j] = (input[i] >> 2) & 0x3f;
        }else if((i % 3) == 1){
            buff[j] = (input[i - 1] << 4) & 0x30;
            buff[j] |= (input[i] >> 4) & 0x0f;
        }else{
            buff[j] = (input[i - 1] << 2) & 0x3C;
            buff[j] |= (input[i] >> 6) & 0x03;
            j++;
            buff[j] = input[i] & 0x3f;
        }
    }
}


