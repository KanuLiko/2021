#include "uart.h"
int main(){
    unsigned char cTestData;
    Uart_Init();
    while(1){
        cTestData = GetChar();
        PutChar(cTestData)   ;
    }
    return 0;
}
/*
    unsigned char cTestDataSpace = 32;
    while(1){
        PutChar(cTestData);
        PutChar(cTestDataSpace);
        for(int i=0;i<10000;i++);
    }
*/