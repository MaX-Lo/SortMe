//
// Created by max on 11.11.16.
// Different sorting algorithms (with speed comparision)
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int *list, int len);

void insertion_sort(int *list, int len);

void quick_sort(int *list, int len);

int *copy(int *from, int *to, int len);


void heap_sort(int *list, int len) ;

int main(void) {

    int size;
    printf("Array size: ");
    scanf("%d", &size);

    int list[size];
    srand(0);
    for (int i = 0; i < size; i++)
        list[i] = rand() % 10000;

    int len = sizeof(list) / sizeof(list[0]);
    printf("len: %d\n", len);

    // bubble sort
    clock_t start = clock();
    bubble_sort(list, len);
    clock_t end = clock();
    double time_spent = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Bubblesort: %fs\n", time_spent);

    // insertion sort
    start = clock();
    insertion_sort(list, len);
    end = clock();
    time_spent = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Insertsort: %fs\n", time_spent);

    // quick sort
    start = clock();
    quick_sort(list, len);
    end = clock();
    time_spent = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Quicksort: %fs\n", time_spent);

    // heap sort
    start = clock();
    heap_sort(list, len);
    end = clock();
    time_spent = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Heapsort: %fs\n", time_spent);

    return 0;
}

int *copy(int *from, int *to, int len) {
    for (int i = 0; i < len; i++) {
        to[i] = from[i];
    }
}

void printArr(int *array, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d\n", array[i]);
    }
}

void bubble_sort(int *list, int len) {
    int tmp;
    int ls[len];

    copy(list, ls, len);

    for (int i = len - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (ls[j] > ls[j + 1]) {
                tmp = ls[j];
                ls[j] = ls[j + 1];
                ls[j + 1] = tmp;
            }
        }
    }
}

void insertion_sort(int *list, int len) {

    int ls[len];
    copy(list, ls, len);

    for (int i = 1; i < len; i++) {
        int current = ls[i];
        for (int j = i; j > 0; j--) {
            if (current < ls[j - 1]) {
                ls[j] = ls[j - 1];
                if (j - 1 == 0) ls[j - 1] = current;
            } else {
                ls[j] = current;
                break;
            }
        }
    }
}

int partition(int a[], int l, int r) {
    int pivot, i, j, t;
    pivot = a[l];
    i = l;
    j = r + 1;

    while (1) {
        do ++i;
        while (a[i] <= pivot && i <= r);

        do --j;
        while (a[j] > pivot);

        if (i >= j) break;

        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    t = a[l];
    a[l] = a[j];
    a[j] = t;

    return j;
}

void quick_sort_run(int *a, int l, int r) {
    int j;

    if (l < r) {
        // divide and conquer
        j = partition(a, l, r);
        quick_sort_run(a, l, j - 1);
        quick_sort_run(a, j + 1, r);
    }

}

void quick_sort(int *list, int len) {

    int ls[len];
    copy(list, ls, len);

    quick_sort_run(ls, 0, len - 1);
}

void sinken_lassen(int a[], int l, int r) {
    int i, j, h;
    i = l;
    h = a[i];

    while (1) {
        j = 2 * i + 1; // gehe zum linken Nachfolger von i
        if (j > r)
            break;

        if (j < r)
            if (a[j] < a[j + 1])
                j = j + 1; // rechter Nachfolger a[j+1] ist groesser als linker Nachfolger a[j]

        if (h > a[j])
            break;
        else {
            a[i] = a[j]; // von j nach i sinken lassen
            i = j;
        }
    a[i] = h;
    }
}

void heap_sort(int *list, int len) {
    int a[len];
    copy(list, a, len);
    int n = len;

    int li, re, x;

    li = n / 2;
    re = n - 1;
    while (li > 0) { // Phase 1
        --li; // rechte Feldgrenze re = n-1 bleibt konstant, linke Feldgrenze wird dekrementiert
        sinken_lassen(a, li, re);
    }

    while (re > 0) { // Phase 2
        x = a[0];
        a[0] = a[re];
        a[re] = x;
        --re;
        sinken_lassen(a, 0, re); // linke Feldgrenze 0 bleibt konstant, rechte Feldgrenz re wird dekrementiert
    }
}