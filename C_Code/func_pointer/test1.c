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
    //Ѱ����ȷ�Ĳ����λ��,�����ǰ�˳���������,ֱ��������ֵ���ڻ�����²���ֵ�Ľڵ�
    while(current!=NULL && current->value<new->value){
        previous = current;
        current = current->link;
    }
    //Ϊ�½ڵ�����ڴ�,������ֵ�洢���½ڵ���
    new = (Node*)malloc(sizeof(Node));
    if(new==NULL)
        return FALSE;
    new->value = new_value;
    //���½ڵ���뵽������,������True
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