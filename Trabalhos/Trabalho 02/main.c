#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//definicao da estrutura da arvore
typedef struct noArvore
{
    char palavra[20];
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
		// (*no)->palavra = novaPalavra;
		strcpy((*no)->palavra, novaPalavra);
		(*no)->esquerda = NULL;
		(*no)->direita = NULL;
		
		return true;
	}
	else if(strcmp(novaPalavra, (*no)->palavra) == 0)
	{
		printf("Palavra ja existente na arvore!\n");
		return false;
	}
	else if(strcmp(novaPalavra, (*no)->palavra) < 0)
	{
		inserir(&(*no)->esquerda, novaPalavra);
	}
	else
	{
		inserir(&(*no)->direita, novaPalavra);
	}
}

void print(noArvore **no)
{
    if((*no) == NULL)
    {
        //printf("ponteiro vazio\n");
        return;
    }
    else
    {
        printf("%s ", (*no)->palavra	);
        print(&(*no)->esquerda);
        print(&(*no)->direita);
    }
}

int main()
{
	FILE *entrada = fopen("./entrada.txt", "r");
    noArvore *raiz;
	iniciar(&raiz);
	
	char palavra[52];

	while(fscanf(entrada, " %s", palavra) != EOF)
	{
		inserir(&raiz, palavra);
	}

	print(&raiz);

	fclose(entrada);
    return 0;
}