#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Steven de Luca Reis de Oliveira, RA: 2484790
// Ana Laura Possan, RA: 2484650

// vetor que ira armazenar a quantidade de comparacoes para cada algoritmo
int cmp[6];

void crescente(int *arr, int size){
    int i;

    for(i=0; i<size; i++){
        arr[i] = i+1;
    }
}

void decrescente(int *arr, int size){
    int i, j = size;
    
    for(i=0; i<size; i++){
        arr[i] = j;
        j--;
    }
}

void aleatorio(int *arr, int size){
    srand(time(NULL));
    int i;
    for(i=0; i<size; i++){
        arr[i] = rand()%3200;
    }
}

int *gera_arr(int size, char order)
{
    int *arr = malloc(size * sizeof(int));
    switch(order){
        case 'c':
            printf("Ordem crescente\n");
            crescente(arr, size);
            
            return arr;

        case 'd':
            printf("Ordem decrescente\n");
            decrescente(arr, size);
            
            return arr;
        
        case 'r':
            printf("Ordem aleatoria\n");
            aleatorio(arr, size);
            
            return arr;
        
        default:
            printf("Ordem desconhecida, encerrando programa!");
            exit(-1);
    }
}

void print_arr(int *arr, int size){
    int i;
    
    printf("Array: [");
    for(i=0; i<size; i++){
        printf(" %d", arr[i]);
    }
    printf(" ]\n");
}

int *copia_arr(int *arr, int size){
    int *novo_arr = malloc (size * sizeof(int)); 
    
    int i;
    for(i=0; i<size; i++){
        novo_arr[i] = arr[i];
    }
    
    return novo_arr;
}

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            cmp[0]++;
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]){
                cmp[1]++;
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                cmp[2]++;
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// estruturando mergeSort
void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        cmp[3]++;
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        cmp[3]++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        cmp[3]++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

// estruturando quickSort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            cmp[4]++;
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


// estruturando heapSort
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
    cmp[5]++;
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int calcula_insertion(int *arr, int size){
    int *arr_tmp = copia_arr(arr, size);
    clock_t start, end;
    
    start = clock();
    insertionSort(arr_tmp, size);
    end = clock();
        
    free(arr_tmp);
    
    return (end - start)/(CLOCKS_PER_SEC/1000);
}

int calcula_selection(int *arr, int size){
    int *arr_tmp = copia_arr(arr, size);
    clock_t start, end;
    
    start = clock();
    selectionSort(arr_tmp, size);
    end = clock();
    
    free(arr_tmp);
    
    return (end - start)/(CLOCKS_PER_SEC/1000);
}

int calcula_bubble(int *arr, int size){
    int *arr_tmp = copia_arr(arr, size);
    clock_t start, end;
    
    start = clock();
    bubbleSort(arr_tmp, size);
    end = clock();
        
    free(arr_tmp);
    
    return (end - start)/(CLOCKS_PER_SEC/1000);
}

int calcula_merge(int *arr, int first, int last){
    int *arr_tmp = copia_arr(arr, last);
    clock_t start, end;
    
    start = clock();
    mergeSort(arr_tmp, first, last);
    end = clock();
        
    free(arr_tmp);
    
    return (end - start)/(CLOCKS_PER_SEC/1000);
}

int calcula_heap(int *arr, int size){
    int *arr_tmp = copia_arr(arr, size);
    clock_t start, end;
    
    start = clock();
    heapSort(arr_tmp, size);
    end = clock();
        
    free(arr_tmp);
    
    return (end - start)/(CLOCKS_PER_SEC/1000);
}

int calcula_quick(int *arr, int first, int last){
    int *arr_tmp = copia_arr(arr, last);
    clock_t start, end;
    
    start = clock();
    quickSort(arr_tmp, first, last);
    end = clock();
        
    free(arr_tmp);
    
    return (end - start)/(CLOCKS_PER_SEC/1000);
}

int main(){
    int size;

    printf("Qual o tamanho do vetor?");
    scanf("%d", &size);
    
    int *arr = gera_arr(size, 'c');
    int *novo_arr = copia_arr(arr, size);
    printf("tempo percorrido insertionSort: %d, comparacoes realizadas: %d\n", calcula_insertion(arr, size), cmp[0]);
    printf("tempo percorrido selectionSort: %d, comparacoes realizadas: %d\n", calcula_selection(arr, size), cmp[1]);
    printf("tempo percorrido bubbleSort: %d, comparacoes realizadas: %d\n", calcula_bubble(arr, size), cmp[2]);
    printf("tempo percorrido mergeSort: %d, comparacoes realizadas: %d\n", calcula_merge(arr, 0, size-1), cmp[3]);
    printf("tempo percorrido quickSort: %d, comparacoes realizadas: %d\n", calcula_quick(arr, 0, size-1), cmp[4]);
    printf("tempo percorrido heapSort: %d, comparacoes realizadas: %d\n", calcula_heap(arr, size), cmp[5]);

    free(arr);

    return 0;
}