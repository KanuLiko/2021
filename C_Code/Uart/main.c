#include "uart.h"

int main(){

    unsigned char cTestData;

    Uart_Init();

    PutStr("Hello, world!\n\r");

    while(1){

        cTestData = GetChar();

        if(cTestData=='\n')

            PutChar('\n');

        if(cTestData == '\r')

            PutChar('\r');

        PutChar(cTestData);

    }
    
    return 0;
}