#include <iostream>
#include <algorithm>

void merge(int* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int getMinPeopleMad(const int* myList, int n) {
    int currentTime = 0;
    int counter = 0;
    for (int i = 0; i < n; ++i) {
        if (myList[i] >= currentTime) {
            ++counter;
            currentTime += myList[i];
        }
    }
    return counter;
}

int main() {
    int n;
    std::cin >> n;
    int* myList = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> myList[i];
    }

    mergeSort(myList, 0, n - 1);

    int minMad = n - getMinPeopleMad(myList, n);
    std::cout << minMad;

    delete[] myList;

    return 0;
}