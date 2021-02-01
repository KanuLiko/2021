#include <stdio.h>
#include <stdlib.h>
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
    int a = 8;
    printf("the answer is %d",a);
    return 0;
}