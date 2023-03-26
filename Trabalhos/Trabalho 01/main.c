#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAM 3

// Feito por:
// Steven de Luca Reis de Oliveira, RA: 2484790
// Ana Laura Possan, RA: 2484650

typedef struct{
    int arr[TAM];
    int topo;
    int qt;
}pilhaEstatica;

void inicia(pilhaEstatica *p){
    p->topo = 0;
    p->qt = 0;
}

bool estaVazia(pilhaEstatica *p){
    return p->qt == 0 ? true : false;
}

bool estaCheia(pilhaEstatica *p){
    return p->qt == TAM ? true : false;
}

void empilha(pilhaEstatica *p, FILE *f){
    if(!estaCheia(p)){
        while(!feof(f)){
            fscanf(f, "%d\n", &p->arr[p->topo]);
            p->topo++;
            p->qt++;
        }
    }
}

void desempilha(pilhaEstatica *p, FILE *f){
    if(!estaVazia(p)){ 
        p->topo--;
        fprintf(f, "%d\n", p->arr[p->topo]);
        p->qt--;
    }
}

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

void verificaArgumentos(int qt){
    if(qt != 3){
        printf("ERRO: Quantidade incorreta de argumentos!");
        exit(0);
    }       
}

void verificaArquivos(FILE *entrada, FILE *saida){
    if(entrada != NULL & saida != NULL){
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
    printf("%d\n", p.qt);
    
    empilha(&p, entrada);
    int i;
    for(i=TAM - 1; i>=0; i--){
        p.arr[i] = paraBinario(p.arr[i]);
    }
    for(i=TAM - 1; i>=0; i--){
        desempilha(&p, saida);
    }
}