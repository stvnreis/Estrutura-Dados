#include <stdio.h>

#define size 10

typedef struct{
    int arr[size];
    int top;
}pilhaEstatica;

void start(pilhaEstatica *p){
    p->top = 0;
}

int pilhaVazia(pilhaEstatica *p){
    return p->top == 0 ? 1 : 0;
}

int pilhaCheia(pilhaEstatica *p){
    return p->top == size ? 1 : 0;
}

void push(pilhaEstatica *p, int value){
    if(pilhaCheia(p)){
        printf("Pilha ja esta cheia!");
    }
    else{
        p->arr[p->top] = value;
        p->top++;
    }
}

void pop(pilhaEstatica *p){
    if(pilhaVazia(p) == 1){
        printf("Pilha ja esta vazia!");
    }else{
        p->top--;
    }
}

int main(int argc, char *argv[]){

    pilhaEstatica p;
    start(&p);
    int value;
    scanf("%d", &value);
    push(&p, value);
    
    printf("%d\n", pilhaVazia(&p));
    printf("%d\n", pilhaCheia(&p));
    
    
    printf("%d ", p.arr[0]);
}