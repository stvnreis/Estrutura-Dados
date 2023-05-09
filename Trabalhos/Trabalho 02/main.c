#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Steven de Luca Reis de Oliveira, RA: 2484790
// Ana Laura Possan, RA: 2484650


// variaveis de Controle
// pagina atual indica qual foi o numero lido em <page:__> e slot_vazio indica qual slot do vetor de strings "termos" e o proximo livre
int paginaAtual, slot_vazio = 0;
char termos[20][250];

//definicao da estrutura da arvore
typedef struct noArvore
{
    char palavra[20];
	int paginas[50];
	int quantidadePaginas;
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
		(*no)->paginas[(*no)->quantidade - 1] = paginaAtual;
		(*no)->paginas[(*no)->quantidade] = -1;
		
		return true;
	}
	else if(strcmp(novaPalavra, (*no)->palavra) == 0)
	{
		// printf("Palavra ja existente na arvore!\n");
		//(*no)->quantidadePaginas++;
		if((*no)->paginas[(*no)->quantidadePaginas - 2] == paginaAtual)
			return false;
		(*no)->paginas[(*no)->quantidade - 1] = paginaAtual;
		(*no)->paginas[(*no)->quantidade] = -1;
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

bool estaEmTermos(char palavra[])
{
	int i;
	for(i=0; i<= slot_vazio; i++)
	{
		if(strcmp(palavra, termos[i]) == 0)
			return true;
	}
	return false;
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
    	if(estaEmTermos((*no)->palavra))
    	{
    		char paginas[100];
			fprintf(s, "%s %d", (*no)->palavra, (*no)->paginas[0]);	
			int i;
			for(i=1; i < (*no)->quantidade; i++)
			{
				fprintf(s, ", %d", (*no)->paginas[i]);
			}
			fprintf(s, "\n");
		}
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

void removeVirgula(char str[])
{
	int i =8, j=0;
	while(str[i] != '>')
	{
		if(str[i] == ',')
		{
			i++;
			slot_vazio++;
			j=0;
			continue;
		}
		termos[slot_vazio][j] = str[i];
		i++;
		j++;
	}
}

// ler todo o arquivo e inserir as palavras na arvore
void lerArquivo(FILE *e, noArvore **no)
{
	char palavra[100];
	while(fscanf(e, " %s", palavra) != EOF)
	{
		if(strncmp(palavra, "<termos:", 8) == 0)
		{
			//printf("termos\n", palavra);
			removeVirgula(palavra);
			continue;			
		}
		else if(strncmp(palavra, "<page:", 6) == 0)
		{
			paginaAtual = getNumeroPagina(palavra);
			//printf("Pagina %d\n", paginaAtual);
			continue;
		}
		inserir(&(*no), palavra);
	}
}

void printTermos()
{
	int i;
	for(i=0; i <= slot_vazio; i++)
	{
		printf("%s\n", termos[i]);
	}
}

int main()
{
	FILE *entrada = fopen("./entrada.txt", "r");
	FILE *saida = fopen("./saida.txt", "w");
    noArvore *raiz;
	iniciar(&raiz);
	
	lerArquivo(entrada, &raiz);

	//printf("Arvore:\n");
	printArquivo(saida, &raiz);
	printTermos();
	// printf("%d", paginaAtual);

	fclose(entrada);
    return 0;
}
