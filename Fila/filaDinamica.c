#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct no{
	int value;
	struct no *next;
}no;

typedef struct{
	no* head;
	no* tail;
	int qt;
}fila;

void start(fila *f){
	f->head = NULL;
	f->tail = NULL;
	f->qt = 0;
}

bool isEmpty(fila *f){
	return f->qt == 0? true : false;
}

int length(fila *f){
	return f->qt;
}

void enQueue(fila *f, int value){
	no *aux = (no*) malloc (sizeof(no*));
	aux->value = value;
	aux->next = NULL;
	if(isEmpty(f)){
		f->head = aux;
	}
	else{
		f->tail->next = aux;	
	}
	f->tail = aux;
}

void print(fila *f){
	printf("Fila = ");
	no* aux = f->head;
	while(aux != NULL){
		printf("%d\t", aux->value);
		aux = aux->next;
	}
}

int main(){
	fila f;
	start(&f);
	
	enQueue(&f, 5);
	print(&f);
	
}
