#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

// Steven de Luca Reis de Oliveira, RA a2484790	
// Ana Laura Possan, RA a2484650

#define MAX_LENGTH 256
#define MAX_PAGES 100

// variaveis de controle de escopo global
int pagina_atual;

typedef struct noLista
{
	char termo[MAX_LENGTH];
	struct noLista *prox;
}noLista;

typedef struct Lista
{
	int qtd;
	noLista *primeiro;
}Lista;

typedef struct noArvore
{
	char palavra[MAX_LENGTH];
	int paginas[MAX_PAGES];
	int quantidade_paginas;
	struct noArvore *esquerda;
	struct noArvore *direita;
}noArvore;

// funcao de controle para verificar se a pagina ja foi inserida na lista de paginas da palavra

int verifica_paginas(noArvore **no)
{
	int i;
	for(i=0; i < (*no)->quantidade_paginas; i++)
	{
		if((*no)->paginas[i] == pagina_atual)
			return 1;
	}
	return 0;
}

// codigos lista ordenada
// inicializando lista ordenada
void iniciar_lista(Lista *l)
{
	l->qtd = 0;
	l->primeiro = NULL;
}

// fazendo verificacao se lista esta vazia atraves da variavel quantidade
int lista_vazia(Lista *l)
{
	return l->qtd == 0 ? 1 : 0;
}

// inserindo termos na lista ordenada
int inserir_termo(Lista *l, char termo[])
{
	// comparacao entre strings em uppercase para garantir case insensitive
	if(strcasecmp(termo, l->primeiro->termo) == 0)
	{
		return 0;
	}
	
	// alocando memoria para novo termo
	noLista *novo_termo = (noLista *) malloc (sizeof(noLista));
	strcpy(novo_termo->termo, termo);
	novo_termo->prox = NULL;
	
	// caso lista de termos esteja vazia, insere na primeira posicao
	if(lista_vazia(l))
	{
		l->primeiro = novo_termo;	
	}
	else if(strcasecmp(termo, l->primeiro->termo) < 0)
	{
		novo_termo->prox = l->primeiro;
		l->primeiro = novo_termo;
	}
	else // se nao, insere na posicao adequada, seguindo a ordem alfabetica
	{
		noLista *aux = l->primeiro;
		
		while(aux->prox != NULL && strcasecmp(termo, aux->prox->termo) > 0)
		{
			aux = aux->prox;
		}
		
		novo_termo->prox = aux->prox;
		aux->prox = novo_termo;
	}
	
	l->qtd++;
	return 1;
}


// codigos arvore binaria

// iniciando arvore
void iniciar_arvore(noArvore **no)
{
	(*no) = NULL;
}

// inserindo valores dentro da arvore 
int inserir_arvore(noArvore **no, char palavra[])
{
	// se nao existe a palavra, sera inserido em um novo no e inicializado seu vetor de paginas com a pagina atual
	if((*no) == NULL)
	{
		*no = malloc (sizeof(noArvore));
		strcpy((*no)->palavra, palavra);
		(*no)->quantidade_paginas = 1;
		(*no)->paginas[(*no)->quantidade_paginas - 1] = pagina_atual;
		(*no)->direita = NULL;
		(*no)->esquerda = NULL;
		
		return 1;
	}
	else if(strcasecmp(palavra, (*no)->palavra) == 0)
	{
		// se palavra ja existe, pagina atual sera inserido no vetor
		if(verifica_paginas(&(*no)) == 0)
		{
			(*no)->quantidade_paginas++;
			(*no)->paginas[(*no)->quantidade_paginas -1] = pagina_atual;
			return 1;
		}
		
	}
	// se palavra for "menor" do que palavra no no atual, vai para a esquerda, se nao, vai para a direita
	else if(strcasecmp(palavra, (*no)->palavra) < 0)
	{
		return inserir_arvore(&(*no)->esquerda, palavra);
	}
	else 
	{
		return inserir_arvore(&(*no)->direita, palavra);
	}
}

// procura o no no qual a palavra pesquisada se encontra e retorna um ponteiro para o no pesquisado
noArvore **pesquisar_palavra(noArvore **no, char palavra[])
{
	if((*no) == NULL)
	{
		return NULL;
	}
	else if(strcasecmp(palavra, (*no)->palavra) == 0)
	{
		strcpy((*no)->palavra, palavra);
		return no;
	}
	else if(strcasecmp(palavra, (*no)->palavra) < 0)
	{
		pesquisar_palavra(&(*no)->esquerda, palavra);
	}
	else
	{
		pesquisar_palavra(&(*no)->direita, palavra);
	}
}

