#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "array.h"

void dump(struct array *array){
    int idx;
    for(idx = 0; idx < array->used;idx++){
        printf("[%02d]:%08d\n",idx,array->arr[idx]);
    }
}

void alloc(struct array *array){
    array->arr = (int *)malloc(array->size*sizeof(int));
}

int insert(struct array *array, int elem){
    int idx;
    if(array->used >= array->size)
        return -1;
    for(idx=0;idx<array->used;idx++){
        if(array->arr[idx]>elem)
            break;
    }
    if(idx<array->used)
        memmove(&array->arr[idx+1],&array->arr[idx],\
        (array->used-idx)*sizeof(int));
    array->arr[idx] = elem;
    array->used ++ ;
    return idx;
}

int delete_array(struct array *array,int idx){
    if(idx<0||idx>=array->used)
        return -1;
    memmove(&array->arr[idx],&array->arr[idx+1],\
    (array->used-idx-1)*sizeof(int));
    array->used -- ;
    return 0;
}

int search(struct array *array, int elem){
    int idx;
    for(idx = 0;idx <array->used;idx++){
        if(array->arr[idx] == elem)
            return idx;
        if(array->arr[idx]>elem)
            return -1;
    }
    return -1;
}