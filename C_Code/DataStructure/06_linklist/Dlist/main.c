#include<stdio.h>
#include<stdlib.h>
#include"Dlist.h"

int main(int argc, char* argv[]){
    stDlistHead dlist = {0};
    stDlistNode* pNode = NULL;
    dlist_init(&dlist);

    printf("\r\n insert 1,2,3");
    dlist_insert_head(&dlist,pNode,1);
    dlist_insert_head(&dlist,pNode,2);
    dlist_insert_head(&dlist,pNode,3);
    printf("\n**********************");
    dlist_dump(&dlist);
    
    pNode = dlist_remove_tail(&dlist);
    if(pNode != NULL)
        printf("\r\n remove %d", pNode->data);
    dlist_insert_head(&dlist, pNode, 4);
    printf("\n--------------------------");
    dlist_dump(&dlist);

    Lru_dlist(&dlist, 5);
    dlist_dump(&dlist);
    Lru_dlist(&dlist, 6);
    dlist_dump(&dlist);
    Lru_dlist(&dlist, 7);
    dlist_dump(&dlist);
    Lru_dlist(&dlist, 5);
    dlist_dump(&dlist);

    while(dlist.size>0){
        pNode = dlist_remove_tail(&dlist);
        if(pNode != NULL){
            printf("\r\n remove %d", pNode->data);
            free(pNode);
        }
    }
    return 0;
}