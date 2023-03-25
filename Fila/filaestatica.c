#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

typedef struct{
	int arr[SIZE];
	int head;
	int tail;
	int qt;
}queue;

void start(queue *q){
	q->head = 0;
	q->tail = -1;
	q->qt = 0;
}

bool isEmpty(queue *q){
	return q->qt == 0 ? true : false;
}

bool isFull(queue *q){
	return q->qt == SIZE ? true : false;
}

int length(queue *q){
	return q->qt;
}

int addIndex(int index){
	if(index == SIZE -1){
		return 0;
	}
	return index + 1;
}

void enQueue(queue *q, int value){
	if(!isFull(q)){
		q->tail = addIndex(q->tail);
		q->arr[q->tail] = value;
		q->qt++;
		printf("Valor %d adicionado na posicao %d\n", value, q->tail);
	}
	else{
		printf("Fila ja esta cheia!\n");
	}
}

void deQueue(queue *q){
	if(!isEmpty(q)){
		q->head = addIndex(q->head);
		q->qt--;
	}
	else{
		return;
	}
}

void print(queue *q){
	if(!isEmpty(q)){
		int i = q->head;
		while(i != q->tail){
			printf("valor %d\n", q->arr[i]);
			i = addIndex(i);
		}
		printf("valor %d\n", q->arr[q->tail]);
	}
	else{
		printf("Fila Vazia!\n");
	}
}

void main(){
	queue q;
	
	start(&q);
	
	enQueue(&q, 1);
	enQueue(&q, 2);
	enQueue(&q, 3);
	enQueue(&q, 4);
	enQueue(&q, 5);
	enQueue(&q, 6);
	enQueue(&q, 7);
	enQueue(&q, 8);
	enQueue(&q, 9);
	enQueue(&q, 10);
	deQueue(&q);
	enQueue(&q, 1);
	printf("%d\n", length(&q));
	print(&q);
}


