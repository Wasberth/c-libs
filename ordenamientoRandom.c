/*
 * García Piña Wilberth David
 * Gómez Tagle Espinosa José Ricardo
 * 2BM1
 * Inteligencia artificial
 * 23/02/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "askfor.h"
#include "genericSort.h"

#define MIN_LENGTH 10
#define MIN_RANDOM 0
#define MAX_RANDOM 70 // 459565

typedef bool (*validation)(int);

void printArray(const char* text, int* array, int size) {
    printf(text);
    printf(": [");
    for (int i = 0; i < size; i++) {
        printf("%d%s", array[i], i != size - 1 ? ", " : "");
    }
    printf("]");
}

int rng(int min, int max) {
    return (rand() * rand()) % (max - min + 1) + min;
}

bool isEven(int i) {
    return i % 2 == 0;
}

bool isOdd(int i) {
    return i % 2 != 0;
}

int filter(int** result, int* array, int size, validation isValid) {
    int filtered = 0;
    int* newArray = malloc(0);

    for (int i = 0; i < size; i++) {
        if (!isValid(array[i])) continue;
        newArray = realloc(newArray, ++filtered * sizeof(int));
        newArray[filtered - 1] = array[i];
    }

    *result = newArray;

    return filtered;
}

int main() {
    time_t t;
    srand((unsigned) time(&t));

    int cNums = askForInt("Ingrese la cantidad de numeros random a generar", MIN_LENGTH, INT_MAX);
    int* array = malloc(cNums * sizeof(int));

    if (array == NULL) {
        puts("Se quedó sin memoria, terminando el programa");
        return 0;
    }

    for (int i = 0; i < cNums; i++) {
        array[i] = rng(MIN_RANDOM, MAX_RANDOM);  // de 0 a 459,565
    }

    printArray("\nEl array sin ordenar es", array, cNums);

    int* evenArray = NULL;
    int cEven = filter(&evenArray, array, cNums, &isEven);

    printArray("\nEl array con los pares sin ordenar es", evenArray, cEven);

    filter(&evenArray, array, cNums, &isEven);
    ArrayControl a = Int2Var(&evenArray, cEven, &intLessThan);
    startSelectionSort(a);
    printArray("\nEl array con los pares ordenados por seleccion es", evenArray, cEven);

    filter(&evenArray, array, cNums, &isEven);
    a = Int2Var(&evenArray, cEven, &intLessThan);
    startBubbleSort(a);
    printArray("\nEl array con los pares ordenados por burbuja es", evenArray, cEven);

    filter(&evenArray, array, cNums, &isEven);
    a = Int2Var(&evenArray, cEven, &intLessThan);
    startInsertionSort(a);
    printArray("\nEl array con los pares ordenados por insercion es", evenArray, cEven);

    filter(&evenArray, array, cNums, &isEven);
    a = Int2Var(&evenArray, cEven, &intLessThan);
    startMergeSort(a);
    printArray("\nEl array con los pares ordenados por merge es", evenArray, cEven);

    int search = array[0];
    void* s = &search;

    int ind = startSecuentialSearch(a, s, &intEquals);
    printf("\nEl índice en donde se encuentra %d es %d (sec)", search, ind);

    ind = startBinarySearch(a, s, &intEquals);
    printf("\nEl índice en donde se encuentra %d es %d (bin)", search, ind);

    int* oddArray = NULL;
    int cOdd = filter(&oddArray, array, cNums, &isOdd);

    printArray("\nEl array con los impares sin ordenar es", oddArray, cOdd);

    ArrayControl b = Int2Var(&oddArray, cOdd, &intLessThan);
    startSelectionSort(b);
    printArray("\nEl array con los impares ordenados por seleccion es", oddArray, cOdd);

    b = Int2Var(&oddArray, cOdd, &intLessThan);
    startBubbleSort(b);
    printArray("\nEl array con los impares ordenados por burbuja es", oddArray, cOdd);

    b = Int2Var(&oddArray, cOdd, &intLessThan);
    startInsertionSort(b);
    printArray("\nEl array con los impares ordenados por insercion es", oddArray, cOdd);

    b = Int2Var(&oddArray, cOdd, &intLessThan);
    startMergeSort(b);
    printArray("\nEl array con los impares ordenados por merge es", oddArray, cOdd);

    ind = startSecuentialSearch(b, s, &intEquals);
    printf("\nEl índice en donde se encuentra %d es %d (sec)", search, ind);

    ind = startBinarySearch(b, s, &intEquals);
    printf("\nEl índice en donde se encuentra %d es %d (bin)", search, ind);

    cleanupAC(&a);
    cleanupAC(&b);
    free(evenArray);
    free(oddArray);

    return 0;
}
