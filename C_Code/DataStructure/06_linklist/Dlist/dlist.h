#ifndef _DLIST_H_
#define _DLIST_H_
#include<stdio.h>

typedef struct DlistNode
{
    struct DlistNode *prev;
    struct DlistNode *next;
    int data;
}stDlistNode;

typedef struct Dlisthead
{
    int size;
    stDlistNode *head;
    stDlistNode *tail;
}stDlistHead;

void dlist_init(stDlistHead *dlist);
void dlist_destroy(stDlistHead *dlist);
int dlist_insert_head(stDlistHead *dlist, stDlistNode *pNode, int data);
stDlistNode * dlist_remove_tail(stDlistHead *dlist);
void dlist_remove_node(stDlistHead* dlist, stDlistNode* pNode);
stDlistNode* dlist_search(stDlistHead *dlist, int data);
void dlist_dump(stDlistHead* dlist);
void Lru_dlist(stDlistHead* dlist, int data);

#endif