#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAM 10

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
        while(!feof(f)){
            fscanf(f, "%d\n", &p->arr[p->topo]);
            p->topo++;
            p->qt++;
        }
    }
}

// removendo os valores do topo da pilha e armazenando no arquivo
void desempilha(pilhaEstatica *p, FILE *f){
    if(!estaVazia(p)){ 
        p->topo--;
        fprintf(f, "%d\n", p->arr[p->topo]);
        p->qt--;
    }
}

// convertendo o numero decimal recebido do arquivo de entrada e convertendo para binário
int paraBinario(int valor){
    int binario = 0;
    int base = 1;
    
    while(valor > 0){
        int resto = valor % 2;
        binario += resto * base;
        base *=10;
        valor/=2;
    }
    
    return binario;
}

// verificando a quantidade de argumentos passados na execução do programa
void verificaArgumentos(int qt){
    // se quantidade de argumentos for diferente de 3, imprime o erro e encerra o programa
    if(qt != 3){
        printf("ERRO: Quantidade incorreta de argumentos!");
        exit(0);
    }       
}

void verificaLinha(char *l){
    int i = 0;

    while(l[i] != '\0' && l[i] != '\n'){
        if(l[i] < '0' || l[i] > '9'){
            printf("Charactere encontrado no arquivo! Por favor, insira um arquivo que contenha apenas numeros decimais.\n");
            exit(0);
        }
            i++;
    }
    return;
}

// armazenando o conteudo da linha do arquivo e verificando se possuem apenas numeros
void verificaConteudo(FILE *entrada){
    char linha[100];
    while(!feof(entrada)){
        printf("verificando conteudo!\n");
        fscanf(entrada, " %[^\n]s\n", &linha);
        printf("Conteudo da linha: %s\n", linha);
        verificaLinha(linha);
    }
    rewind(entrada);
}

// verifica se os arquivos foram alocados com sucesso e chama a função para verificar se o arquivo atende os requisitos
void verificaArquivos(FILE *entrada, FILE *saida){
    if(entrada != NULL & saida != NULL){
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

int main(int argc, char *argv[]){
    verificaArgumentos(argc);
    
    FILE *entrada = fopen(argv[1], "r");
    FILE *saida = fopen(argv[2], "w");
    verificaArquivos(entrada, saida);

    pilhaEstatica p;
    inicia(&p);
    
    empilha(&p, entrada);
    int i;
    for(i=TAM - 1; i>=0; i--){
        p.arr[i] = paraBinario(p.arr[i]);
    }
    for(i=TAM - 1; i>=0; i--){
        desempilha(&p, saida);
    }

    fclose(entrada);
    fclose(saida);
}