#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodeList
{
    int value;
    struct nodeList *next;
}nodeList;

typedef struct List
{
    int qtElements;
    nodeList *start;
}List;

void start(List *l)
{
	printf("Iniciando lista");
    l->start = NULL;
    l->qtElements = 0;
}

bool isEmpty(List *l)
{
    return l->qtElements == 0 ? true : false;
}

bool insert(List *l, int newValue)
{
    nodeList *newNode = (nodeList*) malloc (sizeof(nodeList));
    newNode->value = newValue;
    newNode->next = NULL;
    
    if(isEmpty(l))
    {
        l->start = newNode;
    }
    else if(newValue < l->start->value)
    {
        newNode->next = l->start;
        l->start = newNode;

        return true;
    }
    else if(newValue > l->start->value)
    {
        nodeList *aux = l->start;

        while(aux->next != NULL && newValue > aux->next->value)
        {
            aux = aux->next;
        }

        newNode->next = aux->next;
        aux->next = newNode;

        return true;
    }
    else
    {
        return false;
    }

    l->qtElements++;
}

void printList(List *l)
{
	if(!isEmpty(l))
	{
		nodeList *aux = l->start;
		printf("List = [");
		
		while(aux != NULL)
		{
			printf(" %d", aux->value);
			
			aux = aux->next;
		}
		printf(" ]\n");
	}
	else
	{
		printf("This list is empty!\n");	
	}
}

int main()
{
    List *l;
    start(&l);

    insert(&l, 10);
    insert(&l, 5);
    insert(&l, 50);
    insert(&l, 60);
    insert(&l, 2);
    insert(&l, 1000);
    
    printList(&l);

    return 0;
}
