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

// definicao da estrutura da arvore
typedef struct noArvore
{
    char palavra[20]; // string 
	int paginas[50]; // vetor de inteiros que representam as paginas
	int quantidadePaginas; // quantidade de paginas distintas
    struct noArvore *esquerda;
    struct noArvore *direita;
}noArvore;

// iniciar a raiz da arvore
void iniciar(noArvore **raiz)
{
    (*raiz) = NULL;
}

// verifica se a arvore esta vazia
bool estaVazia(noArvore **raiz)
{
	return (*raiz) == NULL ? true : false;
}

// verifica se a pagina atual esta no vetor de paginas do no
bool verificaPaginas(noArvore **no)
{
	int i;
	for(i=0; i < (*no)->quantidadePaginas; i++)
	{
		if((*no)->paginas[i] == paginaAtual)
			return true;
	}
	return false;
}

// inserir palavras na arvore seguindo ordem alfabetica
bool inserir(noArvore **no, char *novaPalavra)
{
	if((*no) == NULL)
	{
		(*no) = malloc (sizeof(noArvore));
		strcpy((*no)->palavra, novaPalavra); //

		(*no)->esquerda = NULL;
		(*no)->direita = NULL;
		(*no)->quantidadePaginas = 1;
		(*no)->paginas[0] = paginaAtual;
		
		return true;
	}
	// caso a palavra ja exista na arvore, sera adicionado a pagina atual em seu vetor de paginas
	else if(strcmp(novaPalavra, (*no)->palavra) == 0) 
	{
		if(!verificaPaginas(&(*no)))
		{
			(*no)->paginas[(*no)->quantidadePaginas] = paginaAtual;
			(*no)->quantidadePaginas++;
		}
		return false;
	}
	// caso a palavra a ser inserida for "menor" em ordem alfabética, sera direcionado para a subarvore esquerda, se nao, para a direita.
	else if(strcmp(novaPalavra, (*no)->palavra) < 0)
	{
		inserir(&(*no)->esquerda, novaPalavra);
	}
	else
	{
		inserir(&(*no)->direita, novaPalavra);
	}
}

// verifica se a palavra esta no vetor de string
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

// printa as informacoes no arquivo de saida
void printArquivo(FILE *s, noArvore **no)
{
	if(!(*no) == NULL)
    {
    	// se a palavra esta no vetor de string, sera printado todas suas informacoes
    	// print de informacoes em pre-ordem (no -> esquerda ->direita)
    	if(estaEmTermos((*no)->palavra))
    	{
    		char paginas[100];
			fprintf(s, "%s %d", (*no)->palavra, (*no)->paginas[0]);	
			int i;
			for(i=1; i < (*no)->quantidadePaginas; i++)
			{
				fprintf(s, ", %d", (*no)->paginas[i]);
			}
			fprintf(s, "\n");
		}
        printArquivo(s, &(*no)->esquerda);
        printArquivo(s, &(*no)->direita);
    }
}

// lendo valor referente a pagina apos remover "<page:> e retornando a conversao do valor para inteiro
int getNumeroPagina(char *str)
{
	int i, j = 0, tamanho = strlen(str);
	char *numero;
	numero = strtok(str, "<page:");
	numero = strtok(numero, ">");

	return atoi(numero);
}

// le a string de termos a partir da posicao 8 (correspondente ao <termos:)
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
		// caso a linha seja sobre termos, sera adicionado ao vetor de string "termos"
		if(strncmp(palavra, "<termos:", 8) == 0)
		{
			removeVirgula(palavra);
			continue;			
		}
		// caso a linha indique a pagina atual, seu valor sera passado para a variavel global
		else if(strncmp(palavra, "<page:", 6) == 0)
		{
			paginaAtual = getNumeroPagina(palavra);
			continue;
		}
		inserir(&(*no), palavra);
	}
}

bool estaVazioArquivo(FILE *f)
{
	fseek(f, 0, SEEK_END);
	int tamanhoArquivo = ftell(f);
	
	rewind(f);
	
	if(tamanhoArquivo == 0)
		return true;
	else
		return false;
}

// verifica se houve erro na criacao dos ponteiros para os arquvios correspondentes
void verificaArquivos(FILE *e, FILE *s)
{
	if(e == NULL && s != NULL)
	{
		printf("ERRO\n");
		printf("Arquivo de entrada nao encontrado!\n");
		exit(1);
	}
	else if(e != NULL && s == NULL)
	{
		printf("Erro na criacao do arquivo de saida!\n");
		exit(1);
	}
	else if(e != NULL && s == NULL)
	{
		printf("Erro na criacao de ambos arquivos!\n");
		exit(1);
	}
}

// faz tratamento de erro nos arquivos caso arquivo de entrada esteja vazio ou nao seja encontrado
void trataArquivos(FILE *e, FILE *s)
{
	verificaArquivos(e, s);
	if(estaVazioArquivo(e))
	{
		printf("ERRO: Arquivo de entrada vazio!\n");
		exit(1);
	}
	else
	{
		return;		
	}
}

int main(int argc, char *argv[])
{
	FILE *entrada = fopen("./entrada.txt", "r");
	FILE *saida = fopen("./saida.txt", "w");
    
    trataArquivos(entrada, saida);
    
	noArvore *raiz;
	iniciar(&raiz);
	
	lerArquivo(entrada, &raiz);
	printArquivo(saida, &raiz);

	fclose(entrada);
	fclose(saida);
    return 0;
}