// printando no no console e arquivo de saida valores recebidos do no correspondente ao termo pesquisado
void printar_arvore(FILE *s, noArvore **no)
{
	if(no == NULL)
	{
		return;
	}
	
	printf("%s %d", (*no)->palavra, (*no)->paginas[0]);
	fprintf(s, "%s %d", (*no)->palavra, (*no)->paginas[0]);
	int i;
	for(i=1; i<(*no)->quantidade_paginas; i++)
	{
		printf(", %d", (*no)->paginas[i]);
		fprintf(s, ", %d", (*no)->paginas[i]);
	}
	fprintf(s, "\n");
	printf("\n");
}


// parte da juncao das estruturas

//para cada elemento na lista de termos, sera pesquisado na arvore e printado no console/arquivo de saida.

void get_termos(Lista *l, char termos[])
{
	char palavra[MAX_LENGTH];
	int i = 8, j = 0;

	while(termos[i] != '>')
	{
		if(termos[i] == ',')
		{
			palavra[j] = '\0';
			j=0;
			i++;
			inserir_termo(l, palavra);
			continue;
		}
		palavra[j] = termos[i];
		j++;
		i++;
	}
	palavra[j] = '\0';
	inserir_termo(l, palavra);
}

int get_pagina(char *str)
{
	int i, j = 0, tamanho = strlen(str);
	char *numero;

	// removendo caracteres da string e deixando apenas o numero
	numero = strtok(str, "<page:"); 
	numero = strtok(numero, ">");

	return atoi(numero); // retorno da conversao do numero restante da string em inteiro
}

// tratando string, tirando caracteres desnecessarios e dividindo palavras em multiplas strings conforme os separadores
void trata_string(noArvore **no, char str[])
{
	int tamanho = strlen(str);
	if(str[tamanho - 1] == ',' || str[tamanho - 1] == '.' || str[tamanho - 1] == ';')
	{
		str[tamanho - 1] = '\0';
	}
	str = strtok(str, "().");

	while(str != NULL)
	{
		inserir_arvore(&(*no), str);

		str = strtok(NULL, "().");
	}
}

// pegando os termos da lista de termos, pesquisando e printando
void mostrar_termos(FILE *s, Lista *l, noArvore **no)
{
	noLista *aux = l->primeiro;
	
	while(aux != NULL)
	{
		printar_arvore(s, pesquisar_palavra(&(*no), aux->termo));
		aux = aux->prox;
	}
}

// lendo arquivo, localizando numero da pagina e termos
void ler_arquivo(FILE *e, noArvore **no, Lista *l)
{
	char palavra[MAX_LENGTH];
	while(fscanf(e, "%s", palavra) != EOF)
	{
		if(strncmp(palavra, "<termos:", 8) == 0) // se linha contem termos, sera inserido na lista 
		{
			get_termos(l, palavra);
			continue;
		}
		else if(strncmp(palavra, "<page:", 6) == 0) // se linha contem pagina, sera atualizado a variavel de controle global
		{
			pagina_atual = get_pagina(palavra);
			continue;
		}
		else
		{
			trata_string(&(*no), palavra);
		}
	}
}

// funcoes de tratamento de erro

// verifica se o arquivo esta vazio a partir da posicao do ponteiro do arquivo
int estaVazioArquivo(FILE *f)
{
	fseek(f, 0, SEEK_END);
	int tamanhoArquivo = ftell(f);
	
	rewind(f); // reiniciando ponteiro do arquivo
	
	if(tamanhoArquivo == 0)
		return 1;
	else
		return 0;
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
		// caso arquivo esteja vazio, o programa sera encerrado
		printf("ERRO: Arquivo de entrada vazio!\n");
		exit(1);
	}
	else
	{
		return;		
	}
}

// verifica quantidade de argumentos passados na chamada da execucao do programa. Se igual a 3, segue sua execucao normalmente
void verificaArgumentos(int arg)
{
	if(arg == 3)
		return;
	else if(arg < 3)
	{
		printf("Numero de argumentos insuficientes, insira tres argumentos seguindo a seguinte ordem:\n");
		printf("./main 'arquivo_de_entrada.txt 'arquivo_de_saida.txt'\n");
		exit(1);
	}
	else
	{
		printf("Numero de argumentos nao esta de acordo com o necessario, insira tres argumentos seguindo a seguinte ordem:\n");
		printf("./main 'arquivo_de_entrada.txt 'arquivo_de_saida.txt'\n");
		exit(1);
	}
}

int main(int argc, const char *argv[])
{
	FILE *entrada = fopen(argv[1], "r");
	FILE *saida = fopen(argv[2], "w");
	
	verificaArgumentos(argc);
	trataArquivos(entrada, saida);

	Lista *termos = malloc (sizeof(Lista));
	noArvore *raiz;

	iniciar_lista(termos);
	iniciar_arvore(&raiz);
	
	ler_arquivo(entrada, &raiz, termos);
	mostrar_termos(saida, termos, &raiz);

	return 0;
}