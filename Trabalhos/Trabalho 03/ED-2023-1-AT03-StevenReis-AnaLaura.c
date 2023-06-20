#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Steven de Luca Reis de Oliveira, RA: 2484790
// Ana Laura Possan, RA: 2484650

// declaracao de variaveis em escopo global para poder acessar de qualquer funcao
FILE *e;
FILE *s;
int size = 0;
char order;

// gerar array em ordem crescente, de valor 1 ate o valor igual ao tamanho do vetor
void crescente(int *arr, int size){
    int i;

    for(i=0; i<size; i++){
        arr[i] = i+1;
    }
}

// gerar array em ordem decrescente, de valor igual ao tamanho do vetor ate o valor 1
void decrescente(int *arr, int size){
    int i, j = size;
    
    for(i=0; i<size; i++){
        arr[i] = j;
        j--;
    }
}

// gerar array com valores aleatorios de 1 a 3200
void aleatorio(int *arr, int size){
    srand(time(NULL));
    int i;
    for(i=0; i<size; i++){
        arr[i] = rand()%3200;
    }
}

// gerando array de acordo com o que foi lido no arquivo de entrada
int *gera_arr(int size, char order)
{
    int *arr = malloc(size * sizeof(int));
    if(order == 'c'){
        crescente(arr, size);
    }
    else if(order == 'd'){
        decrescente(arr, size);
    }
    else if(order == 'r'){
        aleatorio(arr, size);
    }
    else{
        printf("Ordem desconhecida, insira uma das tres opcoes:\n");
        printf("c -- > gerar array em ordem crescente, de 0 ate o tamanho escolhido.\n");
        printf("d -- > gerar array em ordem decrescente, de 0 ate o tamanho escolhido.\n");
        printf("r -- > gerar array com valores aleatorios entre 1 e 3200.\n");

        exit(-1);
    }

    return arr;
}

// fazer copia do array passado como parametro para poder alterar sem modificar o original
int *copia_arr(int *arr, int size){
    int *novo_arr = malloc (size * sizeof(int)); 
    
    int i;
    for(i=0; i<size; i++){
        novo_arr[i] = arr[i];
    }
    
    return novo_arr;
}

int insertionSort(int array[], int size) {
    int i, chave, j, comparacoes = 0;
    for (i = 1; i < size; i++) {
        chave = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > chave) {
            comparacoes++;
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = chave;
    }
    return comparacoes;
}

int selectionSort(int array[], int size) {
    int i, j, indice_minimo, comparacoes = 0;
    for (i = 0; i < size - 1; i++) {
        indice_minimo = i;
        for (j = i + 1; j < size; j++) {
            // calculando quantas comparacoes foram feitas durante a execucao do algoritmo
            comparacoes++;
            if (array[j] < array[indice_minimo]) {
                indice_minimo = j;
            }
        }
        int temp = array[indice_minimo];
        array[indice_minimo] = array[i];
        array[i] = temp;
    }
    return comparacoes;
}

int bubbleSort(int array[], int size) {
    int i, j, comparacoes = 0;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            // calculando quantas comparacoes foram feitas durante a execucao do algoritmo
            comparacoes++;
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}

// estruturando mergeSort
void merge(int array[], int left, int middle, int right, int *comparacoes) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        // calculando quantas comparacoes foram feitas durante a execucao do algoritmo
        (*comparacoes)++;
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int left, int right, int *comparacoes) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(array, left, middle, comparacoes);
        mergeSort(array, middle + 1, right, comparacoes);

        merge(array, left, middle, right, comparacoes);
    }
}

// estruturando quickSort --> dividir para conquistar 
int partition(int array[], int low, int high, int *comparacoes) {
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // calculando quantas comparacoes foram feitas durante a execucao do algoritmo
        (*comparacoes)++;
        if (array[j] <= pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;

    return (i + 1);
}

void quickSort(int array[], int low, int high, int *comparacoes) {
    if (low < high) {
        int pi = partition(array, low, high, comparacoes);

        quickSort(array, low, pi - 1, comparacoes);
        quickSort(array, pi + 1, high, comparacoes);
    }
}


// estruturando heapSort
void heapify(int array[], int size, int root, int *comparacoes) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && array[left] > array[largest]) {
        largest = left;
    }

    if (right < size && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != root) {
        // calculando quantas comparacoes foram feitas durante a execucao do algoritmo
        (*comparacoes)++;
        int temp = array[root];
        array[root] = array[largest];
        array[largest] = temp;

        heapify(array, size, largest, comparacoes);
    }
}

int heapSort(int array[], int size) {
    int comparacoes = 0;
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(array, size, i, &comparacoes);
    }

    for (int i = size - 1; i > 0; i--) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        heapify(array, i, 0, &comparacoes);
    }
    return comparacoes;
}

