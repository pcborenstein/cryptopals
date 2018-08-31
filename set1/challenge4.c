#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(){

    FILE * f = fopen("4.txt", "r");

    size_t lineMax = 500;
    char * line = malloc(lineMax);

    char inputStr[61];

    int i, j, m;
    int maxIndex;
    uint8_t count[0xff];
    uint8_t key;
    m = 0;
    while(getline(&line, &lineMax, f) != -1){
        m++;
        //put the hex bytes into a C string
        j = 0;
        uint8_t byteValue;
        //convert the hex characters to a string
        memset(inputStr, 0, 61);
        for(i = 0; i < 60; i++){
            if((line[i] >= '0') && (line[i] <= '9'))
                byteValue = line[i] - '0';
            else if((line[i] >= 'a') && (line[i] <= 'f'))
                byteValue = line[i] - 'a' + 10;
            else if(line[i] == 10)
                break;
            else{
                fprintf(stderr, "bad input on line %d: %d\n", m, line[i]);
                exit(EXIT_FAILURE);
            }
            if((i % 2) == 0)
                inputStr[j] = (byteValue << 4) & 0xf0;
            else{
                inputStr[j] |= byteValue & 0x0f;
                j++;
            }
        }

        memset(count, 0, 0xff);

        uint8_t thisChar;
        maxIndex = 0;
        for(i = 0; i < 30; i++){
            thisChar = inputStr[i];
            count[thisChar]++;
            if(count[thisChar] > count[maxIndex])
                maxIndex = thisChar;
        }
        //skipp if no characters are repeated
        if(count[maxIndex] == 1)
            continue;
        //I assume the most common character will be space ' '
        key = maxIndex ^ ' ';
        //break if we get some bad characters
        uint8_t decodedByte;
        for(i = 0; i < 30; i++){
             decodedByte = key ^ inputStr[i];
            if((decodedByte < '0' || decodedByte > '9') &&
            (decodedByte < 'a' || decodedByte > 'z') &&
            (decodedByte < 'A' || decodedByte > 'Z') &&
            decodedByte != ' ' &&
            decodedByte != '\n')
                break;
        }

        if(i != 30){
            continue;
        }
        printf("key is %2x line %d\n", key &0xff, m);
        for(i = 0; i < 30; i++){
            printf("%c", inputStr[i] ^ key);
        }
        printf("\n");
    }

    return 0;
}

