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
	printf("Iniciando lista\n");
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
        l->qtElements++;
        
        return true;
    }
    else if(newValue < l->start->value)
    {
        newNode->next = l->start;
        l->start = newNode;

		l->qtElements++;
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

		l->qtElements++;
        return true;
    }
    else
    {
        return false;
    }

}

bool removeVl(List *l, int rmValue)
{
	if(!isEmpty(l))
	{
		if(rmValue == l->start->value)
		{
			nodeList *rm = l->start;
			l->start = l->start->next;
			
			free(rm);
			
			l->qtElements--;
			
			return true;
		}
		nodeList *aux = l->start;
	
		while(aux->next->value != rmValue && aux->next != NULL)
		{
			aux = aux->next;
		}
		
		nodeList *rm = aux->next;
			
		aux->next = aux->next->next;
		free(rm);
		
		l->qtElements--;
		
		return true;
	}
	else
	{
		return false;
	}
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
    removeVl(&l, 1000);
    
    printList(&l);

    return 0;
}
