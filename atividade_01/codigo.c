#include <stdio.h>
#include <math.h>

int vetor[10] = {5, 10, 9, 2, 4, 3, 7, 6, 8, 1};

void swap(int k){
    int aux = vetor[k];
    vetor[k] = vetor[k+1];
    vetor[k+1] = aux;
}

void sort(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-1; j++){
            if(vetor[j] > vetor[j+1]){
                swap(j);
            }
        }
    }
}

void print_vector(int n){
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
}

int main() {
    sort(10);
    print_vector(10);
    return 0;
}