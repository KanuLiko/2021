#include "uart.h"
void delay(void){
    unsigned int i;
    for(i=0;i<1000;i++);
}
int main(){
    unsigned char cTestData = "F";
    Uart_Init();
    while(1){
        PutChar(cTestData);
        PutChar(" ");
        delay();
    }
    return 0;
}