#include "uart.h"
int main(){
    unsigned char cTestData = 'F';
    Uart_Init();
    while(1){
        PutChar(cTestData);
    }
    return 0;
}