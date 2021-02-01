#include <stdarg.h>
#include "itoa.h"
#include <stdio.h>
#define write32(v, a) (*(volatile unsigned int *)(a) = (v))
#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & (sizeof(int) - 1))
void print_bin(int n)
{
    int l = sizeof(n) * 8;
    int i;
    if (i == 0)
    {
        printf("0");
        return;
    }
    for (i = l - 1; i >= 0; i--)
    {
        if (n & (1 << i))
            break;
    }
    for (; i >= 0; i--)
        printf("%d", (n & (1 << i)) != 0);
}
int main(int args, const char **argv)
{
    // char *a = NULL;
    // char str[32];
    // printf("%d",_INTSIZEOF(a));
    int a = 13;
    int b = 21;
    char *buf1;
    char *buf2;
    char *str;
    printf("hello world!\n");
    printf("%s\n", itoa(buf1, a));
    /*
    printf("%s\n", itoa(1u<<a,str,2));
    printf("%s\n",itoa(24,str,2));
    write32(1|58,&a);
    printf("%s\n",itoa(a,str,2));
    */
    return 0;
}