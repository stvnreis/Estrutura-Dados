#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM 45

// Feito por:
// Steven de Luca Reis de Oliveira, RA: 2484790
// Ana Laura Possan, RA: 2484650

// definindo a estrutura de pilha estática com seu vetor, topo e quantidade
typedef struct{
    int arr[TAM];
    int topo;
    int qt;
}pilhaEstatica;

// iniciando a pilha e definindo seu topo e quantidade como 0
void inicia(pilhaEstatica *p){
    p->topo = 0;
    p->qt = 0;
}

// verificando se a pilha está vazia através da quantidade
bool estaVazia(pilhaEstatica *p){
    return p->qt == 0 ? true : false;
}

// verificando se a pilha está cheia
bool estaCheia(pilhaEstatica *p){
    return p->qt == TAM ? true : false;
}

// adicionando os valores recebidos atráves do arquivo na pilha e adicionando no topo 
void empilha(pilhaEstatica *p, FILE *f){
    if(!estaCheia(p)){
        rewind(f);
		while(!feof(f)){
            fscanf(f, "%d\n", &p->arr[p->topo]);
            p->topo++;
            p->qt++;
        }
    }
    else{
    	printf("Pilha ja esta cheia!");
	}
}

// convertendo o numero decimal recebido do arquivo de entrada e convertendo para binário
char* paraBinario(int valor){
    int aux = ceil(log2(valor + 1));

    char *binario = (char*) malloc(sizeof(char) * aux+1);
    if(valor != 0){
        int i;
        for (i = aux - 1; i >= 0; i--){
            if (valor % 2 == 1){
                binario[i] = '1';
            }
            else{
                binario[i] = '0';
            }

            valor /= 2;
        }

        binario[aux] = '\0';

        return binario;
    }
    else{
        binario = "0\0";
        
        return binario;
    }
}

// removendo os valores do topo da pilha e armazenando no arquivo
void desempilha(pilhaEstatica *p, FILE *f){
    if(!estaVazia(p)){ 
        p->topo--;
        fprintf(f, " %s", paraBinario(p->arr[p->topo]));
        p->qt--;
        
		if(p->topo != 0){
        	fprintf(f, "\n");
		}
    }
}

// verificando a quantidade de argumentos passados na execução do programa
void verificaArgumentos(int qt){
    // se quantidade de argumentos for diferente de 3, imprime o erro e encerra o programa
    if(qt != 3){
        printf("ERRO: Quantidade incorreta de argumentos!");
        exit(0);
    }       
}

// fun��o que verifica se o conte�do da linha do arquivo de entrada possue apenas n�meros
void verificaLinha(char *l){
    int i = 0;
    while(l[i] != '\0' && l[i] != '\n'){
        if(l[i] < '0' || l[i] > '9'){
        	printf("%s\n", l);
            printf("ERRO:\n");
            printf("Charactere inesperado encontrado no arquivo! Por favor, insira um arquivo que contenha apenas numeros decimais inteiros.\n");
            exit(0);
        }
            i++;
    }
    return;
}

// armazenando o conteudo da linha do arquivo e chamando a fun��o que verifica se possuem apenas numeros
void verificaConteudo(FILE *entrada){
    char linha[100];
	printf("verificando conteudo do arquivo!\n");
    while(!feof(entrada)){
        fscanf(entrada, " %s", &linha);
        verificaLinha(linha);
        printf("Conteudo da linha: %s\n", linha);
    }

    rewind(entrada);
}

// fun��o que verifica se o arquivo est� vazio
void verificaVazio(FILE* entrada){
	fseek(entrada, 0, SEEK_END);
	
	int size = ftell(entrada);
	
	if(size == 0){
		printf("ERRO:\n");
        printf("Arquivo de origem em branco!\n");
        fclose(entrada);
		exit(0);
	}
	else{
		rewind(entrada);
		return;
	}
	
}

// verifica se os arquivos foram alocados com sucesso e chama a função para verificar se o arquivo atende os requisitos
void verificaArquivos(FILE *entrada, FILE *saida){
    if(entrada != NULL & saida != NULL){
        verificaVazio(entrada);
		verificaConteudo(entrada);
        return;
    }
    else if(entrada == NULL && saida != NULL){
        printf("Erro na CRIACAO do arquivo de entrada!");
        exit(0);
    }
    else if(entrada != NULL && saida == NULL){
        printf("Erro na CRIACAO do arquivo de saida!");
        exit(0);
    }
    else{
        printf("Erro na CRIACAO de ambos os arquivos!");
        exit(0);
    }
}

int main(int argc, const char *argv[]){
    verificaArgumentos(argc);
    
    FILE *entrada = fopen(argv[1], "r");
    FILE *saida = fopen(argv[2], "w");
    verificaArquivos(entrada, saida);

    pilhaEstatica p;
    inicia(&p);
    
    empilha(&p, entrada);
    
    int i;
    for(i=TAM - 1; i>=0; i--){
        desempilha(&p, saida);
    }

    fclose(entrada);
    fclose(saida);
    
    return 0;
}