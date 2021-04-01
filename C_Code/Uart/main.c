#include "uart.h"
void delay(void){
    unsigned int i;
    for(i=0;i<1000;i++);
}
int main(){
    unsigned char cTestData;
    int i;
    Uart_Init();
    for(i=0;i<10;i++){
        cTestData = (unsigned char)i;
        PutChar(cTestData);
        delay();
    }
    return 0;
}