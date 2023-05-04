#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//definicao da estrutura da arvore
typedef struct noArvore
{
    char *palavra;
    struct noArvore *esquerda;
    struct noArvore *direita;
}noArvore;

//iniciar a raiz da arvore
void iniciar(noArvore **raiz)
{
    (*raiz) = NULL;
}

bool estaVazia(noArvore **raiz)
{
	return (*raiz) == NULL ? true : false;
}

bool inserir(noArvore **no, char *novaPalavra)
{
	if((*no) == NULL)
	{
		(*no) = malloc (sizeof(noArvore));
		(*no)->palavra = novaPalavra;
		(*no)->esquerda = NULL;
		(*no)->direita = NULL;
		
		return true;
	}
	else if((*no)->palavra == novaPalavra)
	{
		printf("Palavra ja existente na arvore!\n");
		return false;
	}
	else if(novaPalavra < (*no)->palavra)
	{
		inserir(&(*no)->esquerda, novaPalavra);
	}
	else
	{
		inserir(&(*no)->direita, novaPalavra);
	}
}

int main()
{
    noArvore *raiz;
	iniciar(&raiz);
	
    inserir(&raiz, "Steven");
    printf("%s\n", raiz->palavra);
    printf("%d", inserir(&raiz, "Ana"));
    return 0;
}
