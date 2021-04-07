/**
 * 0) ����������
 * 1) ������ת
 * 2) �����л��ļ��
 * 3) �������������ϲ�
 * 4) ɾ����������n�����
 * 5) ��������м���
 **/
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include<memory.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct SinglyLinkedNode{
    int data;
    struct SinglyLinkedNode* next;
}SinglyLinkedNode;

void insertNode(SinglyLinkedNode** head_ref, int data);
void printLinkedList(SinglyLinkedNode* head);

//��ת������
void reserse(SinglyLinkedNode** head_ref){
    if(*head_ref == NULL) 
        return ;
    SinglyLinkedNode *prev = NULL;
    SinglyLinkedNode *current = *head_ref;
    while(current){
        SinglyLinkedNode *next = current->next;
        if(!next){
            //����β���,����ַ����head_ref
            *head_ref = current;
        }
        current->next = prev;
        prev = current;
        current = next;
    }
}

void test_reserve(){
    SinglyLinkedNode* head = NULL;
    insertNode(&head,3);
    insertNode(&head,2);
    insertNode(&head,1);

    reserse(&head);
    printLinkedList(head);
}

//��ⵥ�����Ƿ���ڻ�
//����ʹ��һ��ָ��Ҳ����
int checkCircle(SinglyLinkedNode** head_ref){
    if(*head_ref == NULL) return;
    SinglyLinkedNode *slow = *head_ref,*fast = *head_ref;
    while(fast!=NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
        if(slow == fast)
            return 1;
    }
}

void test_checkCircle(){
    SinglyLinkedNode* head = NULL;
    insertNode(&head,3);
    insertNode(&head,2);
    insertNode(&head,1);

    int result1 = checkCircle(&head);
    printf("has circle:%d\n",result1);

    //make circle linklist
    SinglyLinkedNode* current = (SinglyLinkedNode*)malloc(sizeof(SinglyLinkedNode));
    current->data = 0;
    SinglyLinkedNode* h = current;
    for(int i = 1;i < 4; ++i){
        SinglyLinkedNode* node = (SinglyLinkedNode*)malloc(sizeof(SinglyLinkedNode));
        node->data = i;
        current->next = node;
        //reset current node
        current = node;
    }
    current->next = h;
    int result2 = checkCircle(&h);
    printf("has circle:%d\n",result1);   
}
#endif