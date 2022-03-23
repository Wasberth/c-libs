/*
 * García Piña Wilberth David
 * Gómez Tagle Espinosa José Ricardo
 * 2BM1
 * Inteligencia artificial
 * 19/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Retorna verdadero si se deberían acomodar de otra forma los elementos
typedef bool (*genOp)(void*, void*);

// Obtiene un componente del array con su índice
typedef void* (*gGet)(void**, int);

// Coloca un valor en la posisión que se le da en el arreglo
// O guarda un valor en la posición en un temporal
typedef void (*gSet)(void**, int, void*);

typedef struct gen {
    void** vector;
    int size;
    void* temp;
    size_t typeSize;
    genOp doSort;
    gGet get;
    gSet set;
    gSet copyOnTemp;
    gSet writeFromTemp;
} ArrayControl;

// SORTS

/* Normalmente
 * g  = 8
 * s  = 7
 * ct = 6
 * wt = 6
 * ds = 5
 * 
*/

void startSelectionSort(ArrayControl array) { // Normalmente 21n^2 + n + 28
    // T(n) = 1 + n + 2gn^2 + (ds)n^2 + n^2 + ct + s + g + wt
    int sorted; 

    for (int i = 0; i < array.size - 1; i++) { // Para todos los elementos del array
        sorted = i;

        for (int j = i + 1; j < array.size; j++) // Se busca todos los elementos que le siguen
            if (array.doSort(array.get(array.vector, j), array.get(array.vector, sorted)))
                sorted = j; // Y se elige el más pequeño

        array.copyOnTemp(array.vector, i, array.temp); // Se respalda
        array.set(array.vector, i, array.get(array.vector, sorted)); // Se asigna al que se respaldó
        array.writeFromTemp(array.vector, sorted, array.temp); // Se asigna el respaldo
    }
}

void startBubbleSort(ArrayControl array) { // 51n^2
    // T(n) = n^2((ds) + 3g + ct + s + wt + 3)
    for (int i = 0; i < array.size - 1; i++) // Para todos los elementos del array
        for (int j = 0; j < array.size - i - 1; j++) // Se compara con todos los demás
            if (array.doSort(array.get(array.vector, j + 1), array.get(array.vector, j))) { // Y si se cumple la condición
                array.copyOnTemp(array.vector, j, array.temp); // Se cambian
                array.set(array.vector, j, array.get(array.vector, j + 1));
                array.writeFromTemp(array.vector, j + 1, array.temp);
            }
}

void startInsertionSort(ArrayControl array) { // 16n + 30n^2
    // T(n) = 4n + ctn + wtn + n^2((ds) + 2g + s + 2)
    for (int i = 1; i < array.size; i++) { // Para todos los elementos del array, excepto el primero
        int j = i - 1;
        array.copyOnTemp(array.vector, i, array.temp);

        while (j >= 0 && array.doSort(array.temp, array.get(array.vector, j))) {
            array.set(array.vector, j + 1, array.get(array.vector, j));
            j--;
        }

        array.writeFromTemp(array.vector, j + 1, array.temp);
    }
}

void merge(ArrayControl array, int l, int m, int r) { // 113n + 23
    // T(n) = 23 + 17n + 7ng + 5ns + n(ds)
    // Imprimir porque tiene error cuando el arreglo tiene tamaño par
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    void* Lar = malloc(n1 * array.typeSize); // Left array
    void* Rar = malloc(n1 * array.typeSize); // Rigth array

    /* Copy data to temp arrays Lar[] and Rar[] */
    for (i = 0; i < n1; i++)
        array.set(&Lar, i, array.get(array.vector, l + i)); // Lar[i] = arr[l + i]
    for (j = 0; j < n2; j++)
        array.set(&Rar, j, array.get(array.vector, m + 1 + j)); // Rar[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {

        if (array.doSort(array.get(&Lar, i), array.get(&Rar, j))) { // if (L[i], R[j])
            array.set(array.vector, k++, array.get(&Lar, i++)); // arr[k] = L[i];
            continue;
        }

        array.set(array.vector, k++, array.get(&Rar, j++)); // arr[k] = R[j];
    }

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) {
        array.set(array.vector, k++, array.get(&Lar, i++)); // arr[k] = L[i];
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) {
        array.set(array.vector, k++, array.get(&Rar, j++)); // arr[k] = R[j];
    }

    free(Lar);
    free(Rar);
}

void mergeSort(ArrayControl array, int l, int r) { // (113n + 29)(2^n)
    // T(n) = (2^n) (6 + T(merge))
    if (l >= r)
        return;

    // Same as (l + r) / 2, but avoids overflow for
    // large l and h
    int m = l + (r - l) / 2;

    // Sort first and second halves
    mergeSort(array, l, m);
    mergeSort(array, m + 1, r);

    merge(array, l, m, r);
}

void startMergeSort(ArrayControl array) { // (113n + 29)(2^n) + 1
    // T(n) = T(mergeSort) + 1
    mergeSort(array, 0, array.size - 1);
}

// INT ARRAY CONTROL CREATION

void cleanupAC(ArrayControl* a) {
    free(a->temp);
}

void* intGet(void** array, int i) {
    void* a = (void*) &(((int**) array)[0][i]);
    return a;
}

void intSet(void** array, int i, void* v) {
    ((int**) array)[0][i] = *((int*) v);
}

void intCopyOnTemp(void** array, int i, void* temp) {
    ((int*) temp)[0] = ((int**) array)[0][i];
}

void intWriteFromTemp(void** array, int i, void* temp) {
    ((int**) array)[0][i] = ((int*) temp)[0];
}

bool intLessThan(void* a, void* b) {
    return ((int*) a)[0] < ((int*) b)[0];
}

bool intGreatThan(void* a, void* b) {
    return ((int*) a)[0] > ((int*) b)[0];
}

bool intEquals(void* a, void* b) {
    return ((int*) a)[0] == ((int*) b)[0];
}

ArrayControl Int2Var(int** arr, int size, genOp doSort) { // 15
    void** array = (void**) arr;
    void* temp = malloc(sizeof(int));

    ArrayControl a = { array, size, temp, sizeof(int), doSort,
       &intGet, &intSet, &intCopyOnTemp, &intWriteFromTemp };
    return a;
}

// SEARCH

int startSecuentialSearch(ArrayControl array, void* searched, genOp equals) { // 3 + 15n
    // T(n) = 3 + n((ds) + g + 2)
    int found = -1;

    for (int i = 0; i < array.size; i++) {
        if (!equals(array.get(array.vector, i), searched)) continue; // if(array[i] != searched)
        found = i;
        break;
    }

    return found;
}

int startBinarySearch(ArrayControl array, void* searched, genOp equals) { // 8 + 17log(n)
    // 8 + (8 + 2g + 2ds)log(n)
    int i = 0, j = array.size - 1;
    int found = -1;

    while (i <= j) {
        int m = i + (j - i) / 2;
        //if (arreglo[mitad].valor == elementoBuscado.valor) {
        if (equals(array.get(array.vector, m), searched)) {
            found = m;
            break;
        }

        if (array.doSort(array.get(array.vector, m), searched)) {
            i = m + 1;
            continue;
        }

        j = m - 1;
    }

    return found;
}


