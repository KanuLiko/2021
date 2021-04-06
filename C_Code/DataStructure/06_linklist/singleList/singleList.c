#include<string.h>
#include"singleList.h"

linkedList *listCreate(){
    linkedList *list = NULL;
    list = malloc(sizeof(*list));
    if(NULL == list){
        return NULL;
    }
    list->dup = NULL;
    list->free = NULL;
    list->match = NULL;
    
    list->head = NULL;
    list->len = 0;
    return list;
}

void listRelease(linkedList *list){
    if(NULL == list)
        return ;

    listEmpty(list);

    free(list);
    list = NULL;
}

void listEmpty(linkedList *list){
    if(list==NULL)
        return;
    while(list->head!=NULL){
        listNode *pNode = list->head;
        list->head = pNode->next;
        if(list->free!=NULL)
            list->free(pNode->value);
        else
            free(pNode->value);
        pNode->next = NULL;
        free(pNode);
        pNode = NULL;
    }
}

linkedList *listAddNodeHead(linkedList *list,void *value){
    if(list == NULL || value == NULL)
        return list;
    listNode *node = NULL;
    node = malloc(sizeof(*node));
    if(node == NULL)
        return list;
    node->value = value;
    node->next = list->head;
    list->head = node;
     
    ++list->len;
    return list;
}

linkedList *listAddNodeTail(linkedList *list,void *value){
    if(list == NULL || value == NULL)
        return list;
    listNode *node = NULL;
    node = malloc(sizeof(*node));
    if(node==NULL)
        return list;
    node->value = value;
    node->next = NULL;
    if(list->head == NULL && list->len == 0)
        list->head = node;
    else{
        listNode *tail = list->head;
        listNode *pre = list->head;
        while(tail != NULL){
            pre = tail;
            tail = tail->next;
        }
        pre->next = node;
    }
    ++list->len;
    return list;
}

linkedList *listInsertNode(linkedList *list, listNode *old_node, void *value, bool after){
    if(list == NULL || old_node == NULL)
        return NULL;
    listNode *pNode = NULL;
    pNode = malloc(sizeof(*pNode));
    if(pNode == NULL)
        return list;
    pNode->value = value;
    if(after){
        pNode->next = old_node->next;
        old_node->next = pNode;
    }else{
        listNode *pre = list->head;
        while(pre->next != old_node){
            pre = pre->next;
        }
        if(pre != NULL){
            pre->next = pNode;
            pNode->next = old_node;
        }
    }
    ++list->len;
    return list;
}

//无释放函数时不做释放的处理
void listDelNode(linkedList *list, listNode *node){
    if(list==NULL || node==NULL)
        return ;
    listNode *pre = list->head;
    listNode *cur = list->head;
    while(cur != NULL && cur != node){
        pre = cur;
        cur = cur->next;
    }
    //不在链表中
    if(pre==NULL)
        return ;
    pre->next = node->next;
    node->next = NULL;
    --list->len;
    if(list->free!=NULL){
        list->free(node->value);
        free(node);
        node = NULL;
    }
}

listNode *listSearchKey(linkedList *list, void *key){
    if(list==NULL)
        return NULL;
    listNode *node = list->head;
    while(node!=NULL){
        if(list->match!=NULL){
            if(list->match(key,node->value)==0)
                return node;
        }else{
            if(key==node->value)
                return node;
        }
        node = node->next;
    }
    return NULL;
}

listNode *listIndex(linkedList *list,long index){
    if(list == NULL)
        return NULL;
    if(index <= 0 || index>list->len)
        return NULL;
    listNode *pNode = list->head;
    for(long i = 0;i < index ; ++i){
        pNode = pNode->next;
    }
    return pNode;
}

linkedList *listRewind(linkedList *list){
    if(list==NULL)
        return NULL;
    listNode *head = list->head;
    listNode *pre = NULL;
    listNode *next = NULL;
    while(head!=NULL){
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    list->head = pre;
    return list;
}

size_t listLength(linkedList *list){
    if(list==NULL)
        return 0;
    return list->len;
}