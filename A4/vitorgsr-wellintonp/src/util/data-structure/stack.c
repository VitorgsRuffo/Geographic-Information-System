#include "../../include/headers.h"
#include "../../include/util.h"

typedef struct stackNode {
    Info data;
    struct stackNode* next;
}stackNode;


StackNode createStack(){
    return NULL;
}

int empty(Stack* PointerToHead){
    
    if(PointerToHead == NULL)
        return 1;
    
    else if (*PointerToHead == NULL)
        return 1;

    else
        return 0;
}

int stackLength(Stack* PointerToHead){
    if(isElementNull(PointerToHead, "pointeiro para a cabeca da pilha", "stackLength"))
        return 0;  

    if(empty(PointerToHead))
        return 0;
    
    
    stackNode** pointerToHead = (stackNode**) PointerToHead;
    stackNode* aux = *pointerToHead; //endereço do nó no topo da pilha.
    int count = 0;
    
    do {
        count++;
        aux = (*aux).next;
    }while(aux != NULL);
    
    return count;
}

int stackPush(Stack* PointerToHead, Info data){
    if(isElementNull(PointerToHead, "pointeiro para a cabeca da pilha", "stackPush"))
       return 0;

    stackNode** pointerToHead = (stackNode**) PointerToHead; 
    
    stackNode* newNode = (stackNode*) malloc(sizeof(stackNode));
    if(newNode == NULL)
        return 0;

    newNode->data = data;
    newNode->next = *pointerToHead;
    *pointerToHead = newNode;

    return 1;
}

Info stackPop(Stack* PointerToHead){
    if(isElementNull(PointerToHead, "pointeiro para a cabeca da pilha", "stackPop"))
        return NULL;  

    if(empty(PointerToHead))
        return NULL;
    
    
    stackNode** pointerToHead = (stackNode**) PointerToHead;
    stackNode* aux = *pointerToHead;

    *pointerToHead = (**pointerToHead).next;
    Info popedData = (*aux).data;
    free(aux);

    return popedData;
}

Info stackTop(Stack* PointerToHead){
    if(isElementNull(PointerToHead, "pointeiro para a cabeca da pilha", "stackTop"))
        return NULL;

    if(empty(PointerToHead))
        return NULL;
    
    stackNode** pointerToHead = (stackNode**) PointerToHead;
    return (**pointerToHead).data;   
}

Info* stackToArray(Stack* PointerToHead){
    if(isElementNull(PointerToHead, "pointeiro para a cabeca da pilha", "stackToArray"))
        return NULL;

    if(empty(PointerToHead))
        return NULL;
    

    int length = stackLength(PointerToHead);

    Info* array = (Info*) malloc(length*sizeof(Info));
    if(array == NULL)
        return NULL;
    
    for(int i=0; i<length; i++)
        array[i] = stackPop(PointerToHead);
    
    return array;
} 

void printStack(Stack* PointerToHead, char* (*tadToString)(void*)){
    if(isElementNull(PointerToHead, "pointeiro para a cabeca da pilha", "printStack"))
       return;

    if(empty(PointerToHead))
        return;

    stackNode** pointerToHead = (stackNode**) PointerToHead;
    stackNode* aux = *pointerToHead; //endereço do nó no topo da pilha.
    char* tadString;

    printf("\nStack frames: \n");
    
    do {
        tadString = (*tadToString)((*aux).data);
        printf("%s", tadString);
        free(tadString);
        aux = (*aux).next;
    }while(aux != NULL);
}

void freeStack(Stack* PointerToHead, void (*freeTad)(void*)){
    
    if(empty(PointerToHead))
        return;
    
    stackNode** pointerToHead = (stackNode**) PointerToHead; 
    stackNode* aux;
    
    do {
        aux = *pointerToHead;
        *pointerToHead = (**pointerToHead).next;

        (*freeTad)((*aux).data);
        (*aux).data = NULL; (*aux).next = NULL;
        free(aux);
    }while(*pointerToHead != NULL);   
}