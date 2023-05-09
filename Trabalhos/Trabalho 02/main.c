#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Steven de Luca Reis de Oliveira, RA: 2484790
// Ana Laura Possan, RA: 2484650

int paginaAtual;

//definicao da estrutura da arvore
typedef struct noArvore
{
    char palavra[20];
	int quantidade;
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
		strcpy((*no)->palavra, novaPalavra); //

		(*no)->esquerda = NULL;
		(*no)->direita = NULL;
		(*no)->quantidade = 1;
		
		return true;
	}
	else if(strcmp(novaPalavra, (*no)->palavra) == 0)
	{
		// printf("Palavra ja existente na arvore!\n");
		(*no)->quantidade++;
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

void printArquivo(FILE *s, noArvore **no)
{
	if((*no) == NULL)
    {
        //printf("ponteiro vazio\n");
        return;
    }
    else
    {
		printf("%s %d\n", (*no)->palavra, (*no)->quantidade);
		fprintf(s, "%s %d\n", (*no)->palavra, (*no)->quantidade);
        printArquivo(s, &(*no)->esquerda);
        printArquivo(s, &(*no)->direita);
    }
}

int getNumeroPagina(char *str)
{
	int i, j = 0, tamanho = strlen(str);
	char *numero;
	numero = strtok(str, "<page:");
	numero = strtok(numero, ">");

	return atoi(numero);
}

// ler todo o arquivo e inserir as palavras na arvore
void lerArquivo(FILE *e, noArvore **no)
{
	char palavra[100];
	while(fscanf(e, " %s", palavra) != EOF)
	{
		if(strncmp(palavra, "<termos:", 8) == 0)
		{
			printf("termos\n", palavra);
			continue;			
		}
		else if(strncmp(palavra, "<page:", 6) == 0)
		{
			paginaAtual = getNumeroPagina(palavra);
			printf("Paginas %d\n", paginaAtual);
			continue;
		}
		inserir(&(*no), palavra);
	}
}

int main()
{
	FILE *entrada = fopen("./entrada.txt", "r");
	FILE *saida = fopen("./saida.txt", "w");
    noArvore *raiz;
	iniciar(&raiz);
	
	lerArquivo(entrada, &raiz);

	printf("Arvore:\n");
	printArquivo(saida, &raiz);

	// printf("%d", paginaAtual);

	fclose(entrada);
    return 0;
}