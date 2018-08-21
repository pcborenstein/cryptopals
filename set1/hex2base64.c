#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

const char input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
const char output[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
const char base64[64 + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

int main(){
    //first conver the input string to byte values
    int inputLen = strlen(input);
    uint8_t * inputBytes = malloc(inputLen);
    int i;
    for(i = 0; i < inputLen; i++){
        if((input[i] >='0') && (input[i] <='9'))
            inputBytes[i] = input[i] - '0';
        else if((input[i] >='a') && (input[i] <='f'))
            inputBytes[i] = input[i] - 'a' + 10;
        else{
            fprintf(stderr, "invalid input #%d: %c\n",i, input[i]);
            exit(EXIT_FAILURE);
        }
    }

    //need 1 6-bit outputs per 1.5  4-bit inputs
    int outLen = ceil(inputLen * 2 / 3);
    //need 2 bytes to store a 6-bit 64 base number
    uint16_t * outputBytes = malloc(outLen * sizeof(uint16_t));

    for(i = 0; i < outLen; i++){
        uint16_t part1, part2;
        if(i % 2 == 0){
            part1 = inputBytes[(int)i*3/2];
            part2 = inputBytes[(int)i*3/2 + 1];
            outputBytes[i] = ((part1 << 2) & 0x3C) | ((part2 >>2) & 0x3);
            //printf("considering bytes %x and %x\n", part1, part2);
            //printf("considering bytes %x and %x\n", 1, ((part2 >>2) & 0x3));
        }else{
            part1 = inputBytes[(int)i*3/2];
            part2 = inputBytes[(int)i*3/2 + 1];
            outputBytes[i] = ((part1 << 4) & 0x30) | (part2 & 0xf);
        }
    }


    printf("my output:\n");
    for(i = 0; i < outLen; i++){
        printf("%c", base64[outputBytes[i]]);
    }

    printf("\n");
    for(i = 0; i < outLen; i++){
        printf("%c", output[i]);
    }

    printf("\n");
    printf("^answer from website^\n");

    free(inputBytes);

    return 0;
}


