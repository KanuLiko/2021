#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define shift(a) a*8
#define ans_mask(a) (0x80<<shift(a))
void hex2bin(unsigned int a){
    int res;
    int i=0;
    char buf[BUFSIZ][5] = {"0000"};
    char reference[16][5] = {
        "0000","0001","0010","0011",\
        "0100","0101","0110","0111",\
        "1000","1001","1010","1011",\
        "1100","1101","1110","1111"
    };
    while(a/16!=0){
        res = a%16;
        strcpy(buf[i++],reference[res]);
        a /= 16;
    }
    res = a % 16;
    strcpy(buf[i++],reference[res]);
    printf("16进制表示:0x%x\n",a);
    printf("2进制表示:");
    while (i>0)
    {  
       printf("%s",buf[--i]);
       if(i>0){
           printf(",");
       }
    }
}
int main(int argc,char *argv[]){
    int a = 1;
    unsigned int value = 0x00000000;
    value |= ans_mask(a);
    hex2bin(value);
    return 0;
}