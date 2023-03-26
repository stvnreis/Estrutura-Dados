#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct no{
    int value;
    struct no *next;
}no;

typedef struct{
    int qtd;
    no *top;
}pilha;

void start(pilha *p){
    p->top = NULL;
    p->qtd = 0;
}

bool isEmpty(pilha *p){
    return p->top == NULL ? true : false;
}

void push(pilha *p, int value){
    no *aux = (no*) malloc (sizeof(no));
    if(aux == NULL){
        printf("Falha na criacao do no!\n");
        return;
    }
    else{
        aux -> value = value;
        aux -> next = p->top;
        p -> top = aux;
        p->qtd++;
    }
}

void pop(pilha *p){
    if(isEmpty(p)){
        printf("Pilha ja esta vazia!\n");
        return;
    }
    else{
        no *aux = p->top;
        int value = p->top->value;
        p->top = p->top ->next;
        p->qtd--;
        free(aux);
    }
}

void printStack(pilha *p){
    no *aux = p->top;
    if(isEmpty(p)){
        printf("Pilha vazia!\n");
        return;
    }else{
        printf("Printando pilha:\n");
        while(aux != NULL){
            printf("%d ", aux->value);
            aux = aux->next;
        }
        printf("\n");
    }
}

int main(){
    pilha *p = (pilha*) malloc (sizeof(pilha));
    start(p);

    int value = 0;
    while(true){
        scanf("%d", &value);
        
        if(value == -1000){
            break;
        }
        
        push(p, value);
    }
    printf("quantidade: %d\n", p->qtd);
    printStack(p);

    while(!isEmpty(p)){
        pop(p);
    }
    

    printStack(p);
}
