#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"array.h"

int main(int argc,char *argv[]){
    int idx;
    struct array ten_int = {10,0,NULL};
    alloc(&ten_int);
    if(!ten_int.arr)
        return -1;
    insert(&ten_int,1);
    insert(&ten_int,3);
    insert(&ten_int,2);
    printf("===>insert 1,3,2\n");
    dump(&ten_int);

    idx = search(&ten_int,2);
    printf("2 is at position %d\n",idx);
    idx = search(&ten_int,3);
    printf("3 is at position %d\n",idx);

    printf("===>del [6] element\n");
    delete_array(&ten_int,6);
    dump(&ten_int);
    printf("==>del [0] element\n");
    delete_array(&ten_int,0);
    dump(&ten_int);
    return 0;    
}