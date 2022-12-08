#include <stdlib.h>
#include "stack.h"

//function to create empty stack
STACK createStack(){

    LLIST list={0,NULL,NULL};
    STACK S={list};
    return S;
}

//function to check if stack empty or not
int isEmptyStack(STACK S){

    return ((S.list.size==0)? 1 : 0);
}

//function to push element in stack
STACK push(STACK S, int k){

    S.list=insertAtFront(S.list,k);
    return S;
}

//function to pop element from stack
STACK pop(STACK S, int *k){

    S.list=deleteFromFront(S.list,k);
    return S;
}
