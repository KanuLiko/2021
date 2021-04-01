#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
//callback function
typedef struct NODE{
    struct NODE *link;
    int value;
}Node;
int single_link_list_insert(Node **rootp, int new_value){
    Node *current;
    Node *previous;
    Node *new;
    current = *rootp;
    //寻找正确的插入的位置,方法是按顺序访问链表,直到到达其值大于或等于新插入值的节点
    while(current!=NULL && current->value<new->value){
        previous = current;
        current = current->link;
    }
    //为新节点分配内存,并把新值存储到新节点中
    new = (Node*)malloc(sizeof(Node));
    if(new==NULL)
        return FALSE;
    new->value = new_value;
    //把新节点插入到链表中,并返回True
    new->link = current;
    if(previous==NULL)
        *rootp = new;
    else
        previous->link = new;
    return TRUE;
}
int main(int argc,char *grgv[]){
    Node *node1,*node2;
    node1->link = node2;
    node1->value = 5;
    node2->value = 12;
    single_link_list_insert(node1,12);
    return 0;
}