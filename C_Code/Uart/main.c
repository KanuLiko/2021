#include "uart.h"
int main(){
    unsigned char cTestData = 'F';
    unsigned char cTestDataSpace = 36;
    Uart_Init();
    while(1){
        PutChar(cTestData);
        PutChar(cTestDataSpace);
        for(int i=0;i<100;i++);
    }
    return 0;
}