void print_alg(int alg, int tempo, int comparacoes, int *arr){
    if(alg == 1){
        fprintf(s, "tempo percorrido insertionSort em milisegundos: %d comparacoes realizadas: %d ", tempo, comparacoes);
    }
        
    else if(alg == 2){
        fprintf(s, "tempo percorrido selectionSort em milisegundos: %d comparacoes realizadas: %d", tempo, comparacoes);
    }
    else if(alg == 3){
        fprintf(s, "tempo percorrido bubbleSort em milisegundos: %d comparacoes realizadas: %d", tempo, comparacoes);
    }
        
    else if(alg == 4){
        fprintf(s, "tempo percorrido mergeSort em milisegundos: %d comparacoes realizadas: %d", tempo, comparacoes);
    }
    else if(alg == 5){
        fprintf(s, "tempo percorrido quickSort em milisegundos: %d comparacoes realizadas: %d", tempo, comparacoes);
    }
    else if(alg == 6){
        fprintf(s, "tempo percorrido heapSort em milisegundos: %d comparacoes realizadas: %d", tempo, comparacoes);
    }

    int i;
    fprintf(s, " Vetor ordenado: [ %d ", arr[0]);
    for(i=1; i<size; i++){
        fprintf(s, "| %d ", arr[i]);
    }
    fprintf(s, "]\n");
}

// funcoes que calculam o tempo de execucao de cada algoritmo de ordenacao
void calcula_insertion(int *arr, int size){
    int *arr_tmp = copia_arr(arr, size);
    clock_t start, end;
    
    start = clock(); // guarda o valor da hora em que foi iniciado a ordenacao
    int comparacoes = insertionSort(arr_tmp, size);
    end = clock(); // guarda o valor da hora em que foi finalizado a ordenacao
        
    // printa o valor final - inicial / quantidade de ticks por segundo --> em milisegundos 
    // e a quantidade de comparacoes realizadas no algoritmo
    print_alg(1, (end - start)/(CLOCKS_PER_SEC/1000), comparacoes, arr_tmp);
    free(arr_tmp);
}

int calcula_selection(int *arr, int size){
    int *arr_tmp = copia_arr(arr, size);
    clock_t start, end;
    
    start = clock();
    int comparacoes = selectionSort(arr_tmp, size);
    end = clock();
    
    print_alg(2, (end - start)/(CLOCKS_PER_SEC/1000), comparacoes, arr_tmp);
    free(arr_tmp);
}

int calcula_bubble(int *arr, int size){
    int *arr_tmp = copia_arr(arr, size);
    clock_t start, end;
    
    start = clock();
    int comparacoes = bubbleSort(arr_tmp, size);
    end = clock();
        
    print_alg(3, (end - start)/(CLOCKS_PER_SEC/1000), comparacoes, arr_tmp);
    free(arr_tmp);
}

int calcula_merge(int *arr, int first, int last){
    int *arr_tmp = copia_arr(arr, last), comparacoes = 0;
    clock_t start, end;
    
    start = clock();
    mergeSort(arr_tmp, first, last, &comparacoes);
    end = clock();
        
    print_alg(4, (end - start)/(CLOCKS_PER_SEC/1000), comparacoes, arr_tmp);
    free(arr_tmp);
}

void calcula_heap(int *arr, int size){
    int *arr_tmp = copia_arr(arr, size);
    clock_t start, end;
    
    start = clock();
    int comparacoes = heapSort(arr_tmp, size);
    end = clock();
        
    print_alg(5, (end - start)/(CLOCKS_PER_SEC/1000), comparacoes, arr_tmp);
    free(arr_tmp);
}

int calcula_quick(int *arr, int first, int last){
    int *arr_tmp = copia_arr(arr, last), comparacoes = 0;
    clock_t start, end;
    
    start = clock();
    quickSort(arr_tmp, first, last, &comparacoes);
    end = clock();
        
    print_alg(6, (end - start)/(CLOCKS_PER_SEC/1000), comparacoes, arr_tmp);
    free(arr_tmp);
}

void ler_arquivo(){
    fscanf(e, "%d\n", &size);
    fscanf(e, " %c", &order);
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
void verificaArquivos()
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
void trataArquivos()
{
	verificaArquivos();
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

int main(int argv, const char *argc[]){
    verificaArgumentos(argv);
    trataArquivos();

    e = fopen(argc[1], "r");
    s = fopen(argc[2], "w");

    ler_arquivo();
    
    int *arr = gera_arr(size, order);
    
    calcula_insertion(arr, size);
    calcula_selection(arr, size);
    calcula_bubble(arr, size);
    calcula_merge(arr, 0, size-1);
    calcula_quick(arr, 0, size-1);
    calcula_heap(arr, size);
    
    free(arr);

    return 0;
}