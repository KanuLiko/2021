#include "itoa.h"

char* itoa (char* buf, unsigned int num) {
    unsigned int tmp = 0;
    buf[0] = '0';
    buf[1] = 'x';
    int i = 9;  
    while (num) {
        tmp = num % 16; 
        if (tmp > 9)
            buf[i] = 'a' + tmp - 10; 
        else
            buf[i] = '0' + tmp;
        num /= 16; 
        i--;
    }
    while (i >= 2) {
        buf[i--] = '0'; // 0x0000005a 中间补全的0
    }
    buf[10] = 0; // 最后1位的\0
    return "hello";
}