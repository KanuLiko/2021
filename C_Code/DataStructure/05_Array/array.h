#ifndef _ARRAY_H_
#define _ARRAY_H_

struct array{
    int size;
    int used;
    int *arr;
};

void dump(struct array *array);
void alloc(struct array *array);
int insert(struct array *array, int elem);
int delete_array(struct array *array, int idx);
int search(struct array *array, int elem);

#endif