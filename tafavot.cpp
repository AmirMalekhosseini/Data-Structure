#include <iostream>
#include <vector>
#include <cmath>


int maxDiffSum(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    int n1 = arr1.size(), n2 = arr2.size();
    int maxDiffSum = 0;
    int i = 0, j = n2 - 1; 

    while (i < n1) {
        int diff = std::abs(arr2[j] - arr1[i]);

        maxDiffSum += diff;

        i++; 
        j--; 
    }

    return maxDiffSum;
}

void insertionSort(std::vector<int> arr, int n){
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> arr1(n);
    std::vector<int> arr2(m);

    for (int i = 0; i < n; i++) {
        std::cin >> arr1[i];
    }


    for (int i = 0; i < m; i++) {
        std::cin >> arr2[i];
    }

        insertionSort(arr1, n);
        insertionSort(arr2, n);


    // std::vector<bool> mapped(m, false); // Keep track of whether an element in arr2 has been mapped

    // int max_diff = 0;

    // for (int i = n - 1; i >= 0; i--) {
    //     int diff = 0;
    //     int max_temp_diff = 0;  
    //     int max_index = 0;  
    //     for (int j = 0; j < m; j++) {
    //         int temp_diff = std::abs(arr2[j] - arr1[i]);
    //         if (!mapped[j] && temp_diff > max_temp_diff) {
    //             max_temp_diff = temp_diff;
    //             max_index = j;
    //         }
    //     }
    //     diff = max_temp_diff;
    //     mapped[max_index] = true;  // Mark the element in arr2 as mapped
    //     max_diff += diff;
    // }

        int max_diff = maxDiffSum(arr1, arr2);

        std::cout << max_diff << std::endl;

        return 0;
}
