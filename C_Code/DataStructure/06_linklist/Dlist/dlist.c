#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include "Dlist.h"

void dlist_init(stDlistHead *dlist){
    dlist->size = 0;
    dlist->head = NULL;
    dlist->tail = NULL;
    return ;
}

void dlist_destroy(stDlistHead *dlist){
    stDlistNode *pNode = NULL;
    while(dlist->size>0){
        pNode = dlist->head;
        dlist->head = dlist->head->next;
        free(pNode);
        dlist->size--;
    }
    memset(dlist, 0, sizeof(stDlistHead));
    return ;
}

int dlist_insert_head(stDlistHead *dlist, stDlistNode *pNode, int data){
    if(pNode == NULL){ //只传递一个数据时
        pNode = (stDlistNode*)malloc(sizeof(stDlistNode));
        if(pNode == NULL){
            return -1;
        }
    }

    pNode->data = data;
    pNode->prev = NULL;
    pNode->next = NULL;

    if(dlist->size == 0){ //链表是空链表的情形
        dlist->head = pNode;
        dlist->tail = pNode;
    }else{//链表是非空的情形
        pNode->next = dlist->head;
        dlist->head->prev = pNode;
        dlist->head = pNode;
    }
    dlist->size++;
    return 0;
}

stDlistNode * dlist_remove_tail(stDlistHead *dlist){
    stDlistNode *pNode = NULL;
    if(dlist->size == 0){
        return NULL;
    }
    pNode = dlist->tail;
    if(dlist->size>1){
        dlist->tail = dlist->tail->prev;
        dlist->tail->next = NULL;
    }else{
        dlist->head = NULL;
        dlist->tail = NULL;
    }
    dlist->size--;
    return pNode;
}

void dlist_remove_node(stDlistHead* dlist, stDlistNode* pNode){
    if((dlist == NULL) || (pNode == NULL)){
        return ;
    }
    if(dlist->head == pNode){
        dlist->head = dlist->head->prev;
    }else if(dlist->tail == pNode){
        dlist->tail = pNode->prev;
        dlist->tail->next = NULL;
    }else{
        pNode->prev->next = pNode->next;
        pNode->next->prev = pNode->prev;
    }
    dlist->size--;
    pNode->prev = NULL;
    pNode->next = NULL;
    if(dlist->size == 0){
        memset(dlist, 0, sizeof(stDlistHead));
    }
    return ;
}

stDlistNode* dlist_search(stDlistHead *dlist, int data){
    stDlistNode* pNode = dlist->head;
    while(pNode->next != NULL){
        if(pNode->data == data){
            return pNode;
        }
        pNode= pNode->next;
    }
    return NULL;
}

void dlist_dump(stDlistHead* dlist){
    int no = 0;
    stDlistNode* pNode = dlist->head;
    while(pNode->next != NULL){
        printf("\r\n [%d] = %d", no++, pNode->data);
        pNode = pNode->next;
    }
    return ;
}

void Lru_dlist(stDlistHead* dlist, int data){
    stDlistNode* pNode = NULL;
    pNode = dlist_search(dlist, data);
    if(pNode != NULL){
        dlist_remove_node(dlist, pNode);
    }else if(dlist->size >= 4){
        pNode = dlist_remove_tail(dlist);
    }
    dlist_insert_head(dlist, pNode, data);
    return ;
}
