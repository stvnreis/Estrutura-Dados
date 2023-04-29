#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// strcmp("ana", "steven"); -> retorna -1 pq steven vem dps de ana em ordem alfabética

typedef struct noArvore
{
    int valor;
    struct noArvore *direita;
    struct noArvore *esquerda;
}noArvore;

void start(noArvore **ar)
{
   (*ar) = NULL;
}

bool estaVazia(noArvore **ar)
{
    return (*ar) == NULL ? true : false;
}

bool inserir(noArvore **ar, int valor)
{
    if((*ar) == NULL)
    {
        *ar =  malloc (sizeof(noArvore));
        (*ar)->valor = valor;
        (*ar)->direita = NULL;
        (*ar)->esquerda = NULL;
        return true;
    }
    else if((*ar)->valor == valor)
    {
        return false;
    }
    else if(valor > (*ar)->valor)
    {
        return inserir(&(*ar)->direita, valor);
    }
    else if(valor < (*ar)->valor)
    {
        return inserir(&(*ar)->esquerda, valor);
    }
}

void print(noArvore **ar)
{
    if((*ar) == NULL)
    {
        //printf("ponteiro vazio\n");
        return;
    }
    else
    {
        printf("%d ", (*ar)->valor);
        print(&(*ar)->esquerda);
        print(&(*ar)->direita);
    }
}

void preOrdem(noArvore **ar)
{
    printf("Imprimindo arvore em pre-ordem\n");
    print(&(*ar));
}

int main()
{
    noArvore *raiz;
    start(&raiz);

    printf("%d\n", estaVazia(&raiz));

    inserir(&raiz, 5);
    inserir(&raiz, 4);
    inserir(&raiz, 7);
    inserir(&raiz, 3);
    inserir(&raiz, 2);
    inserir(&raiz, 6);
    inserir(&raiz, 8);
    inserir(&raiz, 9);
    preOrdem(&raiz);
}