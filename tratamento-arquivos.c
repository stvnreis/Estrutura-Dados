#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, const char *argv){
    // passar arquivos como parametro
    // exemplo -> ./main 'entrada.txt' 'saida.txt'
    FILE *e = fopen(argv[1], "r");
    FILE *s = fopen(argv[2], "w");

    trataArquivos(e, s);
}