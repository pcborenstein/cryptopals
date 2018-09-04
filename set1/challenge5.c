#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const char inputStr[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
const char key[] = "ICE";
const char answer[] = { 0x0b, 0x36, 0x37, 0x27, 0x2a, 0x2b, 0x2e, 0x63, 0x62, 0x2c, 0x2e, 0x69, 0x69, 0x2a, 0x23, 0x69, 0x3a, 0x2a, 0x3c, 0x63, 0x24, 0x20, 0x2d, 0x62, 0x3d, 0x63, 0x34, 0x3c, 0x2a, 0x26, 0x22, 0x63, 0x24, 0x27, 0x27, 0x65, 0x27, 0x2a, 0x28, 0x2b, 0x2f, 0x20, 0x43, 0x0a, 0x65, 0x2e, 0x2c, 0x65, 0x2a, 0x31, 0x24, 0x33, 0x3a, 0x65, 0x3e, 0x2b, 0x20, 0x27, 0x63, 0x0c, 0x69, 0x2b, 0x20, 0x28, 0x31, 0x65, 0x28, 0x63, 0x26, 0x30, 0x2e, 0x27, 0x28, 0x2f, };


int main(void){

    uint16_t keyLen = strlen(key);
    uint16_t inputLen = strlen(inputStr);

    char * outputStr = malloc(inputLen + 1);
    outputStr[keyLen] = 0;

    uint16_t i, j, m;

    for(i = 0; i < inputLen; i += keyLen){
        j = i;
        m = 0;
        while((j < inputLen) && (m < 3)){
            //printf("%2d, %2d, %c, %c, %02x\n", j + 1, i + m + 1, key[m], inputStr[j], inputStr[i + m] ^ key[m]);
            //fflush(stdout);
            outputStr[i + m] = inputStr[i + m] ^ key[m];
            m++;
            j++;
        }
    }

    int wrong = 0;
    for(i = 0; i < inputLen; i++){
        printf("%02x", outputStr[i] & 0xff);
        if((wrong == 0) && (outputStr[i] != answer[i])){
            printf("\nerror found in %dth char\n", i+1);
            printf("oringinally '%c' or %02x\n", inputStr[i],inputStr[i] & 0xff);
            printf("should be %02x\n", answer[i]);
            wrong = 1;
        }
    }
    printf("\n");
    if(wrong == 0)
        printf("great success\n");

    return 0;

}






