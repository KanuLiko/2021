#include"LinkList.h"
//利用链表判断是否时回文的数组

char array1[] = {'a','b','c','d','a'};
bool isPalindrome(LinkList* list,int length);
int main(int argc,char *argv[]){
    LinkList *list;
    int length = sizeof(array1)/sizeof(array1[0]);
    InitList(list);
    CreateListTail(list,array1,length);//用尾插法创建一个单链表
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
        GetListElem(list,i,e);//遍历获取链表的元素并放入数组中
        buff1[i-1] = e;//正向数组
        buff2[length -i] = e;//反向数组
    }
    i = 0;
    while(i <= length){
        printf("buff1:%c,buff2:%c\n",buff1[i],buff2[i]);
        if(buff1[i]==buff2[i])//比较
            i++;
        else
            return false;
    }
    return true;
}