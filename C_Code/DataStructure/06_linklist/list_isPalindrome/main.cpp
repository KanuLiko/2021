#include"LinkList.h"
//���������ж��Ƿ�ʱ���ĵ�����

char array1[] = {'a','b','c','d','a'};
bool isPalindrome(LinkList* list,int length);
int main(int argc,char *argv[]){
    LinkList *list;
    int length = sizeof(array1)/sizeof(array1[0]);
    InitList(list);
    CreateListTail(list,array1,length);//��β�巨����һ��������
    if(isPalindrome(list,length))
        printf("isPalindrome\n");
    else
        printf("isnotPalindrome\n");
    return 0;
}

bool isPalindrome(LinkList *list,int length){
    int i;
    char buff1[length],buff2[length];
    ElemType e;
    for(i=1;i<=length;i++){
        GetListElem(list,i,e);//������ȡ�����Ԫ�ز�����������
        buff1[i-1] = e;//��������
        buff2[length -i] = e;//��������
    }
    i = 0;
    while(i <= length){
        printf("buff1:%c,buff2:%c\n",buff1[i],buff2[i]);
        if(buff1[i]==buff2[i])//�Ƚ�
            i++;
        else
            return false;
    }
    return true;
}