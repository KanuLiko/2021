#include "uart.h"
int main(){
    unsigned char cTestData;
    // unsigned char cTestDataSpace = 32;
    Uart_Init();
    // while(1){
    //     PutChar(cTestData);
    //     PutChar(cTestDataSpace);
    //     for(int i=0;i<10000;i++);
    // }
    while(1){
        cTestData = GetChar();
        PutChar(cTestData);
    }
    return 0;
}