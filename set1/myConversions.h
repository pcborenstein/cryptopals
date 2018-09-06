#if !defined(MY_CONVERSIONS_H)
#define MY_CONVERSIONS_H

#include <stdint.h>

extern void myStr2Bytes(const char * inputStr, uint8_t * buff, int len);

//this function requires the buffer be 0.75 of the input length
extern void myBase64toHex(const char * inputStr, uint8_t * buff, int inputLen);

extern void myHexToBase64(const uint8_t * input, uint8_t * buff, int inputLen);

extern void hexStrToHex(const char * inputStr, uint8_t * buff, uint32_t inputLen);

extern void base64StrToBase64(const char * inputStr, uint8_t * buff, uint32_t inputLen);

extern void printBase64(const uint8_t * buff, const uint32_t len);

extern void testPrint(void);

#endif
